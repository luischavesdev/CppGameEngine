#pragma once
#include "Sprite.h"

class Pawn : public Sprite
{
private:
	class InputManager* myInputManager = nullptr;


public:
	Pawn(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef);

	void Start() override;
	void Update() override;

	void OnCollision(Sprite* colliderSpriteRef) override;

	InputManager* GetInputManager();

	~Pawn();
};
