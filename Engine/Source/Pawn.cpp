#include "Pawn.h"
#include "Engine.h"
#include "InputManager.h"

Pawn::Pawn(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef) : Sprite(objectNameRef,
	RenderObjectRef, gameEngineRef, idRef)
{
	myInputManager = gameEngineRef->GetInputManager();
}

void Pawn::Start()
{

}

void Pawn::Update()
{

}

void Pawn::OnCollision(Sprite* colliderSpriteRef)
{

}

InputManager* Pawn::GetInputManager()
{
	if (myInputManager)
	{
		return myInputManager;
	}
}

Pawn::~Pawn()
{
	myInputManager = nullptr;
}
