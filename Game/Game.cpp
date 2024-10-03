#include <iostream>
#include "GameEngine.h"
#include "Texture.h"
#include "RenderPipeline.h"
#include "RenderObject.h"
#include "RectValues.h"
#include "PhysicsManager.h"
#include "Collider.h"
#include "Level.h"
#include "Object.h"
#include "Rusher.h"
#include "Sprite.h"
#include "Loner.h"
#include "Pawn.h"
#include "Spaceship.h"
#include "Enemy.h"
#include "Pickable.h"
#include "Spawner.h"
#include "AsteroidsStone.h"
#include "AsteroidsMetal.h"
#include "GameUI.h"
#include "AudioManager.h"


int main(int argc, char ** argv)
{
    GameEngine myEngine;
	myEngine.Init("Xenon 2000 Remake", 620, 480, 8);

	float timeStep = 1.0f / 60.0f;
	myEngine.InitPhysSystem(8.0f, 0.0f, timeStep, 6.0f, 2.0f);
	myEngine.CreateControllerInteraction();

	PhysicsManager* myPhysManager = myEngine.GetPhysManager();
	RenderPipeline* myRenderPipeline = myEngine.GetRenderPipeline();
	Level* firstLevel = myEngine.CreateAndAddLevel("FirstLevel");



	//BACKGROUND
	Texture* backgroundTexture = new Texture("graphics/galaxyBackground.jpg", 1, 1);
	RenderObject* backgroundRendObject = new RenderObject(0, 0, backgroundTexture, &myEngine, 1, 2);
	Sprite* background = new Sprite("Background", backgroundRendObject, &myEngine, backgroundRendObject->id);
	background->SetParallax(true, 0, Vector2(3.0f, 0));
    firstLevel->AddObject(background);
	myRenderPipeline->LoadIntoRenderPipeline(backgroundRendObject);


	//ASTEROID
	Texture* bckgrndStonesTexture = new Texture("graphics/backgroundstones.jpg", 1, 1);
	RenderObject* bckgrndStonesRendObj = new RenderObject(1, 1, bckgrndStonesTexture, &myEngine, 1, 2);
	Sprite* bckgrndStones = new Sprite("Aster", bckgrndStonesRendObj, &myEngine, bckgrndStonesRendObj->id);
	bckgrndStones->SetParallax(true, 0, Vector2(3.5f, 0));
	firstLevel->AddObject(bckgrndStones);
	myRenderPipeline->LoadIntoRenderPipeline(bckgrndStonesRendObj);





	//COLLECTIBLES
	Texture* weaponPUText = new Texture("graphics/PUWeapon.bmp", 2, 4);
	RenderObject* weaponPURendObj = new RenderObject(2, 6, weaponPUText, &myEngine, 1.0f, 1, 1);
	float positionWeaponPUCol[2] = { 300.0f, 200.0f };
	float sizeWeaponPUCol[2] = { weaponPUText->GetFrameDimensions().width, weaponPUText->GetFrameDimensions().height };
	Pickable* weaponPUObj = new Pickable("Pickable", weaponPURendObj, &myEngine, weaponPURendObj->id, Pickable::TypeOfPickable::FirepowerType);
	Collider* weaponPUCol = new Collider(Collider::Dynamic, positionWeaponPUCol, sizeWeaponPUCol, myPhysManager, true, weaponPUObj);
	weaponPUObj->SetCollider(weaponPUCol);
	weaponPUObj->Start();
	firstLevel->AddObject(weaponPUObj);
	myRenderPipeline->LoadIntoRenderPipeline(weaponPURendObj);



	RenderObject* weaponPURendObj2 = new RenderObject(2, 6, weaponPUText, &myEngine, 1.0f, 1, 1);
	float positionWeaponPUCol2[2] = { 500.0f, 200.0f };
	float sizeWeaponPUCol2[2] = { weaponPUText->GetFrameDimensions().width, weaponPUText->GetFrameDimensions().height };
	Pickable* weaponPUObj2 = new Pickable("Pickable", weaponPURendObj2, &myEngine, weaponPURendObj2->id, Pickable::TypeOfPickable::FirepowerType);
	Collider* weaponPUCol2 = new Collider(Collider::Dynamic, positionWeaponPUCol2, sizeWeaponPUCol2, myPhysManager, true, weaponPUObj2);
	weaponPUObj2->SetCollider(weaponPUCol2);
	weaponPUObj2->Start();
	firstLevel->AddObject(weaponPUObj2);
	myRenderPipeline->LoadIntoRenderPipeline(weaponPURendObj2);


	RenderObject* weaponPURendObj3 = new RenderObject(2, 6, weaponPUText, &myEngine, 1.0f, 1, 1);
	float positionWeaponPUCol3[2] = { 200.0f, 100.0f };
	float sizeWeaponPUCol3[2] = { weaponPUText->GetFrameDimensions().width, weaponPUText->GetFrameDimensions().height };
	Pickable* weaponPUObj3 = new Pickable("Pickable", weaponPURendObj3, &myEngine, weaponPURendObj3->id, Pickable::TypeOfPickable::FirepowerType);
	Collider* weaponPUCol3 = new Collider(Collider::Dynamic, positionWeaponPUCol3, sizeWeaponPUCol3, myPhysManager, true, weaponPUObj3);
	weaponPUObj3->SetCollider(weaponPUCol3);
	weaponPUObj3->Start();
	firstLevel->AddObject(weaponPUObj3);
	myRenderPipeline->LoadIntoRenderPipeline(weaponPURendObj3);


	RenderObject* weaponPURendObj4 = new RenderObject(2, 6, weaponPUText, &myEngine, 1.0f, 1, 1);
	float positionWeaponPUCol4[2] = { 100.0f, 100.0f };
	float sizeWeaponPUCol4[2] = { weaponPUText->GetFrameDimensions().width, weaponPUText->GetFrameDimensions().height };
	Pickable* weaponPUObj4 = new Pickable("Pickable", weaponPURendObj4, &myEngine, weaponPURendObj4->id, Pickable::TypeOfPickable::FirepowerType);
	Collider* weaponPUCol4 = new Collider(Collider::Dynamic, positionWeaponPUCol4, sizeWeaponPUCol4, myPhysManager, true, weaponPUObj4);
	weaponPUObj4->SetCollider(weaponPUCol4);
	weaponPUObj4->Start();
	firstLevel->AddObject(weaponPUObj4);
	myRenderPipeline->LoadIntoRenderPipeline(weaponPURendObj4);




	Texture* shieldPUText = new Texture("graphics/PUShield.bmp", 2, 4);
	RenderObject* shieldPURendObj = new RenderObject(2, 6, shieldPUText, &myEngine, 1.0f, 1, 1);
	float positionShieldPUCol[2] = { 300.0f, 0.0f };
	float sizeShieldPUCol[2] = { shieldPUText->GetFrameDimensions().width, shieldPUText->GetFrameDimensions().height };
	Pickable* shieldPUObj = new Pickable("Pickable", shieldPURendObj, &myEngine, shieldPURendObj->id, Pickable::TypeOfPickable::ShieldType);
	Collider* shieldPUCol = new Collider(Collider::Dynamic, positionShieldPUCol, sizeShieldPUCol, myPhysManager, true, shieldPUObj);
	shieldPUObj->SetCollider(shieldPUCol);
	shieldPUObj->Start();
	firstLevel->AddObject(shieldPUObj);
	myRenderPipeline->LoadIntoRenderPipeline(shieldPURendObj);




	Texture* companionPUText = new Texture("graphics/clone.bmp", 5, 4);
	RenderObject* companionPURendObj = new RenderObject(2, 6, companionPUText, &myEngine, 1.0f, 1, 1);
	float positionCompanionPUCol[2] = { 300.0f, -200.0f };
	float sizeCompanionPUCol[2] = { companionPUText->GetFrameDimensions().width, companionPUText->GetFrameDimensions().height };
	Pickable* companionPUObj = new Pickable("Pickable", companionPURendObj, &myEngine, companionPURendObj->id, 
		Pickable::TypeOfPickable::CompanionType);
	Collider* companionPUCol = new Collider(Collider::Dynamic, positionCompanionPUCol, sizeCompanionPUCol, myPhysManager, true, companionPUObj);
	companionPUObj->SetCollider(companionPUCol);
	companionPUObj->Start();
	firstLevel->AddObject(companionPUObj);
	myRenderPipeline->LoadIntoRenderPipeline(companionPURendObj);



	RenderObject* companionPURendObj2 = new RenderObject(2, 6, companionPUText, &myEngine, 1.0f, 1, 1);
	float positionCompanionPUCol2[2] = { 500.0f, -200.0f };
	float sizeCompanionPUCol2[2] = { companionPUText->GetFrameDimensions().width, companionPUText->GetFrameDimensions().height };
	Pickable* companionPUObj2 = new Pickable("Pickable", companionPURendObj2, &myEngine, companionPURendObj2->id,
		Pickable::TypeOfPickable::CompanionType);
	Collider* companionPUCol2 = new Collider(Collider::Dynamic, positionCompanionPUCol2, sizeCompanionPUCol2, myPhysManager, true, companionPUObj2);
	companionPUObj2->SetCollider(companionPUCol2);
	companionPUObj2->Start();
	firstLevel->AddObject(companionPUObj2);
	myRenderPipeline->LoadIntoRenderPipeline(companionPURendObj2);


	//SHIP
	Texture* shipTexture = new Texture("graphics/Ship1.bmp", 1, 7);
	Texture* missileTexture = new Texture("graphics/missile.bmp", 3, 2);
	Texture* explosionTexture = new Texture("graphics/explode64.bmp", 2, 5);
	RenderObject* shipRendObject = new RenderObject(7, 7, shipTexture, &myEngine, 1.0f, 1, 4);
	float position0[2] = { 0, 0 };
	float size0[2] = { shipTexture->GetFrameDimensions().width, shipTexture->GetFrameDimensions().height };
	Spaceship* myShip = new Spaceship("Spaceship", shipRendObject, &myEngine, shipRendObject->id, 10.0f, missileTexture, explosionTexture, 
		companionPUText);
	Collider* shipCol = new Collider(Collider::Dynamic, position0, size0, myPhysManager, true, myShip);
	myShip->SetCollider(shipCol);
	myShip->Start();
	firstLevel->AddObject(myShip);
	myRenderPipeline->LoadIntoRenderPipeline(shipRendObject);


	//RUSHER
	Texture* rusherTexture = new Texture("graphics/rusher.bmp", 6, 4);
	RenderObject* rusherRendObject = new RenderObject(2, 6, rusherTexture, &myEngine, 1.0f, 1, 1);
	float position1[2] = { 300.0f, -100.0f };
	float size1[2] = { rusherTexture->GetFrameDimensions().width, rusherTexture->GetFrameDimensions().height };
	Rusher* testRusher = new Rusher("Enemy", rusherRendObject, &myEngine, rusherRendObject->id, -20.0f);
	Collider* rusherCol = new Collider(Collider::Dynamic, position1, size1, myPhysManager, true, testRusher);
	testRusher->SetCollider(rusherCol);
	testRusher->Start();
	firstLevel->AddObject(testRusher);
	myRenderPipeline->LoadIntoRenderPipeline(rusherRendObject);



	//LONER
	Texture* lonerTexture = new Texture("graphics/LonerA.bmp", 4, 4);
	Texture* projectileText = new Texture("graphics/EnWeap6.bmp", 1, 8);
	RenderObject* lonerRendObject = new RenderObject(2, 4, lonerTexture, &myEngine, 1.0f, 1, 1);
	float positionColLoner[2] = { 150.0f, 150.0f };
	float sizeColLoner[2] = { lonerTexture->GetFrameDimensions().width, lonerTexture->GetFrameDimensions().height };
	Loner* testLoner = new Loner("Enemy", lonerRendObject, &myEngine, lonerRendObject->id, 20.0f, projectileText, explosionTexture, myShip);
	Collider* lonerCollider = new Collider(Collider::Dynamic, positionColLoner, sizeColLoner, myPhysManager, true, testLoner);
	testLoner->SetCollider(lonerCollider);
	testLoner->Start();
	firstLevel->AddObject(testLoner);
	myRenderPipeline->LoadIntoRenderPipeline(lonerRendObject);



	//DRONE SPAWNER
	Texture* droneText = new Texture("graphics/drone.bmp", 2, 8);
	Spawner* droneSpawnerObj = new Spawner("Spawner", &myEngine, 1, droneText, 100, Vector2(400.0f, 150.0f));
	firstLevel->AddObject(droneSpawnerObj);

	Spawner* droneSpawnerObj2 = new Spawner("Spawner", &myEngine, 1, droneText, 100, Vector2(400.0f, -150.0f));
	firstLevel->AddObject(droneSpawnerObj2);


	//STONE ASTEROIDS
	Texture* astBigText = new Texture("graphics/SAster96.bmp", 5, 5);
	Texture* astMediumText = new Texture("graphics/SAster64.bmp", 3, 8);
	Texture* astSmallText = new Texture("graphics/SAster32.bmp", 2, 8);



	RenderObject* astRendObj = new RenderObject(2, 6, astBigText, &myEngine, 1.0f, 1, 1);
	float posAstCol[2] = { 400.0f, 0.0f };
	float sizeAstCol[2] = { astBigText->GetFrameDimensions().width, astBigText->GetFrameDimensions().height };
	AsteroidsStone* astObj = new AsteroidsStone("Enemy", astRendObj, &myEngine, astRendObj->id, -20.0f, AsteroidsStone::Big, astMediumText, 
		astSmallText);
	Collider* astCol = new Collider(Collider::Dynamic, posAstCol, sizeAstCol, myPhysManager, true, astObj);
	astObj->SetCollider(astCol);
	astObj->Start();
	firstLevel->AddObject(astObj);
	myRenderPipeline->LoadIntoRenderPipeline(astRendObj);




	//METAL ASTEROIDS
	Texture* metalBigText = new Texture("graphics/MAster96.bmp", 5, 5);
	Texture* metalMediumText = new Texture("graphics/MAster64.bmp", 3, 8);
	Texture* metalSmallText = new Texture("graphics/MAster32.bmp", 2, 8);

	RenderObject* metalRendObj = new RenderObject(2, 6, metalBigText, &myEngine, 1.0f, 1, 1);
	float posMetalCol[2] = { 600.0f, 0.0f };
	float sizeMetalCol[2] = { metalBigText->GetFrameDimensions().width, metalBigText->GetFrameDimensions().height };
	AsteroidsMetal* metalObj = new AsteroidsMetal("Metal", metalRendObj, &myEngine, metalRendObj->id, -30.0f, AsteroidsMetal::Big);
	Collider* metalCol = new Collider(Collider::Dynamic, posMetalCol, sizeMetalCol, myPhysManager, true, metalObj);
	metalObj->SetCollider(metalCol);
	metalObj->Start();
	firstLevel->AddObject(metalObj);
	myRenderPipeline->LoadIntoRenderPipeline(metalRendObj);

	RenderObject* metalRendObj2 = new RenderObject(2, 6, metalMediumText, &myEngine, 1.0f, 1, 1);
	float posMetalCol2[2] = { 500.0f, -100.0f };
	float sizeMetalCol2[2] = { metalMediumText->GetFrameDimensions().width, metalMediumText->GetFrameDimensions().height };
	AsteroidsMetal* metalObj2 = new AsteroidsMetal("Metal", metalRendObj2, &myEngine, metalRendObj2->id, -20.0f, AsteroidsMetal::Big);
	Collider* metalCol2 = new Collider(Collider::Dynamic, posMetalCol2, sizeMetalCol2, myPhysManager, true, metalObj2);
	metalObj2->SetCollider(metalCol2);
	metalObj2->Start();
	firstLevel->AddObject(metalObj2);
	myRenderPipeline->LoadIntoRenderPipeline(metalRendObj2);

	RenderObject* metalRendObj3 = new RenderObject(2, 6, metalSmallText, &myEngine, 1.0f, 1, 1);
	float posMetalCol3[2] = { 500.0f, 200.0f };
	float sizeMetalCol3[2] = { metalSmallText->GetFrameDimensions().width, metalSmallText->GetFrameDimensions().height };
	AsteroidsMetal* metalObj3 = new AsteroidsMetal("Metal", metalRendObj3, &myEngine, metalRendObj3->id, -25.0f, AsteroidsMetal::Big);
	Collider* metalCol3 = new Collider(Collider::Dynamic, posMetalCol3, sizeMetalCol3, myPhysManager, true, metalObj3);
	metalObj3->SetCollider(metalCol3);
	metalObj3->Start();
	firstLevel->AddObject(metalObj3);
	myRenderPipeline->LoadIntoRenderPipeline(metalRendObj3);



	//UI
	Texture* extraLifeText = new Texture("graphics/PULife.bmp", 1, 1);
	RenderObject* shipLivesRendObject = new RenderObject(30,30, extraLifeText, &myEngine, 1, 2);
	shipLivesRendObject->SetOffsets(-275.0f, -180.0f);

	Texture* lifeUnitText = new Texture("graphics/lifeunit.jpg", 1, 1);
	RenderObject* lifeBarRendObject = new RenderObject(30, 30, lifeUnitText, &myEngine, 1, 8);
	lifeBarRendObject->SetOffsets(-280.0f, -210.0f);
	lifeBarRendObject->SetColorOverlay(1.0f, 0.0f, 0.0f);

	GameUI* gameUIObj = new GameUI("GameUI", lifeBarRendObject, shipLivesRendObject, &myEngine, myShip, 1);
	firstLevel->AddObject(gameUIObj);
	myRenderPipeline->LoadIntoRenderPipeline(shipLivesRendObject);
	myRenderPipeline->LoadIntoRenderPipeline(lifeBarRendObject);


	//Audio
	myEngine.myAudioManager->PlaySoundOnReservedChannel(0, -1, "audio/BackgroundAmbiance.wav", 100);

	//Engine Start
	myEngine.Start(true);
	
	myRenderPipeline->ClearPipeline();

	delete backgroundTexture;
	delete bckgrndStonesTexture;
	delete weaponPUText;
	delete shieldPUText;
	delete companionPUText;
	delete shipTexture;
	delete missileTexture;
	delete explosionTexture;
	delete rusherTexture;
	delete lonerTexture;
	delete projectileText;
	delete droneText;
	delete astSmallText;
	delete astMediumText;
	delete astBigText;
	delete metalSmallText;
	delete metalMediumText;
	delete metalBigText;
	delete extraLifeText;
	delete lifeUnitText;

    return 0;
}