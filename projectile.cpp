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
    Entity* ogreHead = mSceneMgr->createEntity("Bullet" + idTag, "ogrehead.mesh");
            ogreHead->getSubEntity(0)->setMaterialName("CustomOgre/Eyes");
            ogreHead->getSubEntity(1)->setMaterialName("CustomOgre/Skin");
            ogreHead->getSubEntity(2)->setMaterialName("CustomOgre/Earring");
            ogreHead->getSubEntity(3)->setMaterialName("CustomOgre/Tusks");
    
    // Create a SceneNode and attach the Entity to it
    SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BulletNode"+idTag, pos);
    sceneNode->attachObject(ogreHead);
    sceneNode->scale(0.075, 0.075, 0.075);  // make ogre smaller
    sceneNode->yaw(Degree(90));          // make ogre face sideways
    
    node = sceneNode;
    
    projectiles.push_back(this);
    
}

void Projectile::update(Real dt) {
    for(int i = 0, _i = projectiles.size(); i < _i; ++i) {
        Projectile* p = projectiles[i];
        p->node->translate( p->dir * dt);
    }
}
