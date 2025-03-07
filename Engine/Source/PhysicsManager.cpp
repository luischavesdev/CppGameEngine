#include "box2d.h"

#include "PhysicsManager.h"
#include "PhysicsListener.h"
#include "Engine.h"

PhysicsManager::PhysicsManager(GameEngine* gameEngineRef, float PPMRef, float gravityRef, float timeStepRef, int velocityIterationsRef, int positionIterationsRef)
{
	myGameEngine = gameEngineRef;
	PPM = PPMRef;
	gravity = gravityRef;
	timeStep = timeStepRef;
	velocityIterations = velocityIterationsRef;
	positionIterations = positionIterationsRef;
}

void PhysicsManager::InitPhysSim()
{
	//Setting phys world
	b2Vec2 gravityVec = { 0.0f, gravity };
	physWorld = new b2World(gravityVec);

	//Setting world listener
	myListener = new PhysicsListener();
	physWorld->SetContactListener(myListener);

	isRunning = true;
}

void PhysicsManager::RunStep()
{
	physWorld->Step(timeStep, velocityIterations, positionIterations);	
}

b2World* PhysicsManager::GetPhysWorld()
{
	if (physWorld != nullptr)
	{
		return physWorld;
	}
}

float PhysicsManager::PixelsToMeters(float pixels)
{
	return pixels / PPM;
}

float PhysicsManager::MetersToPixels(float meters)
{
	return meters * PPM;
}

PhysicsManager::~PhysicsManager()
{
	delete physWorld;
	delete myListener;

	physWorld = nullptr;
	myListener = nullptr;
	myGameEngine = nullptr;
}
