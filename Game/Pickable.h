#pragma once
#include "Sprite.h"
#include <string>

class Pickable : public Sprite
{
public:
	enum TypeOfPickable { CompanionType = 0, ShieldType, FirepowerType };

private:
	TypeOfPickable myTypeOfPickable;


public:
	Pickable(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, TypeOfPickable typeRef);

	void OnCollision(Sprite* colliderSpriteRef) override;

	void Update() override;

	void Start() override;

	~Pickable();
};