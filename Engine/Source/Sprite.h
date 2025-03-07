#pragma once
#include "Object.h"

class Sprite : public Object
{
private:
	class RenderObject* myRenderObject = nullptr;
	class Collider* myCollider = nullptr;

	bool isParalax = false;
	int paralaxLayer = 0;
	Vector2 paralaxSpeed;


public:
	Sprite(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef);

	void Start() override;
	void Update() override;

	virtual void OnCollision(Sprite* colliderSpriteRef);

	RenderObject* GetRenderObject();
	Collider* GetCollider();

	void SetCollider(Collider* colliderRef);
	void SetParallax(bool isParlaxRef, int paralaxLayerRef, Vector2 paralaxSpeedRef);
	void SetLocation(float newX, float newY) override;
	void SetRotation(float angle);

	~Sprite();
};
