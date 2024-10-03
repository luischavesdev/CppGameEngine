#pragma once
#include "Sprite.h"
#include <string>

class Pawn : public Sprite
{
private:
	class InputManager* myInputManager;

public:
	Pawn(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef);

	InputManager* GetInputManager();

	void OnCollision(Sprite* colliderSpriteRef) override;

	void Update() override;

	void Start() override;

	~Pawn();
};