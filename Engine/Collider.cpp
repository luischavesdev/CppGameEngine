#include "Collider.h"
#include "PhysicsManager.h"
#include <box2d/box2d.h>
#include <iostream>

Collider::Collider(ColliderType typeRef, float positionRef[2], float sizeRef[2], PhysicsManager* physManagerRef,
	bool isSensorRef, Object* objectRef)
{
	//Set local vars
	myPhysManager = physManagerRef;
	physWorld = myPhysManager->GetPhysWorld();
	collType = typeRef;

	position[0] = myPhysManager->PixelsToMeters(positionRef[0]);
	position[1] = myPhysManager->PixelsToMeters(positionRef[1]); 

	collSize[0] = myPhysManager->PixelsToMeters(sizeRef[0] / 2); //Setting a box shape takes half the width and height
	collSize[1] = myPhysManager->PixelsToMeters(sizeRef[1] / 2);

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
	bodyDef.position.Set(position[0], position[1]);
	bodyDef.gravityScale = 1.0f;
	bodyDef.userData.pointer = (uintptr_t)myObject;
	myBody = physWorld->CreateBody(&bodyDef);
	
	//Create shape
	b2PolygonShape colliderShape;
	colliderShape.SetAsBox(collSize[0], collSize[1]); //Center of the box is the same as the position set for the body

	//Create and set ficture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &colliderShape;
	fixtureDef.density = 1.0f;
	fixtureDef.isSensor = isSensor;
	myBody->CreateFixture(&fixtureDef);
	
}

void Collider::SetLocation(float xPos, float yPos)
{
	b2Vec2 tempLocation;
	tempLocation.x = myPhysManager->PixelsToMeters(xPos);
	tempLocation.y = myPhysManager->PixelsToMeters(yPos);

	myBody->SetTransform(tempLocation, myBody->GetAngle());

	
}

void Collider::SetSensor(bool trueFalse)
{
	myBody->GetFixtureList()->SetSensor(trueFalse);
}

void Collider::SetVelocity(float xVel, float yVel)
{
	if (collType != Static)
	{
		b2Vec2 tempVec{ xVel, yVel };
		myBody->SetLinearVelocity(tempVec);
	}
}

b2Body* Collider::GetBody()
{
	if (myBody != nullptr)
	{
		return myBody;
	}
}

Collider::Position Collider::GetPosition()
{
	Position currentPosition;
	currentPosition.x = myBody->GetPosition().x;
	currentPosition.y = myBody->GetPosition().y;
	
	return currentPosition;
}

Collider::~Collider()
{
	physWorld->DestroyBody(myBody);
	physWorld = nullptr;
	myBody = nullptr;
	myObject = nullptr;
}
