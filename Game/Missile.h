#pragma once
#include "Sprite.h"
#include <string>

class Missile : public Sprite
{
private:
	float speed;
	float lifeCounter;
	float lifetime;
	int firepower;
	int damage;
	bool setToDisable = false;
	bool isDisabled = false;

	class Texture* explosionTexture = nullptr;

public:
	Missile(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float speedRef, 
		int firepowerRef, Texture* explosionTextRef);

	void OnCollision(Sprite* colliderSpriteRef) override;

	void Update() override;

	void Start() override;

	~Missile();
};