#include "enemy.h"
#include "collectible.h"

using namespace Ogre;

Enemy::Enemy(SceneManager* mSceneMgr, Vector3 pos, int mode)
	: Item(mSceneMgr), mode(0), vel(Vector3(-350, 0.0, 0.0)) 
{
	init();
	if(mode)
	    hp = 5;
	else
	    hp = 2;
    // Create an Entity
    Entity* enemyEntity = mSceneMgr->createEntity(name, "ogrehead.mesh");
            enemyEntity->getSubEntity(0)->setMaterialName("CustomOgre/Eyes");
            enemyEntity->getSubEntity(1)->setMaterialName("CustomOgre/Skin");
            enemyEntity->getSubEntity(2)->setMaterialName("CustomOgre/Earring");
            enemyEntity->getSubEntity(3)->setMaterialName("CustomOgre/Tusks");

    // Create a SceneNode and attach the Entity to it
    SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name + "Node", pos);
    sceneNode->attachObject(enemyEntity);
    sceneNode->scale(1, 1, 1);
    sceneNode->yaw(Degree(-90));
    sceneNode->roll(Degree(-90));
    sceneNode->pitch(Degree(-45));
    
    setNode(sceneNode);
}

std::string Enemy::getPrefix()
{
	return "Enemy";
}

void Enemy::update(Real dt)
{
	node->translate(vel * dt);
}

bool Enemy::playerCollision()
{
	Item::queueForDeletion(this);
	Collectible::score -= 10;
	return true;
}



EnemySpawner::EnemySpawner(SceneManager* mSceneMgr, Vector3 pos) 
    : Item(mSceneMgr), accumulator(0), totalTime(0), period(2.0)
{
    init();
    // Create an Entity
    ManualObject* enemySpawner = mSceneMgr->createManualObject(name);
    // enemySpawner->end();
    // Create a SceneNode and attach the Entity to it
    SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name + "Node", pos);
    
    sceneNode->attachObject(enemySpawner);
    sceneNode->setPosition(Vector3(240, 0, 0));
    
    setNode(sceneNode);
}

void EnemySpawner::update(Real dt)
{
	
    totalTime += dt;
    accumulator += dt;
    if(accumulator >= period)
    {
        accumulator -= period;
        Vector3 pos = node->getPosition();
        pos.x = 240;
        pos.y = (rand() / double(RAND_MAX) - 0.5) * 2 * 150;
        new Enemy(mSceneMgr, pos);
        period = (rand() / double(RAND_MAX)) * 3.0 + 2.0;
    }
    Vector3 newPos(240, 100 * sin(totalTime), 0);
    node->setPosition(newPos);    // makes the collectibles move <-- that way
}

std::string EnemySpawner::getPrefix() {
    return "eSpawner";
}
