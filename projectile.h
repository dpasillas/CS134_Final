#ifndef PROJECTILE_H
#define PROJECTILE_H

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

class Projectile {
public:
    Projectile(Ogre::SceneManager* mSceneMgr, Ogre::Vector3 pos, Ogre::Vector3 dir = Ogre::Vector3(0,0,0));
    
    void update();
private:
    static unsigned int id;
};

#endif
