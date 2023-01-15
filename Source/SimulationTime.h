#pragma once

struct SimulationTime
{

public:

	//PLAY
	static void Play();
	//Resume and Pause
	static void ResumeAndPause(bool value);
	//Simulation time reset
	static void Finish();

	//Handles the delta time each frame
	static void Update(float appdt);


public: 
	static float dt;
	static bool playing;
private:

	static int countframesperUpdate;
	static float startSimulationTime;
	static float simulationDeltaTime;
	
	static bool pause;

};
