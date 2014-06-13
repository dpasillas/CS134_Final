#ifndef ITEM_H
#define ITEM_H

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreSceneQuery.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include <OgreRectangle2D.h>
#include <OgreRenderSystem.h>
#include <OgreAxisAlignedBox.h>
#include <OgreMaterial.h>

#include <vector>
#include <map>
#include <queue>

class Item {
public:
    Item(Ogre::SceneManager* mSceneMgr);
    
    static void updateAll(Ogre::Real);
    static void checkCollisions(Ogre::SceneManager* mSceneMgr);
    static void cleanup();
    static Item* findByName(std::string name);
    virtual void update(Ogre::Real) = 0;
    virtual std::string getPrefix() = 0;
    virtual bool playerCollision();
    virtual bool enemyCollision(Item* enemy);
protected:

    void init();
    void queueForDeletion(Item * item);
    std::string getUniqueName(std::string prefix);
    void setNode(Ogre::SceneNode* node);
    
    static unsigned int id;
    //static std::vector<Item*> items;
    static std::map<std::string, Item*> itemsByName;
    static std::queue<Item*> deletionQueue;
    
    Ogre::SceneManager* mSceneMgr;
    //Ogre::Vector3 dir;
    Ogre::SceneNode* node;
    std::string name;
    
    class ItemListener : public Ogre::IntersectionSceneQueryListener {
        bool queryResult(Ogre::MovableObject *first, Ogre::MovableObject *second);
        bool queryResult(Ogre::MovableObject*, Ogre::SceneQuery::WorldFragment*);

    };
    
    friend class ItemListener;
    
    static ItemListener* listener;
    
};

#endif
