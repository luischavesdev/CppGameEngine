#include <iostream>
#include "Sprite.h"
#include "RenderObject.h"
#include "Collider.h"
#include "GameEngine.h"
#include "Texture.h"
#include "RenderPipeline.h"

Sprite::Sprite(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef) : 
	Object(objectNameRef, gameEngineRef, idRef)
{
	myRenderObject = RenderObjectRef;
	hasRenderObj = true;
}

RenderObject* Sprite::GetRenderObject()
{
	if (myRenderObject != nullptr)
	{
		return myRenderObject;
	}
}

Collider* Sprite::GetCollider()
{
	if (myCollider != nullptr)
	{
		return myCollider;
	}
}

void Sprite::SetCollider(Collider* colliderRef)
{
	myCollider = colliderRef;
}

void Sprite::SetParallax(bool isParlaxRef, int paralaxLayerRef, Vector2 paralaxSpeedRef)
{
	isParalax = isParlaxRef;
	paralaxLayer = paralaxLayerRef;
	paralaxSpeed = paralaxSpeedRef;
}

void Sprite::SetLocation(float newX, float newY)
{
	Object::SetLocation(newX, newY);
	myRenderObject->SetOffsets(GetLocation().x, GetLocation().y);
}

void Sprite::SetRotation(float angle)
{
	myRenderObject->SetRotation(angle);
}

void Sprite::OnCollision(Sprite* colliderSpriteRef)
{

}

void Sprite::Update()
{
	if (isParalax)
	{
		if (paralaxLayer == 0)
		{
			SetLocation(GetLocation().x - 1.0f * paralaxSpeed.x, GetLocation().y - 1.0f * paralaxSpeed.y);

			if (GetLocation().y <= -myRenderObject->textHeight)
			{
				SetLocation(GetLocation().x, 0);
			}

			if (GetLocation().x <= -myRenderObject->textWidth)
			{
				SetLocation(0, GetLocation().y);
			}
		}

		if (paralaxLayer == 1)
		{
			if (GetRenderObject()->currentColumn != 2)
			{
				GetRenderObject()->SkipToFrame(4, 2);
			}

			SetLocation(100.0f, GetLocation().y - paralaxSpeed.y);

			if (GetLocation().y < -400.0f)
			{
				SetLocation(GetLocation().x, 400.0f);
			}
		}
	}
}

void Sprite::Start()
{

}

void Sprite::DeleteRenderObject()
{
	if (myRenderObject != nullptr)
	{
		delete myRenderObject;
		hasRenderObj = false;
	}
}

Sprite::~Sprite()
{
	if (hasRenderObj == true)
	{
		delete myRenderObject;
	}
	delete myCollider;
}
