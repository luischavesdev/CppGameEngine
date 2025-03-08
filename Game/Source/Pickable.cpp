#include "Pickable.h"
#include "Engine.h"
#include "PhysicsManager.h"
#include "Collider.h"
#include "RenderObject.h"
#include "Spaceship.h"
#include "Companion.h"
#include "AudioManager.h";

Pickable::Pickable(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, TypeOfPickable typeRef) : 
	Sprite(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	myTypeOfPickable = typeRef;
}

void Pickable::Start()
{
	GetCollider()->SetVelocity(-10.0f, 0.0f);
}

void Pickable::Update()
{
	SetLocation(GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().x),
		GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().y));

	if (myTypeOfPickable == TypeOfPickable::CompanionType)
	{
		if (GetRenderObject()->currentColumn >= 4 && GetRenderObject()->currentLine >= 4)
		{
			GetRenderObject()->SkipToFrame(1, 1);
		}
	}
}

void Pickable::OnCollision(Sprite* colliderSpriteRef)
{
	if (colliderSpriteRef != nullptr)
	{
		Spaceship* spaceshipRef = dynamic_cast<Spaceship*>(colliderSpriteRef);

		if (spaceshipRef != nullptr)
		{
			GetGameEngine()->GetAudioManager()->PlaySound(0, "data/audio/PowerupAcquired.wav", 60);
			switch (myTypeOfPickable)
			{
			case CompanionType:
				spaceshipRef->AddCompanion();
				break;

			case ShieldType:
				spaceshipRef->ChangeLife(1.0f);
				break;

			case FirepowerType:
				spaceshipRef->UpgradeFirepower();
				break;
			}

			SetObjectToDestroy();
		}
		else
		{
			Companion* myCompanionRef = dynamic_cast<Companion*>(colliderSpriteRef);

			if (myCompanionRef != nullptr)
			{
				GetGameEngine()->GetAudioManager()->PlaySound(0, "data/audio/PowerupAcquired.wav", 60);
				switch (myTypeOfPickable)
				{
				case CompanionType:
					break;

				case ShieldType:
					myCompanionRef->ChangeLife(1.0f);
					SetObjectToDestroy();
					break;

				case FirepowerType:
					myCompanionRef->UpgradeFirepower();
					SetObjectToDestroy();
					break;
				}
			}
		}
	}
}

Pickable::~Pickable()
{
	
}
