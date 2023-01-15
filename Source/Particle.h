#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "MathGeoLib/include/Math/MathAll.h"

struct ParticleProperties 
{
	//Position of the particle
	float3 position;
	//Speed of the particle
	float3 velocity;
	float3 acceleration;
	//Starting and Ending color of the particle
	float4 startColor, endColor;
	float startsize;
	float endsize;
	float MaxLifetime = 1.0f;
};


struct Particle
{

	Particle();

	~Particle();
	//Position of the particle
	float3 position;
	//Speed of the particle
	float3 velocity;
	//Starting color of the particle
	float4 startColor;
	//Ending color of the particle
	float4 endColor;
	//how many seconds remain of the particle to be dead
	float remainingLifetime;
	//Max Life time of the particle
	float maxLifetime;
	//initial size of the particle
	float startSize;
	//End size of the particle
	float endSize;
	//particle's Euler rotation in degrees.
	float rotation;
	//Angular velocity of the particle
	float rotationSpeed;

	//OPTIONAL?
	float3 acceleration;

	bool Active;

};

#endif // !__PARTICLE_H__

