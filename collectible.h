#ifdef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "item.h"

class Collectible : public Item {
public:
    class Collectible(Ogre::SceneManager* mSceneMgr);
    
    virtual void update(Ogre::Real);
};

#endif
