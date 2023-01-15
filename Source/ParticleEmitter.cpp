#include "ParticleEmitter.h"

#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleRenderer3D.h"
#include "ModuleFileSystem.h"
#include "TextureImporter.h"
#include "Comp_Transform.h"
#include "Shaders.h"




ParticleEmitter::ParticleEmitter(TYPES_OF_PARTICLES typeofpart)
{
	app = Application::GetInstance();

	this->name = "smokeparticle";
	//TODO UPGRADE
	//Compute how many particles are being emited each second and multiply by lifetime of each particle and set that as poolsize

	SetParticlePoolSize(2000);

	Vertex quadvertices[]
	{
		//POS               //Normals                               //Texture Coords
		Vertex(float3{-0.5f, -0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{0.0f, 0.0f}),
		Vertex(float3{0.5f, -0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{1.0f, 0.0f}),
		Vertex(float3{0.5f,  0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{1.0f, 1.0f}),
		Vertex(float3{-0.5f,  0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{0.0f, 1.0f}),
	};

	uint quadindices[]
	{
		0,1,2,2,3,0
	};

	SetData(quadvertices, 4, quadindices, 6);

	text = TextureImporter::Import("Assets/smoke.png");
	//INIT BUFFERS

	InitBuffers();

	switch (typeofpart)
	{

	case (SMOKE):

		propertiesOfTheParticle.position = { 0.0f,1.0f,0.0f };
		propertiesOfTheParticle.startsize = 0.5f;
		propertiesOfTheParticle.endsize = 0.2f;
		propertiesOfTheParticle.MaxLifetime = 3.0f;
		propertiesOfTheParticle.velocity = { 0.01f,0.01f,0.0f };
		propertiesOfTheParticle.acceleration = { 0.1f,0.1f,0.0f };
		propertiesOfTheParticle.startColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
		propertiesOfTheParticle.endColor = float4(0.6f, 0.6f, 0.6f, 0.0f);

		break;
	default:

		propertiesOfTheParticle.position = { random.Float() * 5,3.0f,random.Float() };
		propertiesOfTheParticle.startsize = random.Float() * 5;
		propertiesOfTheParticle.endsize = 0.1f;
		propertiesOfTheParticle.MaxLifetime = 5.0f;
		propertiesOfTheParticle.velocity = { 0.0f,0.01f,0.0f };
		propertiesOfTheParticle.acceleration = { 0.0f,0.01f,0.0f };
		propertiesOfTheParticle.startColor = float4(0.0f, 0.0f, 1.0f, 1.0f);
		propertiesOfTheParticle.endColor = float4(0.0f, 0.0f, 1.0f, 1.0f);

	}

	currentparticle = particlesInEmitter.size() - 1;

	EmitParticles(10);

}

void ParticleEmitter::InitBuffers()
{

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoords));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


	texture = text->textID;

	glBindVertexArray(0);

}

ParticleEmitter::~ParticleEmitter()
{
	SaveParticle(particlesInEmitter[lastActiveParticle]);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

	VAO = 0;
	VBO = 0;
	EBO = 0;
	
	particlesInEmitter.clear();

}

void ParticleEmitter::Update(float dt)
{
	for (int i = 0; i < numOfParticlesToRespawn; i++)
	{
		lastActiveParticle = SearchNotActiveParticle();

		//TODO REWORK THIS IN ORDER TO CHANGE HOW RESPAWN PARTICLES WORK
		SettingUpParticlePool(particlesInEmitter[lastActiveParticle]); 
		numOfParticlesToRespawn--;
	}

	EmitParticles(1);

	for (int i = 0; i < particlesInEmitter.size(); i++)
	{
		//No Active means it is available to be remplace
		if (particlesInEmitter[i].Active == false)
		{
			continue;
		}
		//No remainingLifetime means it is dead therefore, is not active
		if (particlesInEmitter[i].remainingLifetime < 0.0f)
		{
			numOfParticlesToRespawn++;
			particlesInEmitter[i].Active = false;
			continue;
		}
		else
		{

			//Compute all the calculus needed to move the particles

			//Remaining life minus dt
			particlesInEmitter[i].remainingLifetime -= dt;

			
			if (particlesInEmitter[i].remainingLifetime > 0.0f)
			{
				// velocity = acceleration * dt
				particlesInEmitter[i].velocity += particlesInEmitter[i].acceleration * dt ;

				// pos += velocity * dt
				particlesInEmitter[i].position += particlesInEmitter[i].velocity * dt;

				
				
			}
		}
	}
}

void ParticleEmitter::Draw(Shaders* shader, Quat BBrot)
{
	//DRAW WITH THE BUFFERS CREATED AT CONSTRUCTOR

	shader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shader->Set1Int("texture0", 0);

	shader->SetMat4fv("viewMatrix", app->camera->cameratobedrawn->GetViewMatrix());
	shader->SetMat4fv("projectionMatrix", app->camera->cameratobedrawn->GetProjMatrix());
	

	for (Particle& particleInPool : particlesInEmitter)
	{
		if (particleInPool.Active == false)
		{
			continue;
		}

		float3 zAxis = { 0.0f,0.0f,1.0f };
		float partRotationInRad = DegToRad(particleInPool.rotation);

		//ROTATION NECESSARY AROUND Z AXIS TO ACHIEVE BILLBOARDING
		//Quat rotation = Quat::RotateAxisAngle(zAxis, partRotationInRad);
		Quat BBRotAroundZ = BBrot * Quat::RotateAxisAngle({ 0.0f,0.0f,1.0f }, DegToRad(particleInPool.rotation));

		float percentageOfLife = particleInPool.remainingLifetime / particleInPool.maxLifetime;

		float4 currentcolor = math::Lerp(particleInPool.endColor, particleInPool.startColor, percentageOfLife);

		shader->Set4Float("partcolor", currentcolor.ptr());

		float currentsize = math::Lerp(particleInPool.endSize, particleInPool.startSize, percentageOfLife);
		
		//Gather pos & rotation &scale
		float4x4 transform = float4x4::FromTRS(particleInPool.position, BBRotAroundZ, { currentsize,currentsize ,1.0f}).Transposed();

		shader->SetMat4fv("modelMatrix", transform.ptr());

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0);
	}
	
}

void ParticleEmitter::SetParticlePoolSize(uint size)
{
	particlesInEmitter.resize(size);
	/*for (int i = 0; i< particlesInEmitter.size();i++)
	{
		SettingUpParticlePool(particlesInEmitter[i]);
	}*/
}

int ParticleEmitter::SearchNotActiveParticle()
{

	// Search the last particle that was used or a particle that has not been used yet 
	//and returns its index in particlesInEmitter Pool

	int maxParticles = particlesInEmitter.size();
	//First we check from the index of the last active particle

	for (int i = lastActiveParticle; i < maxParticles; ++i)
	{
		if (particlesInEmitter[i].remainingLifetime < 0.0f && particlesInEmitter[i].Active == false) {
			lastActiveParticle = i;
			return i;
		}
	}

	//If the first for doesn't return anything we check from the index num 0 till last active
	for (int i = 0; i < lastActiveParticle; ++i)
	{
		if (particlesInEmitter[i].remainingLifetime < 0.0f && particlesInEmitter[i].Active == false)
		{
			lastActiveParticle = i;
			return i;
		}
	}


	lastActiveParticle = 0;
	return 0; // If All particles are Active return the index of the first one and override it
}

void ParticleEmitter::EmitParticles(int numOfparticles)
{
	//SET UP PARTICLE

	for (int i = 0; i < numOfparticles;i++)
	{
		if (currentparticle <= 0)
		{
			currentparticle = particlesInEmitter.size() - 1;
		}

		SettingUpParticlePool(particlesInEmitter[currentparticle]);

		currentparticle--;

	}

}

void ParticleEmitter::SettingUpParticlePool(Particle& particlePoolRef)
{

	particlePoolRef.position = propertiesOfTheParticle.position + this->position;
	particlePoolRef.position.z += random.Float() -0.5;
	particlePoolRef.Active = true;

	particlePoolRef.acceleration = propertiesOfTheParticle.acceleration;
	particlePoolRef.velocity = propertiesOfTheParticle.velocity;
	particlePoolRef.velocity.x += propertiesOfTheParticle.acceleration.x * random.Float() * 1.2f;
	particlePoolRef.velocity.y += propertiesOfTheParticle.acceleration.y * random.Float() * 1.2f;

	particlePoolRef.startColor = propertiesOfTheParticle.startColor;
	particlePoolRef.endColor = propertiesOfTheParticle.endColor;

	particlePoolRef.maxLifetime = propertiesOfTheParticle.MaxLifetime;
	particlePoolRef.remainingLifetime = propertiesOfTheParticle.MaxLifetime;

	particlePoolRef.startSize = propertiesOfTheParticle.startsize;
	particlePoolRef.endSize = propertiesOfTheParticle.endsize;

}

void ParticleEmitter::SetData(const Vertex* vertices, const uint numvertices, const GLuint* indices, const uint numindices)
{
	for (uint i = 0; i < numvertices; i++)
	{
		this->vertices.push_back(vertices[i]);
	}
	for (uint i = 0; i < numindices; i++)
	{
		this->indices.push_back(indices[i]);
	}
}

void ParticleEmitter::AttachEmitterOnGameObject(Comp_Transform* comp_owner_transform)
{
	//Pass gameobject position to emitter pos
	this->position = comp_owner_transform->GetGlobalMatrix().TranslatePart();
}

void ParticleEmitter::SaveParticle(Particle& particleToSave)
{

	std::string modelfilepath = "Library/Particles/" + this->name + ".PKparticle";

	json particle = {

		{"particle",
			{
				{"position", {particleToSave.position.x, particleToSave.position.y, particleToSave.position.z}},
				{"MaxLifeTime", particleToSave.maxLifetime},
				{"StartSize", particleToSave.startSize},
				{"StartColor", {particleToSave.startColor.x, particleToSave.startColor.y,particleToSave.startColor.z,particleToSave.startColor.w}},
				{"EndColor", {particleToSave.endColor.x, particleToSave.endColor.y,particleToSave.endColor.z,particleToSave.endColor.w}},
			}
		}
	};

	std::string s = particle.dump();
	char* buffer = new char[s.length() + 1];
	strcpy(buffer, s.c_str());

	app->fileSystem->SaveBufferToFile(modelfilepath, buffer, s.size(), false);
	RELEASE_ARRAY(buffer);

}
