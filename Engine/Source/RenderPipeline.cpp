#include <algorithm>
#include "SDL.h"
#include "glad.h"

#include "RenderPipeline.h"
#include "RenderObject.h"
#include "Sprite.h"
#include "Engine.h"
#include "Window.h"

RenderPipeline::RenderPipeline(GameEngine* gameEngineRef)
{
	myGameEngine = gameEngineRef;
}

void RenderPipeline::LoadIntoRenderPipeline(RenderObject* rendObjRef)
{
	renderPipelineObjects.push_back(rendObjRef);

	std::sort(renderPipelineObjects.begin(), renderPipelineObjects.end(), 
		[](RenderObject* obj1, RenderObject* obj2) {return obj1->layer < obj2->layer;});
}

void RenderPipeline::AddToUnloadList(Sprite* spriteRef)
{
	if (spriteRef !=nullptr)
	{
		objectsToUnload.push_back(spriteRef);
	}
}

void RenderPipeline::UnloadFromRenderPipeline(Sprite* unloadSpriteRef)
{
	int increment = -1;
	

	for (RenderObject* i : renderPipelineObjects)
	{
		++increment;

		if (i != nullptr)
		{
			if (i == unloadSpriteRef->GetRenderObject())
			{
				i->id = 0;
				i->layer = 0;
				i->myTexture = nullptr;
				i->timestamp = 0;
				i->animationSpeed = 0;

				renderPipelineObjects.erase(renderPipelineObjects.begin() + increment);
				delete unloadSpriteRef;

				std::sort(renderPipelineObjects.begin(), renderPipelineObjects.end(),
					[](RenderObject* obj1, RenderObject* obj2) {return obj1->layer < obj2->layer; });

				break;
			}
		}
	}
}

void RenderPipeline::PlayRenderPipeline(float deltaTime)
{
	if (objectsToUnload.size() > 0)
	{
		for (Sprite* i : objectsToUnload)
		{
			UnloadFromRenderPipeline(i);
		}
		objectsToUnload.clear();
	}

	glClear(GL_COLOR_BUFFER_BIT);

	for (RenderObject* i : renderPipelineObjects)
	{
		if (i->animated == true)
		{
			i->RenderAnimated(myGameEngine->GetShaderProgram(), deltaTime);
		}
		else if (i->tiled == true)
		{
			i->RenderTiled(myGameEngine->GetShaderProgram());
		}
		else
		{
			i->RenderStill(myGameEngine->GetShaderProgram());
		}
	}
	
	SDL_GL_SwapWindow(myGameEngine->GetWindow()->GetSDLWindow());
}

void RenderPipeline::ClearRenderPipeline()
{
	if (renderPipelineObjects.size() > 0)
	{
		for (RenderObject* i : renderPipelineObjects)
		{
			i->id = 0;
			i->layer = 0;
			i->myTexture = nullptr;
			i->timestamp = 0;
			i->animationSpeed = 0;
		}
		renderPipelineObjects.clear();
	}
}

void RenderPipeline::UnloadRenderObject(RenderObject* rendObjRef)
{
	int increment = -1;

	for (RenderObject* i : renderPipelineObjects)
	{
		++increment;

		if (i != nullptr)
		{
			if (i == rendObjRef)
			{
				i->id = 0;
				i->layer = 0;
				i->myTexture = nullptr;
				i->timestamp = 0;
				i->animationSpeed = 0;

				renderPipelineObjects.erase(renderPipelineObjects.begin() + increment);
				delete rendObjRef;

				std::sort(renderPipelineObjects.begin(), renderPipelineObjects.end(),
					[](RenderObject* obj1, RenderObject* obj2) {return obj1->layer < obj2->layer; });

				break;
			}
		}
	}
}

RenderPipeline::~RenderPipeline()
{
	for (RenderObject* i : renderPipelineObjects)
	{
		i->id = 0;
		i->layer = 0;
		i->myTexture = nullptr;
		i->timestamp = 0;
		i->animationSpeed = 0;
	}

	myGameEngine = nullptr;
}
