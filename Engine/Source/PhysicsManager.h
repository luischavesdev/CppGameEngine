#pragma once

class PhysicsManager
{
private:
	class GameEngine* myGameEngine = nullptr;
	float PPM; //Pixels Per Meter Ratio
	float gravity;
	class b2World* physWorld = nullptr;
	class PhysicsListener* myListener = nullptr;

	//Engine loop vars
	float timeStep;
	int velocityIterations;
	int positionIterations;
	bool isRunning = false;


public:
	PhysicsManager(GameEngine* gameEngineRef, float PPMRef, float gravityRef, float timeStepRef, int velocityIterationsRef, int positionIterationsRef);

	void InitPhysSim();
	void RunStep();

	b2World* GetPhysWorld();
	inline float GetPPM() { return PPM; };

	float PixelsToMeters(float pixels);
	float MetersToPixels(float meters);

	~PhysicsManager();
};
