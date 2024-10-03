#pragma once
#include <vector>
#include <string>

class Level 
{
private:
	std::string levelName;

	class GameEngine* myGameEngine;

	std::vector<class Object*> objectsInLevel{};

	std::vector<class Object*> objectsInBuffer{};

	std::vector<class Object*> objectsToDestroy{};


public:
	Level(std::string levelNameRef, GameEngine* engineRef);

	void AddObject(Object* objectRef);

	void AddObjectToBuffer(Object* objectRef);

	void AddObjectToDestroy(Object* objectRef);

	void RemoveObjectFromLevel(Object* objectRef);

	std::vector<Object*> GetObjectsInLevel();

	inline std::string GetName() { return levelName; };

	void Update();

	~Level();


};