#include "Level.h"
#include "Object.h"
#include "Sprite.h"
#include "GameEngine.h"
#include "RenderObject.h"
#include "RenderPipeline.h"
#include <iostream>

Level::Level(std::string levelNameRef, GameEngine* engineRef)
{
	levelName = levelNameRef;
	myGameEngine = engineRef;
}

void Level::AddObject(Object* objectRef)
{
	if (objectRef != nullptr)
	{
		objectsInLevel.push_back(objectRef);
		objectRef->SetLevelRef(this);
	}
}

void Level::AddObjectToBuffer(Object* objectRef)
{
	if (objectRef != nullptr)
	{
		objectsInBuffer.push_back(objectRef);
	}
}

void Level::AddObjectToDestroy(Object* objectRef)
{
	if (objectRef != nullptr)
	{
		objectsToDestroy.push_back(objectRef);
	}
}

void Level::RemoveObjectFromLevel(Object* objectRef)
{
	int increment = -1;

	for (Object* i : objectsInLevel)
	{
		++increment;

		if (i == objectRef)
		{
			objectsInLevel.erase(objectsInLevel.begin() + increment);
		}
	}
}

std::vector<class Object*> Level::GetObjectsInLevel()
{
	if (objectsInLevel.size() > 0)
	{
		return objectsInLevel;
	}
}

void Level::Update()
{
	if (objectsInBuffer.size() > 0)
	{
		for (Object* i : objectsInBuffer)
		{
			AddObject(i);

			Sprite* tempSprite = static_cast<Sprite*>(i);
			if (tempSprite)
			{
				myGameEngine->GetRenderPipeline()->LoadIntoRenderPipeline(tempSprite->GetRenderObject());
			}
		}
		objectsInBuffer.clear();
	}

	if (objectsInLevel.size() > 0)
	{
		for (Object* i : objectsInLevel)
		{
			i->Update();
		}
	}

	if (objectsToDestroy.size() > 0)
	{
		for (Object* i : objectsToDestroy)
		{
			RemoveObjectFromLevel(i);

			Sprite* tempSprite = static_cast<Sprite*>(i);
			if (tempSprite)
			{
				myGameEngine->GetRenderPipeline()->AddToUnloadList(tempSprite);
			}
		}
		objectsToDestroy.clear();
	}
}

Level::~Level()
{
	if (objectsInLevel.size() > 0)
	{
		for (Object* i : objectsInLevel)
		{
			i = nullptr;
		}
	}

	if (objectsInBuffer.size() > 0)
	{
		for (Object* i : objectsInBuffer)
		{
			i = nullptr;
		}
	}

	if (objectsToDestroy.size() > 0)
	{
		for (Object* i : objectsToDestroy)
		{
			i = nullptr;
		}
	}

	myGameEngine = nullptr;
}
