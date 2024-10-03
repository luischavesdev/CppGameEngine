#include "Pawn.h"
#include "GameEngine.h"
#include "InputManager.h"

Pawn::Pawn(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef) : Sprite(objectNameRef,
	RenderObjectRef, gameEngineRef, idRef)
{
	myInputManager = gameEngineRef->GetInputManager();
}

InputManager* Pawn::GetInputManager()
{
	if (myInputManager)
	{
		return myInputManager;
	}
}

void Pawn::OnCollision(Sprite* colliderSpriteRef)
{

}

void Pawn::Update()
{

}

void Pawn::Start()
{

}

Pawn::~Pawn()
{
	myInputManager = nullptr;
}
