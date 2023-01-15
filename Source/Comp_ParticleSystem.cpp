#include "Comp_ParticleSystem.h"

#include "Application.h"
#include "Shaders.h"
#include "ModuleRenderer3D.h"
#include "Comp_Transform.h"
#include "Comp_BillBoarding.h"
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
	
	RELEASE(particleShaders);
	
	for (int i = 0; i < emitters.size(); i++)
	{
		RELEASE(emitters[i]);
	}

	emitters.clear();

}

void Comp_ParticleSystem::Update()
{
	//DO WE REALLY NEED A VECTOR OF EMITTERS IN A PARTICLE SYSTEM?
	for each (ParticleEmitter* parrticleemitter in emitters)
	{
		parrticleemitter->AttachEmitterOnGameObject(comp_owner->GetComponent<Comp_Transform>());
		parrticleemitter->Update(app->GetDeltaTime());
	}
	
}

void Comp_ParticleSystem::OnUIController()
{
	if (ImGui::CollapsingHeader("Particle System", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Separator();
		ImGui::Text("Particle Settings:");
		ImGui::Separator();

		//CHANGE THIS IN ORDER TO HANDLE MULTIPLE EMITTERS IN ONE PARTICLE SYSTEM
		ImGui::DragFloat3("Velocity", emitters[0]->propertiesOfTheParticle.velocity.ptr(), 0.1f,0.0f,1000.0f);
		ImGui::DragFloat3("Acceleration", emitters[0]->propertiesOfTheParticle.acceleration.ptr(), 0.1f, 0.0f, 1000.0f);

		ImGui::ColorEdit4("Start Color ", emitters[0]->propertiesOfTheParticle.startColor.ptr());
		ImGui::ColorEdit4("End Color ", emitters[0]->propertiesOfTheParticle.endColor.ptr());

		ImGui::DragFloat("Life Time ", &emitters[0]->propertiesOfTheParticle.MaxLifetime, 0.1f, 0.1f, 1000.0f);

		ImGui::DragFloat("Start Size ", &emitters[0]->propertiesOfTheParticle.startsize, 0.1f, 0.1f, 50.0f);
		ImGui::DragFloat("End Size ", &emitters[0]->propertiesOfTheParticle.endsize, 0.1f, 0.1f, 50.0f);

	}

}

void Comp_ParticleSystem::Draw()
{
	if (comp_owner->GetComponent<Comp_BillBoarding>() == nullptr)
	{
		comp_owner->AddComponent(COMP_TYPE::BILLBOARD);
	}
		

	for each (ParticleEmitter* parrticleemitter in emitters)
	{
		parrticleemitter->Draw(particleShaders, comp_owner->GetComponent<Comp_BillBoarding>()->GetBBRotation());
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
	emitters.push_back(new ParticleEmitter(TYPES_OF_PARTICLES::SMOKE));
}
