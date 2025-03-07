#include "PhysicsListener.h"
#include "Sprite.h"

PhysicsListener::PhysicsListener()
{

}

void PhysicsListener::BeginContact(b2Contact* contact)
{
	void* userDataA = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	void* userDataB = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (userDataA && userDataB)
	{
		Sprite* objectRefA = static_cast<Sprite*>(userDataA);
		Sprite* objectRefB = static_cast<Sprite*>(userDataB);

		if (objectRefA && objectRefB)
		{
			objectRefA->OnCollision(objectRefB);
			objectRefB->OnCollision(objectRefA);
		}
	}
}

PhysicsListener::~PhysicsListener()
{

}
