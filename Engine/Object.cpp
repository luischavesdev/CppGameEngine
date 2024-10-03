#include <iostream>
#include "Object.h"
#include "Level.h"
#include "GameEngine.h"

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

void Object::SetLocation(float newX, float newY)
{
	myLocation.x = newX;
	myLocation.y = newY;
}

GameEngine* Object::GetGameEngine()
{
	if (myGameEngine)
	{
		return myGameEngine;
	}
}

void Object::SetObjectToDestroy()
{
	myGameEngine->GetCurrentLevel()->AddObjectToDestroy(this);
}

Level* Object::GetLevelRef()
{
	if (myLevel)
	{
		return myLevel;
	}
}

void Object::SetLevelRef(Level* levelRef)
{
	if (levelRef)
	{
		myLevel = levelRef;
	}
}

void Object::Update()
{

}

void Object::Start()
{

}

Object::~Object()
{
	myLevel = nullptr;
	myGameEngine = nullptr;
}
