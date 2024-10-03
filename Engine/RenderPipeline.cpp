#include <iostream>
#include <SDL.h>
#include <algorithm>
#include "RenderPipeline.h"
#include "RenderObject.h"
#include "Texture.h"
#include "Sprite.h"
#include "GameEngine.h"
#include "RectValues.h"
#include "glad.h"
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

		if (i == unloadSpriteRef->GetRenderObject())
		{
			i->id = NULL;
			 
			i->layer = NULL;
			i->myTexture = nullptr;
			i->textRectValue.NullifieValues();
			i->screenRectValue.NullifieValues();
			 
			i->timestamp = NULL;
			i->animationSpeed = NULL;
			i->frameWidth = NULL;
			i->frameHeight = NULL;
			i->textureWidth = NULL;
			i->textureHeight = NULL;

			

			renderPipelineObjects.erase(renderPipelineObjects.begin() + increment);

			unloadSpriteRef->DeleteRenderObject();

			delete unloadSpriteRef;

			std::sort(renderPipelineObjects.begin(), renderPipelineObjects.end(), 
				[](RenderObject* obj1, RenderObject* obj2) {return obj1->layer < obj2->layer;});
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

void RenderPipeline::ClearPipeline()
{
	for (RenderObject* i : renderPipelineObjects)
	{
		//SDL_DestroyTexture(i->texture->GetTexture());
		i->id = NULL;
		 
		i->layer = NULL;
		i->myTexture = nullptr;
		i->textRectValue.NullifieValues();
		i->screenRectValue.NullifieValues();
		 
		i->timestamp = NULL;
		i->animationSpeed = NULL;
		i->frameWidth = NULL;
		i->frameHeight = NULL;
		i->textureWidth = NULL;
		i->textureHeight = NULL;
	}
}

RenderPipeline::~RenderPipeline()
{
	ClearPipeline();
	myGameEngine = nullptr;
}
