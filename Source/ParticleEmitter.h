#ifndef __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

#include "Particle.h"
#include "Mesh.h"
#include "Algorithm/Random/LCG.h"
#include "single_include/nlohmann/json.hpp"

using json = nlohmann::json;

enum TYPES_OF_PARTICLES
{
	SMOKE,

};

class Comp_Transform;
class Shaders;
class Application;

class ParticleEmitter
{
public:
	ParticleEmitter(TYPES_OF_PARTICLES typeofpart);

	~ParticleEmitter();

	void Update(float dt);

	void Draw(Shaders* shader, Quat BBrot);

	void InitBuffers();

	void SetData(const Vertex* vertices, const uint numvertices, const GLuint* indices, const uint numindices);

	void EmitParticles(int numOfparticles);

	void SettingUpParticlePool(Particle& particlePoolRef);

	void SetParticlePoolSize(uint size);

	int SearchNotActiveParticle();

	void AttachEmitterOnGameObject(Comp_Transform* comp_owner_transform);

	void SaveParticle(Particle& particleToSave);

private:

	Application* app;

	std::string name;

	float3 position;

	std::vector<Particle> particlesInEmitter;

	ParticleProperties propertiesOfTheParticle;

	int lastActiveParticle = 0;

	int numOfParticlesToRespawn = 0;

	int currentparticle;

	//Add Particles efects;

	//Open GL

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	GLuint texture;

	//MathGeoLIB RANDOM
	LCG random;

	friend class Comp_ParticleSystem;

};

#endif // !__PARTICLE_EMITTER_H__