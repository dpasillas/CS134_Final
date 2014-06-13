#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "item.h"

class Collectible : public Item {
public:
    Collectible(Ogre::SceneManager* mSceneMgr, Ogre::Vector3 pos = Ogre::Vector3(0,0,0));
    
    virtual void update(Ogre::Real);
    
    static std::vector<std::string> collectibleNames;
    virtual std::string getPrefix();
    virtual bool playerCollision();
    virtual bool enemyCollision();

    static int score;
};

class CollectibleSpawner : public Item {
public:
    CollectibleSpawner(Ogre::SceneManager* mSceneMgr, Ogre::Vector3 pos = Ogre::Vector3(0,0,0));
    
    virtual void update(Ogre::Real);

    virtual std::string getPrefix();
    
    virtual bool playerCollision();
    virtual bool enemyCollision();
    
    volatile Ogre::Real accumulator;
    volatile Ogre::Real totalTime;
};

#endif
