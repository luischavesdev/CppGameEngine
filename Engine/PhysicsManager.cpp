#include "PhysicsManager.h"
#include "PhysicsListener.h"
#include "GameEngine.h"
#include <box2d/box2d.h>
#include <iostream>

PhysicsManager::PhysicsManager(float PPMRef, GameEngine* gameEngineRef)
{
	PPM = PPMRef;
	if (gameEngineRef != nullptr)
	{
		myGameEngine = gameEngineRef;
	}
}

void PhysicsManager::InitPhysSim(float PPMRef, float gravityRef, float timeStepRef, int velocityIterationsRef, int positionIterationsRef)
{
	//Setting phys world
	gravity = gravityRef;
	b2Vec2 gravityVec = { 0.0f, gravity };
	physWorld = new b2World(gravityVec);

	//Setting world listener
	myListener = new PhysicsListener();
	physWorld->SetContactListener(myListener);

	//Setting phys loop variables
	timeStep = timeStepRef;
	velocityIterations = velocityIterationsRef;
	positionIterations = positionIterationsRef;
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
