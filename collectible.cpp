#include "collectible.h"
#include <cstdlib>
//#include <stdlib.h>

using namespace Ogre;

Collectible::Collectible(SceneManager* mSceneMgr) : Item(mSceneMgr) {

    // Create an Entity
    Entity* barrelCollectible = mSceneMgr->createEntity(getUniqueName("Collectible"), "cube.mesh");

    // Create a SceneNode and attach the Entity to it
    SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(getUniqueName("CollectibleNode"), pos);
    
    sceneNode->attachObject(collectibleEntity);
    sceneNode->scale(1, 1, 2);
    sceneNode->yaw(Degree(90));
    
    setNode(sceneNode);
}

// modify as you please :3
void Collectible::update(Real dt) {
    node->translate(Vector3(-25,0,0) * dt);
    node->yaw(Degree(5));
}
