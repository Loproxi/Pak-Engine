#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter()
{

	//TODO UPGRADE
	//Compute how many particles are being emited each second and multiply by lifetime of each particle and set that as poolsize
	SetParticlePoolSize(1000);

	//INIT BUFFERS
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

		if (particleInPool.remainingLifetime < 0.0f)
		{
			particleInPool.Active = false;
			continue;
		}
		else
		{

			//Compute all the calculus needed to move the particles

			//Remaining life minus dt

			// velocity = acceleration * dt

			// pos += velocity * dt

		}

	}

}

void ParticleEmitter::Draw(Shaders* shader)
{
	//DRAW WITH THE BUFFERS CREATED AT CONSTRUCTOR
}

void ParticleEmitter::SetParticlePoolSize(uint size)
{
	particlesInEmitter.resize(size);
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


