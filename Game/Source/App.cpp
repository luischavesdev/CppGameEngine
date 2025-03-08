#include "Engine.h"
#include "Level.h"
#include "Object.h"
#include "Texture.h"
#include "RenderObject.h"
#include "Sprite.h"
#include "RenderPipeline.h"
#include "PhysicsManager.h"
#include "Collider.h"
#include "AudioManager.h"

#include "Spaceship.h"
#include "Pickable.h"
#include "Rusher.h"
#include "Loner.h"
#include "Spawner.h"
#include "AsteroidsStone.h"
#include "AsteroidsMetal.h"
#include "GameUI.h"

// If using microsoft compiler, setup application to be windowed only
#ifdef _MSC_VER
#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


int main() {
	GameEngine myEngine;
	myEngine.Init("Xenon 2000 Remake", 620, 480, 60, 8);

	float timeStep = 1.0f / 60.0f;
	myEngine.InitPhysSystem(8.0f, 0.0f, timeStep, 6.0f, 2.0f);
	myEngine.CreateControllerInteraction();

	PhysicsManager* myPhysManager = myEngine.GetPhysManager();
	RenderPipeline* myRenderPipeline = myEngine.GetRenderPipeline();
	Level* firstLevel = myEngine.CreateAndAddLevel("FirstLevel");


	//BACKGROUND
	Texture* backgroundTexture = new Texture("data/graphics/GalaxyBackground.jpg", 1, 1);
	RenderObject* backgroundRendObject = new RenderObject(0, 0, backgroundTexture, &myEngine, 1, 2);
	Sprite* background = new Sprite("Background", backgroundRendObject, &myEngine, backgroundRendObject->id);
	Vector2 parallaxSpeed;
	parallaxSpeed.x = 3.0f;
	parallaxSpeed.y = 0.0f;
	background->SetParallax(true, 0, parallaxSpeed);
	firstLevel->AddObjectToBuffer(background);
	
	//ASTEROID BELT
	Texture* bckgrndStonesTexture = new Texture("data/graphics/BackgroundStones.jpg", 1, 1);
	RenderObject* bckgrndStonesRendObj = new RenderObject(1, 1, bckgrndStonesTexture, &myEngine, 1, 2);
	Sprite* bckgrndStones = new Sprite("Aster", bckgrndStonesRendObj, &myEngine, bckgrndStonesRendObj->id);
	Vector2 parallaxSpeed2;
	parallaxSpeed2.x = 3.5f;
	parallaxSpeed2.y = 0.0f;
	bckgrndStones->SetParallax(true, 0, parallaxSpeed2);
	firstLevel->AddObjectToBuffer(bckgrndStones);
	
	//COLLECTIBLES
	Texture* weaponPUText = new Texture("data/graphics/PUWeapon.bmp", 2, 4);
	RenderObject* weaponPURendObj = new RenderObject(2, 6, weaponPUText, &myEngine, 1.0f, 1, 1);
	Vector2 positionWeaponPUCol;
	positionWeaponPUCol.x = 300.0f;
	positionWeaponPUCol.y = 200.0f;
	Vector2 sizeWeaponPUCol;
	sizeWeaponPUCol.x = weaponPUText->GetFrameDimensions().width;
	sizeWeaponPUCol.y = weaponPUText->GetFrameDimensions().height;
	Pickable* weaponPUObj = new Pickable("Pickable", weaponPURendObj, &myEngine, weaponPURendObj->id, Pickable::TypeOfPickable::FirepowerType);
	Collider* weaponPUCol = new Collider(Collider::Dynamic, positionWeaponPUCol, sizeWeaponPUCol, myPhysManager, true, weaponPUObj);
	weaponPUObj->SetCollider(weaponPUCol);
	firstLevel->AddObjectToBuffer(weaponPUObj);
	
	RenderObject* weaponPURendObj2 = new RenderObject(2, 6, weaponPUText, &myEngine, 1.0f, 1, 1);
	Vector2 positionWeaponPUCol2;
	positionWeaponPUCol2.x = 500.0f;
	positionWeaponPUCol2.y = 200.0f;
	Pickable* weaponPUObj2 = new Pickable("Pickable", weaponPURendObj2, &myEngine, weaponPURendObj2->id, Pickable::TypeOfPickable::FirepowerType);
	Collider* weaponPUCol2 = new Collider(Collider::Dynamic, positionWeaponPUCol2, sizeWeaponPUCol, myPhysManager, true, weaponPUObj2);
	weaponPUObj2->SetCollider(weaponPUCol2);
	firstLevel->AddObjectToBuffer(weaponPUObj2);
	
	RenderObject* weaponPURendObj3 = new RenderObject(2, 6, weaponPUText, &myEngine, 1.0f, 1, 1);
	Vector2 positionWeaponPUCol3;
	positionWeaponPUCol3.x = 200.0f;
	positionWeaponPUCol3.y = 100.0f;
	Pickable* weaponPUObj3 = new Pickable("Pickable", weaponPURendObj3, &myEngine, weaponPURendObj3->id, Pickable::TypeOfPickable::FirepowerType);
	Collider* weaponPUCol3 = new Collider(Collider::Dynamic, positionWeaponPUCol3, sizeWeaponPUCol, myPhysManager, true, weaponPUObj3);
	weaponPUObj3->SetCollider(weaponPUCol3);
	firstLevel->AddObjectToBuffer(weaponPUObj3);
	
	RenderObject* weaponPURendObj4 = new RenderObject(2, 6, weaponPUText, &myEngine, 1.0f, 1, 1);
	Vector2 positionWeaponPUCol4;
	positionWeaponPUCol4.x = 100.0f;
	positionWeaponPUCol4.y = 100.0f;
	Pickable* weaponPUObj4 = new Pickable("Pickable", weaponPURendObj4, &myEngine, weaponPURendObj4->id, Pickable::TypeOfPickable::FirepowerType);
	Collider* weaponPUCol4 = new Collider(Collider::Dynamic, positionWeaponPUCol4, sizeWeaponPUCol, myPhysManager, true, weaponPUObj4);
	weaponPUObj4->SetCollider(weaponPUCol4);
	firstLevel->AddObjectToBuffer(weaponPUObj4);

	Texture* shieldPUText = new Texture("data/graphics/PUShield.bmp", 2, 4);
	RenderObject* shieldPURendObj = new RenderObject(2, 6, shieldPUText, &myEngine, 1.0f, 1, 1);
	Vector2 positionShieldPUCol;
	positionShieldPUCol.x = 300.0f;
	positionShieldPUCol.y = 0.0f;
	Vector2 sizeShieldPUCol;
	sizeShieldPUCol.x = shieldPUText->GetFrameDimensions().width;
	sizeShieldPUCol.y = shieldPUText->GetFrameDimensions().height;
	Pickable* shieldPUObj = new Pickable("Pickable", shieldPURendObj, &myEngine, shieldPURendObj->id, Pickable::TypeOfPickable::ShieldType);
	Collider* shieldPUCol = new Collider(Collider::Dynamic, positionShieldPUCol, sizeShieldPUCol, myPhysManager, true, shieldPUObj);
	shieldPUObj->SetCollider(shieldPUCol);
	firstLevel->AddObjectToBuffer(shieldPUObj);

	Texture* companionPUText = new Texture("data/graphics/Clone.bmp", 5, 4);
	RenderObject* companionPURendObj = new RenderObject(2, 6, companionPUText, &myEngine, 1.0f, 1, 1);
	Vector2 positionCompanionPUCol;
	positionCompanionPUCol.x = 300.0f;
	positionCompanionPUCol.y = -200.0f;
	Vector2 sizeCompanionPUCol;
	sizeCompanionPUCol.x = companionPUText->GetFrameDimensions().width;
	sizeCompanionPUCol.y = companionPUText->GetFrameDimensions().height;
	Pickable* companionPUObj = new Pickable("Pickable", companionPURendObj, &myEngine, companionPURendObj->id,
		Pickable::TypeOfPickable::CompanionType);
	Collider* companionPUCol = new Collider(Collider::Dynamic, positionCompanionPUCol, sizeCompanionPUCol, myPhysManager, true, companionPUObj);
	companionPUObj->SetCollider(companionPUCol);
	firstLevel->AddObjectToBuffer(companionPUObj);

	RenderObject* companionPURendObj2 = new RenderObject(2, 6, companionPUText, &myEngine, 1.0f, 1, 1);
	Vector2 positionCompanionPUCol2;
	positionCompanionPUCol2.x = 500.0f;
	positionCompanionPUCol2.y = -200.0f;
	Pickable* companionPUObj2 = new Pickable("Pickable", companionPURendObj2, &myEngine, companionPURendObj2->id,
		Pickable::TypeOfPickable::CompanionType);
	Collider* companionPUCol2 = new Collider(Collider::Dynamic, positionCompanionPUCol2, sizeCompanionPUCol, myPhysManager, true, companionPUObj2);
	companionPUObj2->SetCollider(companionPUCol2);
	firstLevel->AddObjectToBuffer(companionPUObj2);

	//SHIP
	Texture* shipTexture = new Texture("data/graphics/Ship.bmp", 1, 7);
	Texture* missileTexture = new Texture("data/graphics/Missile.bmp", 3, 2);
	Texture* explosionTexture = new Texture("data/graphics/Explosion.bmp", 2, 5);
	RenderObject* shipRendObject = new RenderObject(7, 7, shipTexture, &myEngine, 1.0f, 1, 4);
	Vector2 positionShipCol;
	positionShipCol.x = 0.0f;
	positionShipCol.y = 0.0f;
	Vector2 sizeShipCol;
	sizeShipCol.x = shipTexture->GetFrameDimensions().width;
	sizeShipCol.y = shipTexture->GetFrameDimensions().height;
	Spaceship* myShip = new Spaceship("Spaceship", shipRendObject, &myEngine, shipRendObject->id, 10.0f, missileTexture, explosionTexture,
		companionPUText);
	Collider* shipCol = new Collider(Collider::Dynamic, positionShipCol, sizeShipCol, myPhysManager, true, myShip);
	myShip->SetCollider(shipCol);
	firstLevel->AddObjectToBuffer(myShip);
	
	//RUSHER
	Texture* rusherTexture = new Texture("data/graphics/Rusher.bmp", 6, 4);
	RenderObject* rusherRendObject = new RenderObject(2, 6, rusherTexture, &myEngine, 1.0f, 1, 1);
	Vector2 positionRusherCol;
	positionRusherCol.x = 300.0f;
	positionRusherCol.y = -100.0f;
	Vector2 sizeRusherCol;
	sizeRusherCol.x = rusherTexture->GetFrameDimensions().width;
	sizeRusherCol.y = rusherTexture->GetFrameDimensions().height;
	Rusher* testRusher = new Rusher("Enemy", rusherRendObject, &myEngine, rusherRendObject->id, -20.0f);
	Collider* rusherCol = new Collider(Collider::Dynamic, positionRusherCol, sizeRusherCol, myPhysManager, true, testRusher);
	testRusher->SetCollider(rusherCol);
	firstLevel->AddObjectToBuffer(testRusher);

	//LONER
	Texture* lonerTexture = new Texture("data/graphics/Loner.bmp", 4, 4);
	Texture* projectileText = new Texture("data/graphics/EnemyProjectile.bmp", 1, 8);
	RenderObject* lonerRendObject = new RenderObject(2, 4, lonerTexture, &myEngine, 1.0f, 1, 1);
	Vector2 positionLonerCol;
	positionLonerCol.x = 150.0f;
	positionLonerCol.y = 150.0f;
	Vector2 sizeLonerCol;
	sizeLonerCol.x = lonerTexture->GetFrameDimensions().width;
	sizeLonerCol.y = lonerTexture->GetFrameDimensions().height;
	Loner* testLoner = new Loner("Enemy", lonerRendObject, &myEngine, lonerRendObject->id, 20.0f, projectileText, explosionTexture, myShip);
	Collider* lonerCollider = new Collider(Collider::Dynamic, positionLonerCol, sizeLonerCol, myPhysManager, true, testLoner);
	testLoner->SetCollider(lonerCollider);
	firstLevel->AddObjectToBuffer(testLoner);

	//DRONE SPAWNER
	Texture* droneText = new Texture("data/graphics/Drone.bmp", 2, 8);
	Vector2 spawnLocation;
	spawnLocation.x = 400.0f;
	spawnLocation.y = 150.0f;
	Spawner* droneSpawnerObj = new Spawner("Spawner", &myEngine, 1, droneText, 100, spawnLocation);
	firstLevel->AddObjectToBuffer(droneSpawnerObj);

	Vector2 spawnLocation2;
	spawnLocation2.x = 400.0f;
	spawnLocation2.y = -150.0f;
	Spawner* droneSpawnerObj2 = new Spawner("Spawner", &myEngine, 1, droneText, 100, spawnLocation2);
	firstLevel->AddObjectToBuffer(droneSpawnerObj2);

	//STONE ASTEROIDS
	Texture* astBigText = new Texture("data/graphics/StoneAsterBig.bmp", 5, 5);
	Texture* astMediumText = new Texture("data/graphics/StoneAsterMedium.bmp", 3, 8);
	Texture* astSmallText = new Texture("data/graphics/StoneAsterSmall.bmp", 2, 8);
	RenderObject* astRendObj = new RenderObject(2, 6, astBigText, &myEngine, 1.0f, 1, 1);
	Vector2 posAstCol;
	posAstCol.x = 400.0f;
	posAstCol.y = 0.0f;
	Vector2 sizeAstCol;
	sizeAstCol.x = astBigText->GetFrameDimensions().width;
	sizeAstCol.y = astBigText->GetFrameDimensions().height;
	Vector2 velAstCol;
	velAstCol.x = -20.0f;
	velAstCol.y = 1.0f;
	AsteroidsStone* astObj = new AsteroidsStone("Enemy", astRendObj, &myEngine, astRendObj->id, velAstCol, AsteroidsStone::Big, astMediumText,
		astSmallText);
	Collider* astCol = new Collider(Collider::Dynamic, posAstCol, sizeAstCol, myPhysManager, true, astObj);
	astObj->SetCollider(astCol);
	firstLevel->AddObjectToBuffer(astObj);

	//METAL ASTEROIDS
	Texture* metalBigText = new Texture("data/graphics/MetalAsterBig.bmp", 5, 5);
	Texture* metalMediumText = new Texture("data/graphics/MetalAsterMedium.bmp", 3, 8);
	Texture* metalSmallText = new Texture("data/graphics/MetalAsterSmall.bmp", 2, 8);
	RenderObject* metalRendObj = new RenderObject(2, 6, metalBigText, &myEngine, 1.0f, 1, 1);
	Vector2 posMetalCol;
	posMetalCol.x = 600.0f;
	posMetalCol.y = 0.0f;
	Vector2 sizeMetalCol;
	sizeMetalCol.x = metalBigText->GetFrameDimensions().width;
	sizeMetalCol.y = metalBigText->GetFrameDimensions().height;
	AsteroidsMetal* metalObj = new AsteroidsMetal("Metal", metalRendObj, &myEngine, metalRendObj->id, -30.0f, AsteroidsMetal::Big);
	Collider* metalCol = new Collider(Collider::Dynamic, posMetalCol, sizeMetalCol, myPhysManager, true, metalObj);
	metalObj->SetCollider(metalCol);
	firstLevel->AddObjectToBuffer(metalObj);

	RenderObject* metalRendObj2 = new RenderObject(2, 6, metalMediumText, &myEngine, 1.0f, 1, 1);
	Vector2 posMetalCol2;
	posMetalCol2.x = 500.0f;
	posMetalCol2.y = -100.0f;
	Vector2 sizeMetalCol2;
	sizeMetalCol2.x = metalMediumText->GetFrameDimensions().width;
	sizeMetalCol2.y = metalMediumText->GetFrameDimensions().height;
	AsteroidsMetal* metalObj2 = new AsteroidsMetal("Metal", metalRendObj2, &myEngine, metalRendObj2->id, -20.0f, AsteroidsMetal::Medium);
	Collider* metalCol2 = new Collider(Collider::Dynamic, posMetalCol2, sizeMetalCol2, myPhysManager, true, metalObj2);
	metalObj2->SetCollider(metalCol2);
	firstLevel->AddObjectToBuffer(metalObj2);

	RenderObject* metalRendObj3 = new RenderObject(2, 6, metalSmallText, &myEngine, 1.0f, 1, 1);
	Vector2 posMetalCol3;
	posMetalCol3.x = 500.0f;
	posMetalCol3.y = 200.0f;
	Vector2 sizeMetalCol3;
	sizeMetalCol3.x = metalSmallText->GetFrameDimensions().width;
	sizeMetalCol3.y = metalSmallText->GetFrameDimensions().height;
	AsteroidsMetal* metalObj3 = new AsteroidsMetal("Metal", metalRendObj3, &myEngine, metalRendObj3->id, -25.0f, AsteroidsMetal::Small);
	Collider* metalCol3 = new Collider(Collider::Dynamic, posMetalCol3, sizeMetalCol3, myPhysManager, true, metalObj3);
	metalObj3->SetCollider(metalCol3);
	firstLevel->AddObjectToBuffer(metalObj3);

	//UI
	Texture* extraLifeText = new Texture("data/graphics/PULife.bmp", 1, 1);
	RenderObject* shipLivesRendObject = new RenderObject(30, 30, extraLifeText, &myEngine, 1, 2);
	shipLivesRendObject->SetOffsets(-275.0f, -180.0f);
	Texture* lifeUnitText = new Texture("data/graphics/LifeUnitUI.jpg", 1, 1);
	RenderObject* lifeBarRendObject = new RenderObject(30, 30, lifeUnitText, &myEngine, 1, 8);
	lifeBarRendObject->SetOffsets(-280.0f, -210.0f);
	lifeBarRendObject->SetColorOverlay(1.0f, 0.0f, 0.0f);
	GameUI* gameUIObj = new GameUI("GameUI", lifeBarRendObject, shipLivesRendObject, &myEngine, myShip, 1);
	firstLevel->AddObjectToBuffer(gameUIObj);
	myRenderPipeline->LoadIntoRenderPipeline(shipLivesRendObject);
	myRenderPipeline->LoadIntoRenderPipeline(lifeBarRendObject);

	myEngine.GetAudioManager()->PlaySoundOnReservedChannel(0, -1, "data/audio/BackgroundAmbiance.wav", 100);

	myEngine.Start(true);


	myRenderPipeline->ClearRenderPipeline();

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
