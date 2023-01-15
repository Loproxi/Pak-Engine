#pragma once

#include "Globals.h"

struct GameClock
{
	static void Play();
	static void Stop();

	static void Pause();
	static void Unpause();

	static void Tick(float dt);
	static void Update(float dt);

	static bool IsStopped();
	static bool IsPaused();

	static float GetFrameCount();
	static float GetTimeScale();
	static float GetGameTimeSinceStart();
	static float GetGameTimeDeltaTime();
	static float GetDeltaTime();
private:
	
	static bool stop;
	static bool pause;
	
	static float realTimeSinceStart;
	static float realTimeDeltaTime;
	static float deltaTime;

	static float frameCount;
	static float timeScale;
};