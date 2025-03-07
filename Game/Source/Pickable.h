#pragma once
#include "Sprite.h"

class Pickable : public Sprite
{
public:
	enum TypeOfPickable { CompanionType = 0, ShieldType, FirepowerType };

private:
	TypeOfPickable myTypeOfPickable;


public:
	Pickable(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, TypeOfPickable typeRef);

	void Start() override;
	void Update() override;

	void OnCollision(Sprite* colliderSpriteRef) override;

	~Pickable();
};
