#include "ParticleEmitter.h"

#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleRenderer3D.h"
#include "Shaders.h"


ParticleEmitter::ParticleEmitter()
{
	app = Application::GetInstance();
	//TODO UPGRADE
	//Compute how many particles are being emited each second and multiply by lifetime of each particle and set that as poolsize

	SetParticlePoolSize(5);

	
	//INIT BUFFERS

	app->renderer3D->LoadTextureImporter("");


	Vertex quadvertices[]
	{
		//POS               //Normals                               //Texture Coords
		Vertex(float3{-0.5f, -0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{0.0f, 0.0f}),
		Vertex(float3{0.5f, -0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{0.0f, 0.0f}),
		Vertex(float3{0.5f,  0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{0.0f, 0.0f}),
		Vertex(float3{-0.5f,  0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{0.0f, 0.0f}),
	};

	uint quadindices[]
	{
		0,1,2,2,3,0
	};

	SetData(quadvertices, 4, quadindices, 6);


	InitBuffers();
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


	texture = Application::GetInstance()->renderer3D->textures.at(0)->textID;

	glBindVertexArray(0);

}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::Update(float dt)
{
	for (int i = 0; i < numOfParticlesToRespawn; i++)
	{
		lastActiveParticle = SearchNotActiveParticle();

		SettingUpParticlePool(particlesInEmitter[lastActiveParticle]);
		numOfParticlesToRespawn--;
	}


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
				particlesInEmitter[i].velocity += particlesInEmitter[i].acceleration * dt;

				
				// pos += velocity * dt
				particlesInEmitter[i].position += (particlesInEmitter[i].velocity * dt) * random.Float() * 100;

				
			}

			
		}

	}

}

void ParticleEmitter::Draw(Shaders* shader)
{
	//DRAW WITH THE BUFFERS CREATED AT CONSTRUCTOR

	shader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shader->Set1Int("texture0", 0);

	shader->SetMat4fv("viewMatrix", app->camera->cameratobedrawn->GetViewMatrix());
	shader->SetMat4fv("projectionMatrix", app->camera->cameratobedrawn->GetProjMatrix());
	shader->Set4Float("partcolor", propertiesOfTheParticle.startColor.ptr());

	for (Particle& particleInPool : particlesInEmitter)
	{
		if (particleInPool.Active == false)
		{
			continue;
		}

		float3 zAxis = { 0.0f,0.0f,1.0f };
		float partRotationInRad = DegToRad(particleInPool.rotation);
		Quat rotation = Quat::RotateAxisAngle(zAxis, partRotationInRad);

		
		//Gather pos & rotation &scale
		float4x4 transform = float4x4::FromTRS(particleInPool.position, Quat::identity, {particleInPool.startSize,particleInPool.startSize ,1.0f}).Transposed();

		shader->SetMat4fv("modelMatrix", transform.ptr());

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0);
	}
	
}

void ParticleEmitter::SetParticlePoolSize(uint size)
{
	particlesInEmitter.resize(size);
	for (int i = 0; i< particlesInEmitter.size();i++)
	{
		SettingUpParticlePool(particlesInEmitter[i]);
	}
}

int ParticleEmitter::SearchNotActiveParticle()
{

	// Search the last particle that was used or a particle that has not been used yet 
	//and returns its index in particlesInEmitter Pool

	int maxParticles = particlesInEmitter.size();
	//First we check from the index of the last active particle

	for (int i = lastActiveParticle; i < maxParticles; ++i)
	{
		if (particlesInEmitter[i].remainingLifetime < 0.0f || particlesInEmitter[i].Active == false) {
			lastActiveParticle = i;
			return i;
		}
	}

	//If the first for doesn't return anything we check from the index num 0 till last active
	for (int i = 0; i < lastActiveParticle; ++i)
	{
		if (particlesInEmitter[i].remainingLifetime < 0.0f || particlesInEmitter[i].Active == false)
		{
			lastActiveParticle = i;
			return i;
		}
	}


	lastActiveParticle = 0;
	return 0; // If All particles are Active return the index of the first one and override it
}

void ParticleEmitter::EmitParticles(ParticleProperties& partprops )
{

	//FIND INDEX IN PARTICLE POOL WITH PARTICLE NOT ACTIVE AND REMPLACE FOR THE NEXT ONE THAT IS GOING TO BE EMITED

	//SET UP PARTICLE

}

void ParticleEmitter::SettingUpParticlePool(Particle& particlePoolRef)
{

	propertiesOfTheParticle.position = { random.Float() * 5,3.0f,random.Float() };
	propertiesOfTheParticle.startsize = random.Float() * 5;
	propertiesOfTheParticle.MaxLifetime = 5.0f;
	propertiesOfTheParticle.velocity = { 0.0f,0.01f,0.0f };
	propertiesOfTheParticle.acceleration = { 0.0f,0.01f,0.0f };
	propertiesOfTheParticle.startColor = float4(0.0f, 0.0f, 1.0f, 1.0f);
	
	particlePoolRef.position = propertiesOfTheParticle.position;
	particlePoolRef.Active = true;

	particlePoolRef.velocity = propertiesOfTheParticle.velocity;
	particlePoolRef.acceleration = propertiesOfTheParticle.acceleration;

	particlePoolRef.startColor = propertiesOfTheParticle.startColor;

	particlePoolRef.maxLifetime = propertiesOfTheParticle.MaxLifetime;
	particlePoolRef.remainingLifetime = propertiesOfTheParticle.MaxLifetime;

	particlePoolRef.startSize = propertiesOfTheParticle.startsize;

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
