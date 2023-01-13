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
	SetParticlePoolSize(1000);

	//INIT BUFFERS

	InitBuffers();
}

void ParticleEmitter::InitBuffers()
{

	Vertex quadvertices[]
	{
		//POS               //Normals                               //Texture Coords
		Vertex(float3{-0.5f, -0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{0.0f, 0.0f}),
		Vertex(float3{0.5f, -0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{0.0f, 0.0f}),
		Vertex(float3{0.5f,  0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{0.0f, 0.0f}),
		Vertex(float3{-0.5f,  0.5f, 0.0f},float3{0.0f, 0.0f, 0.0f}, float2{0.0f, 0.0f}),
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(quadvertices), quadvertices, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoords));

	uint quadindices[]
	{
		0,1,2,2,3,0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadindices), quadindices, GL_STATIC_DRAW);

	texture = Application::GetInstance()->renderer3D->textures.at(0)->textID;

	glBindVertexArray(0);

}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::Update(float dt)
{

	for each (Particle& particleInPool in particlesInEmitter)
	{
		//No Active means it is available to be remplace
		if (particleInPool.Active == false)
		{
			continue;
		}
		//No remainingLifetime means it is dead therefore, is not active
		if (particleInPool.remainingLifetime < 0.0f)
		{
			particleInPool.Active = false;
			continue;
		}
		else
		{

			//Compute all the calculus needed to move the particles

			//Remaining life minus dt
			particleInPool.remainingLifetime -= dt;

			
			if (particleInPool.remainingLifetime < 0.0f)
			{
				// velocity = acceleration * dt
				particleInPool.velocity = particleInPool.acceleration * dt;

				// pos += velocity * dt
				particleInPool.position += particleInPool.velocity * dt;

				
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

	for each (Particle & particleInPool in particlesInEmitter)
	{
		float3 zAxis = { 0.0f,0.0f,1.0f };
		float partRotationInRad = DegToRad(particleInPool.rotation);
		Quat rotation = Quat::RotateAxisAngle(zAxis, partRotationInRad);
		float4x4 transform;
		//Gather pos & rotation &scale
		transform.FromTRS(particleInPool.position, rotation, {particleInPool.startSize,particleInPool.startSize ,1.0f}).Transpose();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
	
}

void ParticleEmitter::SetParticlePoolSize(uint size)
{
	particlesInEmitter.resize(size);
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

void ParticleEmitter::SettingUpParticlePool(Particle& particlePoolRef,ParticleProperties& partprops)
{
	
	particlePoolRef.position = partprops.position;
	particlePoolRef.Active = true;

	particlePoolRef.velocity = partprops.velocity;
	particlePoolRef.acceleration = partprops.acceleration;

	particlePoolRef.startColor = partprops.startColor;

	particlePoolRef.maxLifetime = partprops.MaxLifetime;
	particlePoolRef.remainingLifetime = partprops.MaxLifetime;

	particlePoolRef.startSize = partprops.startsize;

}


