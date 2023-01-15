#include "SimulationTime.h"

//INIT EVERY STATIC VARIABLE FROM THE SIMULATION TIME STRUCT

int SimulationTime::countframesperUpdate = 0;
float SimulationTime::dt = 0;
float SimulationTime::simulationDeltaTime = 0;
float SimulationTime::startSimulationTime = 0;
bool SimulationTime::playing = false;
bool SimulationTime::pause = false;


//STARTING SIMULATION TIME
void SimulationTime::Play()
{
	playing = true;
	startSimulationTime = simulationDeltaTime;

}

void SimulationTime::ResumeAndPause(bool value)
{

	pause = value;

}

void SimulationTime::Finish()
{
	pause = false;

	playing = false;
	simulationDeltaTime = 0;
	startSimulationTime = 0;
	dt = 0;
	countframesperUpdate = 0;
}

void SimulationTime::Update(float appdt)
{
	if (pause)
	{
		dt = 0; 
		return;
	}
	countframesperUpdate++;
	startSimulationTime += appdt;
	simulationDeltaTime = appdt;
	dt = appdt;
	
}
