#include "projectile.h"
#include <cstdlib>
//#include <stdlib.h>

using namespace Ogre;

unsigned int Projectile::id = 0;
std::vector<Projectile*> Projectile::projectiles = std::vector<Projectile*>();

Projectile::Projectile(SceneManager* mSceneMgr, Vector3 pos, Vector3 dir) : mSceneMgr(mSceneMgr), dir(dir) {

    // Create an Entity
    char buf[256];
    std::string idTag = std::string("") + id++;
    Entity* barrelProjectile = mSceneMgr->createEntity("Bullet" + idTag, "RZR-002.mesh");

    // Create a SceneNode and attach the Entity to it
    SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BulletNode"+idTag, pos);
    
    sceneNode->attachObject(barrelProjectile);
    sceneNode->scale(1, 1, 1);
    sceneNode->yaw(Degree(90));
    
    node = sceneNode;
    projectiles.push_back(this);
}

void Projectile::update(Real dt) {
    for(int i = 0, _i = projectiles.size(); i < _i; ++i) {
        Projectile* p = projectiles[i];
        p->node->translate(p->dir * dt);
    }
}
