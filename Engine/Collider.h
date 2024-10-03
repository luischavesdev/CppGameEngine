#pragma once
#include <vector>

class Collider 
{
public:
	enum ColliderType { Static, Kinematic, Dynamic };

	struct Position 
	{
		float x;
		float y;
	};
	
private:
	ColliderType collType;
	float position[2];
	float collSize[2];
	class b2Body* myBody = nullptr;
	bool isSensor;

	class b2World* physWorld = nullptr;
	class PhysicsManager* myPhysManager = nullptr;
	class Object* myObject = nullptr;
	

public:
	Collider(ColliderType typeRef, float positionRef[2], float sizeRef[2], class PhysicsManager* physManagerRef,
		bool isSensorRef, class Object* objectRef);

	inline ColliderType GetColliderType() { return collType; };

	void SetLocation(float xPos, float yPos);

	void SetSensor(bool trueFalse);

	void SetVelocity(float xVel, float yVel);

	b2Body* GetBody();

	Position GetPosition();

	~Collider();
};