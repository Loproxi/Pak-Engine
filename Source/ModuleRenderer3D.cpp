#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "ModuleUIcontroller.h"
#include "ModuleScene.h"

#include "Mesh.h"
#include "Comp_MeshRenderer.h"
#include "Comp_Transform.h"

#include "glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "DevIL/include/ilut.h"
#include "DevIL/include/ilu.h"

#include "MathGeoLib.h"

#include "ModuleInput.h"



ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled),test(nullptr),cube(nullptr)
{
	SetNameOfModule("Renderer");
	renderstuff.cullface = false;
	renderstuff.depthtest = false;
	renderstuff.lighting = false;
	renderstuff.wireframe = false;
	renderstuff.vsync = false;
	context = NULL;
	testshader = nullptr;

}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}



// Called before render is available
bool ModuleRenderer3D::Init(pugi::xml_node& config)
{
	
	LOG("Creating 3D Renderer context");

	App->AddLog(Logs::NORMAL,"Creating 3D Renderer context");

	bool ret = true;

	//Set context attributes

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		App->AddLog(Logs::ERROR_LOG, "OpenGL context could not be created! ");
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	//Init DevIL
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		/* wrong DevIL version */
		App->AddLog(Logs::ERROR_LOG, "Error wrong DevIL version");
	}
	else
	{
		ilInit();
		iluInit();
		ilutInit();
	}
	//Init Glew
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		App->AddLog(Logs::ERROR_LOG, "Glew could not be initialized!! ");
		printf("Glew could not be initialized! Glew_error: %s \n", glewGetErrorString(error));
	}
	
	if(ret == true)
	{
		renderstuff.vsync = config.child("Renderer").child("vsync").attribute("value").as_bool();
		renderstuff.depthtest = config.child("Renderer").child("depthtest").attribute("value").as_bool();
		renderstuff.cullface = config.child("Renderer").child("cullface").attribute("value").as_bool();
		renderstuff.lighting = config.child("Renderer").child("lighting").attribute("value").as_bool();
		renderstuff.wireframe = config.child("Renderer").child("wireframe").attribute("value").as_bool();
		//Use Vsync
		


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

		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
		

		SetDepthTest();
		SetCullFace();
		SetLightning();
		SetWireframe();

		lights[0].Active(true);
		glEnable(GL_COLOR_MATERIAL);

		// Enable opacity
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	// Projection matrix for
	OnResize(App->window->GetScreenWidth(), App->window->GetScreenHeight());

	//Test RapidJSON
	LoadTextureImporter("");
	LoadTextureImporter("Assets/Baker_house.png");

	testshader = new Shaders("Assets/Shaders/vertexshader_core.pesh", "Assets/Shaders/fragmentshader_core.pesh");
	
	
	LoadModelImporter("Assets/BakerHouse.fbx");

	return ret;
}

bool ModuleRenderer3D::Start()
{

	return true;
}



// PreUpdate: clear buffer
UpdateStatus ModuleRenderer3D::PreUpdate()
{
	//CLEANING Every Frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Test Intersections Mathgeo
	/*bool intersects = false;

	LineSegment* line = new LineSegment(float3(1, 0, 5), float3(2, 0, 5));

	Capsule capsule(LineSegment(float3(0.5, 0, 5), float3(2, 0, 5)), 10);

	intersects = line->Intersects(capsule);

	LCG hey;

	int hey2 = hey.Int(1, 89);

	delete line;

	line = nullptr;*/

	//App->AddLog(Logs::WARNING,"Updating 3D Renderer context");

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
UpdateStatus ModuleRenderer3D::PostUpdate()
{
	UpdateStatus ret = UpdateStatus::UPDATE_CONTINUE;
	
	glBindFramebuffer(GL_FRAMEBUFFER, App->camera->scenecam.framebuffer.GetFrameBuffer());
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	App->camera->cameratobedrawn = &App->camera->scenecam;

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Draw(testshader);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (App->camera->gamecams.size() != 0 && App->camera->gamecamactive != nullptr)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, App->camera->gamecamactive->framebuffer.GetFrameBuffer());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		App->camera->cameratobedrawn = App->camera->gamecamactive;

		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->Draw(testshader);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	if (!App->uiController->Draw())
	{
		ret = UpdateStatus::UPDATE_STOP;
	};

	SDL_GL_SwapWindow(App->window->window);

	meshes.clear();

	return ret;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	App->AddLog(Logs::NORMAL,"Destroying 3D Renderer");
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	RELEASE(test);
	RELEASE(cube);
	RELEASE(testshader);

	for (int i = 0; i < textures.size(); i++)
	{
		RELEASE(textures[i]);
	}
	textures.clear();

	auto iter = trihitsdistmap.begin();
	while (iter != trihitsdistmap.end()) 
	{
		RELEASE(iter->second);
	}

	//house.CleanUp();

	return true;
}

bool ModuleRenderer3D::SaveSettings(pugi::xml_node& config)
{

	config.child("Renderer").child("vsync").attribute("value") = renderstuff.vsync;
	config.child("Renderer").child("depthtest").attribute("value") = renderstuff.depthtest;
	config.child("Renderer").child("cullface").attribute("value") = renderstuff.cullface;
	config.child("Renderer").child("lighting").attribute("value") = renderstuff.lighting;
	config.child("Renderer").child("wireframe").attribute("value") = renderstuff.wireframe;

	return true;
}

void ModuleRenderer3D::SetVsync(bool vsync)
{
	renderstuff.vsync = vsync;
	//If vsync is true enable if it is not disable
	vsync ? SDL_GL_SetSwapInterval(vsync) : SDL_GL_SetSwapInterval(vsync);
	
}

void ModuleRenderer3D::SetDepthTest()
{
	//If depthtest is true enable if it is not disable
	renderstuff.depthtest ? glEnable(GL_DEPTH_TEST): glDisable(GL_DEPTH_TEST);
}

void ModuleRenderer3D::SetCullFace()
{
	
	//If cullface is true enable if it is not disable
	renderstuff.cullface ? glEnable(GL_CULL_FACE): glDisable(GL_CULL_FACE);
}

void ModuleRenderer3D::SetLightning()
{
	//If lightning is true enable if it is not disable
	renderstuff.lighting ? glEnable(GL_LIGHTING): glDisable(GL_LIGHTING);
}

void ModuleRenderer3D::SetWireframe()
{
	//If wireframe is true enable if it is not disable
	renderstuff.wireframe ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE): glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ModuleRenderer3D::OnResize(int width, int height)
{
	App->window->SetScreenWidth(width);
	App->window->SetScreenHeight(height);

	App->camera->scenecam.SetUpFrameBuffer(width, height);
	if (App->camera->gamecams.size() != 0)
	{
		App->camera->gamecamactive->SetUpFrameBuffer(width, height);
	}
	glViewport(0, 0, width, height);

}

void ModuleRenderer3D::LoadModelImporter(std::string path)
{

	ModelImporter currentModel;

	currentModel.Import(path);

}

void ModuleRenderer3D::LoadTextureImporter(std::string path)
{
	if (path == "")
	{
		texturenum++;
		textures.push_back(TextureImporter::LoadCheckerImage());
	}
	else
	{
		//TODO Enhance this system
		texturenum++;
		textures.push_back(TextureImporter::Import(path));

		if (App->uiController->GetGameObjSelected() != nullptr)
		{
			if (App->uiController->GetGameObjSelected()->GetComponent<Comp_MeshRenderer>() == nullptr)
			{
				App->AddLog(Logs::ERROR_LOG, "This GameObject doesnt has MeshRenderer");
			}
			else
			{
				App->uiController->GetGameObjSelected()->GetComponent<Comp_MeshRenderer>()->GetMesh()->SetTextureID(textures.at(texturenum)->textID);
			}
		}
	}

}

void ModuleRenderer3D::AddDebug(/*float3* points*/)
{
	
	glBegin(GL_POINTS);
	
		glColor3f(1.f, 0.f, 0.f);

		glPointSize(8.0f);
		
		glVertex3f(5.0f, 0.0f, 0.0f); 
		glVertex3f(10.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		//glVertex3f(points[6].x, points[6].y, points[6].z);
		//glVertex3f(points[6].x, points[6].y, points[6].z); 
		//glVertex3f(points[4].x, points[4].y, points[4].z);
		//glVertex3f(points[4].x, points[4].y, points[4].z); 
		//glVertex3f(points[0].x, points[0].y, points[0].z);
	
	glEnd();


}

Comp_MeshRenderer* ModuleRenderer3D::RayIntersects(LineSegment& line)
{
	std::vector<Comp_MeshRenderer*> meshIntersectedbyAABB;
	for (uint i = 0; i < meshes.size(); i++)
	{
		if (line.Intersects(meshes[i]->GetMesh()->GlobalAxisAlignBB))
		{
			meshIntersectedbyAABB.push_back(meshes[i]);
		}
	}

	if (meshIntersectedbyAABB.size() == 0)
	{
		App->uiController->SetGameObjSelected(nullptr);
	}


	

	for (int j = 0; j < meshIntersectedbyAABB.size(); j++)
	{
		//New variable to save the ray in local coordinates
		LineSegment rayinlocalspace = line;

		float4x4 meshglobalmatrix = meshIntersectedbyAABB[j]->comp_owner->GetComponent<Comp_Transform>()->GetGlobalMatrix();

		float4x4 meshlocalmatrix = meshglobalmatrix.Inverted();

		//multiply ray's position by the inverted global matrix of the mesh in order to convert ray in global position to mesh's local space
		rayinlocalspace.Transform(meshlocalmatrix);

		Mesh* tempmesh = meshIntersectedbyAABB[j]->GetMesh();

		for (uint k = 0; k < tempmesh->GetNumIndices(); k += 3)
		{
			float intersectlength = 0;
			//Creating vertices from the vertices of the mesh at the index of the indices
			float3 vertex1 = tempmesh->GetVertices()[tempmesh->GetIndices()[j]].position;
			float3 vertex2 = tempmesh->GetVertices()[tempmesh->GetIndices()[j + 1]].position;
			float3 vertex3 = tempmesh->GetVertices()[tempmesh->GetIndices()[j + 2]].position;

			//Create the triangle using the 3 vertices previously created
			Triangle triIntersects(vertex1, vertex2, vertex3);

			if (rayinlocalspace.Intersects(triIntersects, &intersectlength, nullptr))
			{
				trihitsdistmap[intersectlength] = meshIntersectedbyAABB[j];
			}
		}
	}
	meshIntersectedbyAABB.clear();

	if (trihitsdistmap.size() == 0)
	{
		return nullptr;
	}
	else
	{
		return trihitsdistmap.begin()->second;
	}
	
}
