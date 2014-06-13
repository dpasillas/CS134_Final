#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "item.h"

class Collectible : public Item {
public:
    Collectible(Ogre::SceneManager* mSceneMgr, Ogre::Vector3 pos = Ogre::Vector3(0,0,0));
    
    virtual void update(Ogre::Real);
};

#endif
