#ifndef __COMP_PARTICLESYSTEM_H__
#define __COMP_PARTICLESYSTEM_H__

#include "Component.h"
#include <vector>

class ParticleEmitter;
class Shaders;
class Application;

class Comp_ParticleSystem :
    public Component
{

public:

	Comp_ParticleSystem(GameObject* _go);
	~Comp_ParticleSystem();

	void Update() override;

	void OnUIController() override;

	void Draw();

	void Play();
	void Stop();

	void AddParticleEmitter();

private:

	bool systemActive;
	//emitter vector
	std::vector<ParticleEmitter*> emitters;

	bool looping = false;
	float maxDuration = 0.0f;

	Application* app;

	Shaders* particleShaders;

	//Timer insert

};

#endif // !__COMP_PARTICLESYSTEM_H__