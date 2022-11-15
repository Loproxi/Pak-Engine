#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "ModuleUIcontroller.h"
#include "ModuleScene.h"

#include "Mesh.h"
#include "Comp_MeshRenderer.h"

#include "glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "DevIL/include/ilut.h"
#include "DevIL/include/ilu.h"

#include "MathGeoLib.h"

#include "ModuleInput.h"

//#include "document.h"     // rapidjson's DOM-style API
//#include "prettywriter.h" // for stringify JSON
//#include <cstdio>

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
	
	
//	using namespace rapidjson;
//	
//	const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
//	printf("Original JSON:\n %s\n", json);
//
//	Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
//
//#if 0
//	// "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
//	if (document.Parse(json).HasParseError())
//		return 1;
//#else
//	// In-situ parsing, decode strings directly in the source string. Source must be string.
//	char buffer[sizeof(json)];
//	memcpy(buffer, json, sizeof(json));
//	if (document.ParseInsitu(buffer).HasParseError())
//		return 1;
//#endif
//
//	printf("\nParsing to document succeeded.\n");
//
//	////////////////////////////////////////////////////////////////////////////
//	// 2. Access values in document. 
//
//	printf("\nAccess values in document:\n");
//	assert(document.IsObject());    // Document is a JSON value represents the root of DOM. Root can be either an object or array.
//
//	assert(document.HasMember("hello"));
//	assert(document["hello"].IsString());
//	printf("hello = %s\n", document["hello"].GetString());
//
//	// Since version 0.2, you can use single lookup to check the existing of member and its value:
//	Value::MemberIterator hello = document.FindMember("hello");
//	assert(hello != document.MemberEnd());
//	assert(hello->value.IsString());
//	assert(strcmp("world", hello->value.GetString()) == 0);
//	(void)hello;
//
//	assert(document["t"].IsBool());     // JSON true/false are bool. Can also uses more specific function IsTrue().
//	printf("t = %s\n", document["t"].GetBool() ? "true" : "false");
//
//	assert(document["f"].IsBool());
//	printf("f = %s\n", document["f"].GetBool() ? "true" : "false");
//
//	printf("n = %s\n", document["n"].IsNull() ? "null" : "?");
//
//	assert(document["i"].IsNumber());   // Number is a JSON type, but C++ needs more specific type.
//	assert(document["i"].IsInt());      // In this case, IsUint()/IsInt64()/IsUint64() also return true.
//	printf("i = %d\n", document["i"].GetInt()); // Alternative (int)document["i"]
//
//	assert(document["pi"].IsNumber());
//	assert(document["pi"].IsDouble());
//	printf("pi = %g\n", document["pi"].GetDouble());
//
//	{
//		const Value& a = document["a"]; // Using a reference for consecutive access is handy and faster.
//		assert(a.IsArray());
//		for (SizeType i = 0; i < a.Size(); i++) // rapidjson uses SizeType instead of size_t.
//			printf("a[%d] = %d\n", i, a[i].GetInt());
//
//		int y = a[0].GetInt();
//		(void)y;
//
//		// Iterating array with iterators
//		printf("a = ");
//		for (Value::ConstValueIterator itr = a.Begin(); itr != a.End(); ++itr)
//			printf("%d ", itr->GetInt());
//		printf("\n");
//	}
//
//	// Iterating object members
//	static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
//	for (Value::ConstMemberIterator itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr)
//		printf("Type of member %s is %s\n", itr->name.GetString(), kTypeNames[itr->value.GetType()]);
//
//	////////////////////////////////////////////////////////////////////////////
//	// 3. Modify values in document.
//
//	// Change i to a bigger number
//	{
//		uint64_t f20 = 1;   // compute factorial of 20
//		for (uint64_t j = 1; j <= 20; j++)
//			f20 *= j;
//		document["i"] = f20;    // Alternate form: document["i"].SetUint64(f20)
//		assert(!document["i"].IsInt()); // No longer can be cast as int or uint.
//	}
//
//	// Adding values to array.
//	{
//		Value& a = document["a"];   // This time we uses non-const reference.
//		Document::AllocatorType& allocator = document.GetAllocator();
//		for (int i = 5; i <= 10; i++)
//			a.PushBack(i, allocator);   // May look a bit strange, allocator is needed for potentially realloc. We normally uses the document's.
//
//		// Fluent API
//		a.PushBack("Lua", allocator).PushBack("Mio", allocator);
//	}
//
//	// Making string values.
//
//	// This version of SetString() just store the pointer to the string.
//	// So it is for literal and string that exists within value's life-cycle.
//	{
//		document["hello"] = "rapidjson";    // This will invoke strlen()
//		// Faster version:
//		//document["hello"].SetString("rapidjson", 9);
//	}
//
//	// This version of SetString() needs an allocator, which means it will allocate a new buffer and copy the the string into the buffer.
//	Value author;
//	{
//		char buffer2[10];
//		int len = sprintf_s(buffer2, "%s %s", "Milo", "Yip");  // synthetic example of dynamically created string.
//
//		author.SetString(buffer2, static_cast<SizeType>(len), document.GetAllocator());
//		// Shorter but slower version:
//		// document["hello"].SetString(buffer, document.GetAllocator());
//
//		// Constructor version: 
//		// Value author(buffer, len, document.GetAllocator());
//		// Value author(buffer, document.GetAllocator());
//		//memset(buffer2, 567, sizeof(buffer2)); // For demonstration purpose.
//	}
//	// Variable 'buffer' is unusable now but 'author' has already made a copy.
//	document.AddMember("author", author, document.GetAllocator());
//
//	assert(author.IsNull());        // Move semantic for assignment. After this variable is assigned as a member, the variable becomes null.
//
//	////////////////////////////////////////////////////////////////////////////
//	// 4. Stringify JSON
//
//	printf("\nModified JSON with reformatting:\n");
//	StringBuffer sb;
//	PrettyWriter<StringBuffer> writer(sb);
//	document.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
//	puts(sb.GetString());

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	/*if (debug_draw == true)
	{
		BeginDebugDraw();
		App->DebugDraw();
		EndDebugDraw();
	}*/
	App->camera->cameratobedrawn = &App->camera->scenecam;

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Draw(testshader);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//cambiar el gamecams por una variable active bool en camera 3D
	if (App->camera->gamecams.size() != 0)
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