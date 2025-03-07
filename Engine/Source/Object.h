#pragma once
#include <string>
#include "VectorCustom.h"

class Object 
{
private:
	std::string objectName;
	Vector2 myLocation;
	int id;
	
	class GameEngine* myGameEngine = nullptr;
	class Level* myLevel = nullptr;

	
public:
	Object(std::string objectNameRef, GameEngine* gameEngineRef, int idRef);
	Object(float xPos, float yPos, std::string objectNameRef, GameEngine* gameEngineRef, int idRef);

	virtual void Start();
	virtual void Update();

	inline std::string GetName() { return objectName; };
	inline Vector2 GetLocation() { return myLocation; };
	inline int GetId() { return id; };
	GameEngine* GetGameEngine();
	Level* GetLevelRef();
	
	virtual void SetLocation(float newX,  float newY);
	void SetLevelRef(Level* levelRef);

	void SetObjectToDestroy();

	virtual ~Object();
};
