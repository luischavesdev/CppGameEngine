#include "box2d.h"

#include "Collider.h"
#include "PhysicsManager.h"

Collider::Collider(ColliderType typeRef, Vector2 positionRef, Vector2 sizeRef, PhysicsManager* physManagerRef,
	bool isSensorRef, Object* objectRef)
{
	//Set local vars
	myPhysManager = physManagerRef;
	physWorld = myPhysManager->GetPhysWorld();
	collType = typeRef;

	collSize.x = myPhysManager->PixelsToMeters(sizeRef.x / 2); //Setting a box shape takes half the width and height
	collSize.y = myPhysManager->PixelsToMeters(sizeRef.y / 2);

	isSensor = isSensorRef;

	if (objectRef != nullptr)
	{
		myObject = objectRef;
	}

	b2BodyDef bodyDef;
	switch (typeRef) 
	{
		case Static:
			bodyDef.type = b2_staticBody;
			break;
		case Kinematic:
			bodyDef.type = b2_kinematicBody;
			break;
		case Dynamic:
			bodyDef.type = b2_dynamicBody;
			break;
	}

	//Create body
	bodyDef.position.Set(myPhysManager->PixelsToMeters(positionRef.x), myPhysManager->PixelsToMeters(positionRef.y));
	bodyDef.gravityScale = 1.0f;
	bodyDef.userData.pointer = (uintptr_t)myObject;
	myBody = physWorld->CreateBody(&bodyDef);
	
	//Create shape
	b2PolygonShape colliderShape;
	colliderShape.SetAsBox(collSize.x, collSize.y); //Center of the box is the same as the position set for the body

	//Create and set ficture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &colliderShape;
	fixtureDef.density = 1.0f;
	fixtureDef.isSensor = isSensor;
	myBody->CreateFixture(&fixtureDef);
	
}

// --- || Getters || ---

b2Body* Collider::GetBody()
{
	if (myBody != nullptr)
	{
		return myBody;
	}
}

Vector2 Collider::GetPosition()
{
	Vector2 currentPosition;
	currentPosition.x = myBody->GetPosition().x;
	currentPosition.y = myBody->GetPosition().y;

	return currentPosition;
}

// --- || Setters || ---

void Collider::SetLocation(float xPos, float yPos)
{
	b2Vec2 tempLocation;
	tempLocation.x = myPhysManager->PixelsToMeters(xPos);
	tempLocation.y = myPhysManager->PixelsToMeters(yPos);

	myBody->SetTransform(tempLocation, myBody->GetAngle());
}

void Collider::SetVelocity(float xVel, float yVel)
{
	if (collType != Static)
	{
		b2Vec2 tempVec{ xVel, yVel };
		myBody->SetLinearVelocity(tempVec);
	}
}

void Collider::SetSensor(bool trueFalse)
{
	myBody->GetFixtureList()->SetSensor(trueFalse);
}

Collider::~Collider()
{
	physWorld->DestroyBody(myBody);
	physWorld = nullptr;
	myBody = nullptr;
	myObject = nullptr;
}
