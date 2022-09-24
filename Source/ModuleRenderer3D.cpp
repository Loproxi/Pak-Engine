#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "ModuleUIcontroller.h"

#include "glew.h"
#include "External/SDL/include/SDL_opengl.h"

#include "MathGeoLib.h"

#include "parson.h"

ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

void print_commits_info(const char* username, const char* repo) {
	JSON_Value* root_value;
	JSON_Array* commits;
	JSON_Object* commit;
	size_t i;

	char curl_command[512];
	char cleanup_command[256];
	char output_filename[] = "commits.json";

	/* it ain't pretty, but it's not a libcurl tutorial */
	sprintf_s(curl_command,
		"curl -s \"https://api.github.com/repos/%s/%s/commits\" > %s",
		username, repo, output_filename);
	sprintf_s(cleanup_command, "rm -f %s", output_filename);
	system(curl_command);

	/* parsing json and validating output */
	root_value = json_parse_file(output_filename);
	if (json_value_get_type(root_value) != JSONArray) {
		system(cleanup_command);
		return;
	}

	/* getting array from root value and printing commit info */
	commits = json_value_get_array(root_value);
	printf("%-10.10s %-10.10s %s\n", "Date", "SHA", "Author");
	for (i = 0; i < json_array_get_count(commits); i++) {
		commit = json_array_get_object(commits, i);
		printf("%.10s %.10s %s\n",
			json_object_dotget_string(commit, "commit.author.date"),
			json_object_get_string(commit, "sha"),
			json_object_dotget_string(commit, "commit.author.name"));
	}

	/* cleanup code */
	json_value_free(root_value);
	system(cleanup_command);
}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			//LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			//LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			//LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.60f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);

		// Enable opacity
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	print_commits_info("Loproxi", "Pak-Engine");

	return ret;
}

// PreUpdate: clear buffer
UpdateStatus ModuleRenderer3D::PreUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	// Test Intersections Mathgeo

	/*bool intersects = false;

	LineSegment* line = new LineSegment(float3(1, 0, 5), float3(2, 0, 5));

	Capsule capsule(LineSegment(float3(0.5, 0, 5), float3(2, 0, 5)), 10);

	intersects = line->Intersects(capsule);

	LCG hey;

	int hey2 = hey.Int(1, 89);

	delete line;

	line = nullptr;*/

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
UpdateStatus ModuleRenderer3D::PostUpdate()
{
	UpdateStatus ret = UpdateStatus::UPDATE_CONTINUE;

	SDL_GL_SwapWindow(App->window->window);
	return ret;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 2048.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
