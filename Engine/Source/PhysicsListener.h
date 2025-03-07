#pragma once
#include "box2d.h"

class PhysicsListener : public b2ContactListener
{
public:
	PhysicsListener();

	void BeginContact(b2Contact* contact);
	
	~PhysicsListener();
};
