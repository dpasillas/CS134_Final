#include "projectile.h"
#include <cstdlib>
//#include <stdlib.h>

using namespace Ogre;

Projectile::Projectile(SceneManager* mSceneMgr, Vector3 pos, Vector3 dir) : Item(mSceneMgr), dir(dir) {

    // Create an Entity
    Entity* projectileEntity = mSceneMgr->createEntity(getUniqueName("Bullet"), "RZR-002.mesh");
            projectileEntity->setMaterialName("CustomOgre/Eyes");

    // Create a SceneNode and attach the Entity to it
    SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(getUniqueName("BulletNode"), pos);
    

    sceneNode->attachObject(projectileEntity);
    sceneNode->scale(0.75, 0.75, 2);
    sceneNode->yaw(Degree(90));
    
    setNode(sceneNode);
}

void Projectile::update(Real dt) {
    node->translate(dir * dt);
    node->roll(Degree(15));
}
