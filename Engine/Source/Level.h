#pragma once
#include <vector>
#include <string>

class Level 
{
private:
	class GameEngine* myGameEngine = nullptr;
	std::string levelName;
	
	std::vector<class Object*> objectsInLevel{};
	std::vector<class Object*> objectsInBuffer{};
	std::vector<class Object*> objectsToDestroy{};


public:
	Level(std::string levelNameRef, GameEngine* engineRef);

	void AddObjectToBuffer(Object* objectRef);
	void AddObjectToDestroy(Object* objectRef);

	void Update();

	std::vector<Object*> GetObjectsInLevel();
	inline std::string GetName() { return levelName; };

	~Level();


private:
	void RemoveObjectFromLevel(Object* objectRef);
};