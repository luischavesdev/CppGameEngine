#pragma once
#include "VectorCustom.h"

class Collider 
{
public:
	enum ColliderType { Static, Kinematic, Dynamic };


private:
	ColliderType collType;
	Vector2 collSize;
	class b2Body* myBody = nullptr;
	bool isSensor;

	class b2World* physWorld = nullptr;
	class PhysicsManager* myPhysManager = nullptr;
	class Object* myObject = nullptr;
	

public:
	Collider(ColliderType typeRef, Vector2 positionRef, Vector2 sizeRef, class PhysicsManager* physManagerRef,
		bool isSensorRef, class Object* objectRef);

	b2Body* GetBody();
	inline ColliderType GetColliderType() { return collType; };
	Vector2 GetPosition();
	
	void SetLocation(float xPos, float yPos);
	void SetVelocity(float xVel, float yVel);
	void SetSensor(bool trueFalse);

	~Collider();
};
