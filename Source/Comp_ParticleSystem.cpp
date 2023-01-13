#include "Comp_ParticleSystem.h"

#include "Application.h"
#include "Shaders.h"
#include "ModuleRenderer3D.h"
#include "ParticleEmitter.h"
#include "ImGuiUtils.h"

Comp_ParticleSystem::Comp_ParticleSystem(GameObject* _go) :Component(_go)
{
	this->type = COMP_TYPE::PARTICLE_SYSTEM;
	this->name = "Particle_System";

	app = Application::GetInstance();

	particleShaders = new Shaders("Assets/Shaders/vertexshader_particle.pesh", "Assets/Shaders/fragmentshader_particle.pesh");
	AddParticleEmitter();

	app->renderer3D->particleSystems.push_back(this);

}

Comp_ParticleSystem::~Comp_ParticleSystem()
{

}

void Comp_ParticleSystem::Update()
{
	for each (ParticleEmitter* parrticleemitter in emitters)
	{
		parrticleemitter->Update(app->GetDeltaTime());
	}
	
}

void Comp_ParticleSystem::OnUIController()
{
	if (ImGui::CollapsingHeader("Particle System", ImGuiTreeNodeFlags_DefaultOpen))
	{

	}

}

void Comp_ParticleSystem::Draw()
{
	for each (ParticleEmitter* parrticleemitter in emitters)
	{
		parrticleemitter->Draw(particleShaders);
	}
}

void Comp_ParticleSystem::Play()
{

}

void Comp_ParticleSystem::Stop()
{

}

void Comp_ParticleSystem::AddParticleEmitter()
{
	emitters.push_back(new ParticleEmitter());
}
