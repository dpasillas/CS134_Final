#ifndef ENEMY_H
#define ENEMY_H

#include "item.h"

class Enemy : Item
{
public:
	Enemy(Ogre::SceneManager* mSceneMgr, Ogre::Vector3 pos, int mode = 0);
	std::string getPrefix();
	void update(Ogre::Real dt);
	virtual bool playerCollision();
    
    int hp;
private:
	int mode;
	Ogre::Vector3 vel;
};

class EnemySpawner : public Item {
public:
    EnemySpawner(Ogre::SceneManager* mSceneMgr, Ogre::Vector3 pos = Ogre::Vector3(0,0,0), int mode = 0);

    virtual void update(Ogre::Real);
    virtual std::string getPrefix();
    static OgreSpawner* os;
    volatile Ogre::Real accumulator;
    volatile Ogre::Real totalTime;
    double period;
    int mode;
};

#endif
