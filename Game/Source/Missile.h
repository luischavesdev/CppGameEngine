#pragma once
#include "Sprite.h"

class Missile : public Sprite
{
private:
	float speed;
	float lifeCounter = 0;
	float lifetime = 50;
	int firepower;
	int damage;
	bool setToDisable = false;
	bool isDisabled = false;

	class Texture* explosionTexture = nullptr;


public:
	Missile(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef, float speedRef, 
		int firepowerRef, Texture* explosionTextRef);

	void Start() override;
	void Update() override;

	void OnCollision(Sprite* colliderSpriteRef) override;

	~Missile();
};
