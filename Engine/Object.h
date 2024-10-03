#pragma once
#include <string>
#include "Vector2.h"

class Object 
{
private:
	Vector2 myLocation;

	std::string objectName;

	class GameEngine* myGameEngine;

	class Level* myLevel;

	int id;

public:
	Object(std::string objectNameRef, GameEngine* gameEngineRef, int idRef);

	Object(float xPos, float yPos, std::string objectNameRef, GameEngine* gameEngineRef, int idRef);

	virtual void SetLocation(float newX,  float newY);

	GameEngine* GetGameEngine();

	void SetObjectToDestroy();

	inline Vector2 GetLocation() { return myLocation; };

	inline std::string GetName() { return objectName; };

	inline int GetId() { return id; };

	Level* GetLevelRef();

	void SetLevelRef(Level* levelRef);

	virtual void Update();

	virtual void Start();

	~Object();
};