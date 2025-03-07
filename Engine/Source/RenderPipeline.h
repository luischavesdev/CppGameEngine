#pragma once
#include <vector>

class RenderPipeline 
{
private:
	class GameEngine* myGameEngine = nullptr;
	std::vector<class Sprite*> objectsToUnload{};
	std::vector<class RenderObject*> renderPipelineObjects{};
	

public:
	RenderPipeline(GameEngine* gameEngineRef);

	void LoadIntoRenderPipeline(RenderObject* rendObjRef);
	void AddToUnloadList(Sprite* spriteRef);
	void UnloadFromRenderPipeline(Sprite* unloadSpriteRef);

	void PlayRenderPipeline(float deltaTime);

	void ClearRenderPipeline();

	// Exceptional use for render objects that exist without a sprite. Not elegant code.
	void UnloadRenderObject(RenderObject* rendObjRef);

	~RenderPipeline();
};
