#include "Drone.h"
#include "Engine.h"
#include "Collider.h"
#include "PhysicsManager.h"

Drone::Drone(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float velRef) : 
	Enemy(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	myVelocity = velRef;
}

void Drone::Start()
{
	SetLocation(GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().x),
		GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().y));
}

void Drone::Update()
{
	timer += 0.1f;

	float x = (GetLocation().x - myVelocity) - (GetLocation().x);
	float y = (GetLocation().y + sin(timer) * 2) - (GetLocation().y);

	GetCollider()->SetVelocity(x * 10, y * 10);

	SetLocation(GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().x),
		GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().y));

	

	if (timer >= lifeTime)
	{
		SetObjectToDestroy();
	}
}

void Drone::Die()
{
	SetObjectToDestroy();
}

Drone::~Drone()
{

}
