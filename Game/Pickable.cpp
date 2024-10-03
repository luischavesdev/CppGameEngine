#include <iostream>
#include "Pickable.h"
#include "Level.h"
#include "Collider.h"
#include "GameEngine.h"
#include "PhysicsManager.h"
#include "RenderObject.h"
#include "Spaceship.h"
#include "Texture.h"
#include "Companion.h"

Pickable::Pickable(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, TypeOfPickable typeRef) : 
	Sprite(objectNameRef, RenderObjectRef, gameEngineRef, idRef)
{
	myTypeOfPickable = typeRef;
}

void Pickable::OnCollision(Sprite* colliderSpriteRef)
{
	if (colliderSpriteRef != nullptr)
	{
		Spaceship* spaceshipRef = static_cast<Spaceship*>(colliderSpriteRef);

		if (spaceshipRef->GetName() == "Spaceship")
		{
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
			Companion* myCompanionRef = static_cast<Companion*>(colliderSpriteRef);

			if (myCompanionRef->GetName() == "Companion")
			{
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

void Pickable::Update()
{
	SetLocation(GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().x),
		GetGameEngine()->GetPhysManager()->MetersToPixels(GetCollider()->GetPosition().y));

	if (GetRenderObject()->myTexture->GetTextName() == "graphics/clone.bmp")
	{
		if (GetRenderObject()->currentColumn >= 4 && GetRenderObject()->currentLine >= 4)
		{
			GetRenderObject()->SkipToFrame(1, 1);
		}
	}

}

void Pickable::Start()
{
	GetCollider()->SetVelocity(-10.0f, 0.0f);
}

Pickable::~Pickable()
{
	
}
