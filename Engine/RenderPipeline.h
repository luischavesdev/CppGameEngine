#pragma once
#include <vector>

class RenderPipeline 
{
private:
	std::vector<class RenderObject*> renderPipelineObjects{};
	
	class GameEngine* myGameEngine;

	std::vector<class Sprite*> objectsToUnload{};

public:
	RenderPipeline(GameEngine* gameEngineRef);

	void LoadIntoRenderPipeline(RenderObject* rendObjRef);

	void AddToUnloadList(Sprite* spriteRef);

	void UnloadFromRenderPipeline(Sprite* unloadSpriteRef);

	void PlayRenderPipeline(float deltaTime);

	void ClearPipeline();

	~RenderPipeline();
};