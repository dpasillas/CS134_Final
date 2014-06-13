#include "projectile.h"
#include <cstdlib>
//#include <stdlib.h>

using namespace Ogre;

unsigned 
int Projectile::id = 0;

Projectile::Projectile(SceneManager* mSceneMgr, Vector3 pos, Vector3 dir) {
    //mSceneMgr->setAmbientLight(ColourValue(1.0, 1.0, 1.0));

    // Create an Entity
    char buf[256];
    std::string idTag = std::string("") + id++;
    Entity* barrelProjectile = mSceneMgr->createEntity("Bullet" + idTag, "fish.mesh");

    // Create a SceneNode and attach the Entity to it
    SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BulletNode"+idTag, pos);
    sceneNode->attachObject(barrelProjectile);
    sceneNode->scale(5, 5, 5);
    // sceneNode->yaw(Degree(90));          // make ogre face sideways

    /*// Create a Light and set its pos
    Light* mainLight = mSceneMgr->createLight("MainLight");
    mainLight->setType(Light::LT_POINT);
    mainLight->setPosition(Vector3(250, 150, 250));
    mainLight->setDiffuseColour(ColourValue::White);
    mainLight->setSpecularColour(ColourValue::White);

    // create the second camera node and pitch node
    sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode", Vector3(0, 0, 400));
    sceneNode = sceneNode->createChildSceneNode("PitchNode");
    sceneNode->attachObject(mCamera);*/
}

void Projectile::update() {
    
}
