#pragma once
#include <string>
#include "Object.h"
#include "Vector2.h"

class Sprite : public Object
{
private:
	class RenderObject* myRenderObject = nullptr;
	class Collider* myCollider = nullptr;

	bool isParalax = false;
	int paralaxLayer = 0;
	Vector2 paralaxSpeed = Vector2(0,0);

	bool hasRenderObj;

public:
	Sprite(std::string objectNameRef, RenderObject* RenderObjectRef, GameEngine* gameEngineRef, int idRef);

	RenderObject* GetRenderObject();

	Collider* GetCollider();

	void SetCollider(Collider* colliderRef);

	void SetParallax(bool isParlaxRef, int paralaxLayerRef, Vector2 paralaxSpeedRef);

	void SetLocation(float newX, float newY) override;

	void SetRotation(float angle);

	virtual void OnCollision(Sprite* colliderSpriteRef);

	void Update() override;

	void Start() override;

	void DeleteRenderObject();

	~Sprite();
};
