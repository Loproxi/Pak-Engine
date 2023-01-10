#ifndef __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

#include "Particle.h"
#include "Mesh.h"

class Comp_Transform;
class Shaders;

class ParticleEmitter
{
public:
	ParticleEmitter();

	~ParticleEmitter();

	void Update(float dt);

	void Draw(Shaders* shader);

	void EmitParticles(ParticleProperties& partprops);

	void SettingUpParticlePool(Particle& particlePoolRef, ParticleProperties& partprops);

	void SetParticlePoolSize(uint size);

private:

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

};

#endif // !__PARTICLE_EMITTER_H__