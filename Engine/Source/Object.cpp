#include "Object.h"
#include "Level.h"
#include "Engine.h"

Object::Object(std::string objectNameRef, GameEngine* gameEngineRef, int idRef)
{
	myLocation.x = 0;
	myLocation.y = 0;
	objectName = objectNameRef;
	myGameEngine = gameEngineRef;
	id = idRef;
}

Object::Object(float xPos, float yPos, std::string objectNameRef, GameEngine* gameEngineRef, int idRef)
{
	myLocation.x = xPos;
	myLocation.y = yPos;
	objectName = objectNameRef;
	myGameEngine = gameEngineRef;
	id = idRef;
}

void Object::Start()
{

}

void Object::Update()
{

}

// --- || Getters || ---

GameEngine* Object::GetGameEngine()
{
	if (myGameEngine)
	{
		return myGameEngine;
	}
}

Level* Object::GetLevelRef()
{
	if (myLevel)
	{
		return myLevel;
	}
}

// --- || Setters || ---

void Object::SetLocation(float newX, float newY)
{
	myLocation.x = newX;
	myLocation.y = newY;
}

void Object::SetLevelRef(Level* levelRef)
{
	if (levelRef)
	{
		myLevel = levelRef;
	}
}

void Object::SetObjectToDestroy()
{
	myGameEngine->GetCurrentLevel()->AddObjectToDestroy(this);
}

Object::~Object()
{
	myLevel = nullptr;
	myGameEngine = nullptr;
}
