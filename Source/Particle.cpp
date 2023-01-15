#include "Particle.h"


Particle::Particle():startColor(0.0f, 1.0f, 0.0f, 1.0f)
{
	this->position = { 0.0f,0.0f,0.0f };

	this->maxLifetime = 0.0f;

	this->acceleration = { 0.0f,0.0f,0.0f };

	this->remainingLifetime = 0.0f;

	this->rotation = 180.0f;

	this->rotationSpeed = 0.0f;

	this->startSize = 5.0f;

	this->velocity = { 0.0f,0.0f,0.0f };

	this->Active = false;
}

Particle::~Particle()
{

	//LOG("PARTICLE DESTROYED")

}
