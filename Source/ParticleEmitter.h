#ifndef __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

#include "Particle.h"
#include "Mesh.h"
#include "Algorithm/Random/LCG.h"

class Comp_Transform;
class Shaders;
class Application;

class ParticleEmitter
{
public:
	ParticleEmitter();

	~ParticleEmitter();

	void Update(float dt);

	void Draw(Shaders* shader);

	void EmitParticles(ParticleProperties& partprops);

	void SettingUpParticlePool(Particle& particlePoolRef);

	void SetParticlePoolSize(uint size);

	int SearchNotActiveParticle();

	void InitBuffers();

	void SetData(const Vertex* vertices, const uint numvertices, const GLuint* indices, const uint numindices);

private:

	Application* app;

	std::string name;

	float3 position;

	float currentdelay;
	float maxdelay;

	//particles size dynamic?
	float minParticlesSize;
	float maxParticlesSize;

	//particles lifetime dynamic?
	float minParticlesLifetime;
	float maxParticlesLifetime;

	std::vector<Particle> particlesInEmitter;

	ParticleProperties propertiesOfTheParticle;

	int lastActiveParticle = 0;

	int numOfParticlesToRespawn = 0;

	//Add Particles efects;

	Comp_Transform* particlesystemGO = nullptr;

	//Open GL

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	uint numvertices;
	uint numindices;

	GLuint texture;

	//MathGeoLIB RANDOM
	LCG random;

};

#endif // !__PARTICLE_EMITTER_H__