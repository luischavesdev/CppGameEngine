#pragma once
#include <vector>

class PhysicsManager
{
private:
	class GameEngine* myGameEngine;
	float PPM; //Pixels Per Meter Ratio
	float gravity;
	class b2World* physWorld;
	class PhysicsListener* myListener;

	//Engine loop vars
	float timeStep;
	int velocityIterations;
	int positionIterations;
	bool isRunning = false;


public:

	PhysicsManager(float PPMRef, GameEngine* gameEngineRef);

	void InitPhysSim(float PPMRef, float gravityRef, float timeStepRef, int velocityIterationsRef, int positionIterationsRef);

	void RunStep();

	b2World* GetPhysWorld();

	inline float GetPPM() { return PPM; };

	float PixelsToMeters(float pixels);

	float MetersToPixels(float meters);

	~PhysicsManager();
};