#include "Level.h"
#include "Object.h"
#include "Sprite.h"
#include "Engine.h"
#include "RenderPipeline.h"

Level::Level(std::string levelNameRef, GameEngine* engineRef)
{
	levelName = levelNameRef;
	myGameEngine = engineRef;
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

void Level::Update()
{
	if (objectsInBuffer.size() > 0)
	{
		for (Object* i : objectsInBuffer)
		{
			objectsInLevel.push_back(i);
			i->SetLevelRef(this);
			i->Start();

			Sprite* tempSprite = dynamic_cast<Sprite*>(i);
			if (tempSprite != nullptr)
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

			Sprite* tempSprite = dynamic_cast<Sprite*>(i);
			if (tempSprite != nullptr)
			{
				myGameEngine->GetRenderPipeline()->AddToUnloadList(tempSprite);
			}
			else
			{
				delete i;
				i = nullptr;
			}
		}
		objectsToDestroy.clear();
	}
}

std::vector<class Object*> Level::GetObjectsInLevel()
{
	if (objectsInLevel.size() > 0)
	{
		return objectsInLevel;
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
