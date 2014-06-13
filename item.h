#ifndef ITEM_H
#define ITEM_H

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
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

class Item {
public:
    Item(Ogre::SceneManager* mSceneMgr);
    
    static void updateAll(Ogre::Real);
    virtual void update(Ogre::Real) = 0;
protected:
    std::string getUniqueName(std::string prefix);
    void setNode(Ogre::SceneNode* node);
    
    static unsigned int id;
    static std::vector<Item*> items;
    
    Ogre::SceneManager* mSceneMgr;
    //Ogre::Vector3 dir;
    Ogre::SceneNode* node;
    
};

#endif
