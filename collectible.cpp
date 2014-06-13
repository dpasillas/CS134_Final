#include "collectible.h"
#include <cstdlib>
#include <math.h>
//#include <stdlib.h>

const double PI = acos(-1);

using namespace Ogre;

Collectible::Collectible(SceneManager* mSceneMgr, Vector3 pos) : Item(mSceneMgr) {
   
    // Create an Entity
    Entity* collectibleEntity = mSceneMgr->createEntity(getUniqueName("Collectible"), "cube.mesh");
            collectibleEntity->setMaterialName("CustomOgre/Earring");
    // Create a SceneNode and attach the Entity to it
    std::string collectibleName = getUniqueName("CollectibleNode");
    collectibleNames.push_back(collectibleName);
    SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(getUniqueName("CollectibleNode"), pos);
    sceneNode->attachObject(collectibleEntity);
    sceneNode->scale(0.2, 0.2, 0.2);
    
    setNode(sceneNode);
}

// modify as you please :3
void Collectible::update(Real dt) {
    node->translate(Vector3(-200,0,0) * dt);    // makes the collectibles move <-- that way
    node->yaw(Degree(-2));
    node->roll(Degree(2));
    node->pitch(Degree(-2));
}

CollectibleSpawner::CollectibleSpawner(SceneManager* mSceneMgr, Vector3 pos) 
    : Item(mSceneMgr), accumulator(0), totalTime(0) 
{
    // Create an Entity
    ManualObject* collectibleSpawner = mSceneMgr->createManualObject(getUniqueName("Spawner"));
    // collectibleSpawner->end();
    // Create a SceneNode and attach the Entity to it
    SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(getUniqueName("SpawnerNode"), pos);
    
    sceneNode->attachObject(collectibleSpawner);
    sceneNode->scale(0.2, 0.2, 0.2);
    sceneNode->setPosition(Vector3(240, 0, 0));
    
    setNode(sceneNode);
}

void CollectibleSpawner::update(Real dt)
{
#define SPAWN_PERIOD (1./3.)
    totalTime += dt;
    accumulator += dt;
    if(accumulator >= SPAWN_PERIOD)
    {
        accumulator -= SPAWN_PERIOD;
        new Collectible(mSceneMgr, node->getPosition());
    }
    Vector3 newPos(240, 100 * sin(totalTime), 0);
    node->setPosition(newPos);    // makes the collectibles move <-- that way
}