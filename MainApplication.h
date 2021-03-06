/*
-----------------------------------------------------------------------------
Filename:    %ProjectName:l%.%CppHeaderSuffix%
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.8.x Application Wizard for QtCreator (May 2012)
      https://bitbucket.org/jacmoe/ogreappwizards
-----------------------------------------------------------------------------
*/
#ifndef __MainApplication_h__
#define __MainApplication_h__

#include "BaseApplication.h"

class MainApplication: public BaseApplication
{
public:
    MainApplication(void);
    virtual ~MainApplication(void);

protected:
    virtual void createScene(void);
    virtual void createFrameListener(void);
    
    // Ogre FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    // OIS KeyListener
    virtual bool keyPressed(const OIS::KeyEvent& evt);
    virtual bool keyReleased(const OIS::KeyEvent& evt);
    // OIS MouseListener
    virtual bool mouseMoved(const OIS::MouseEvent& evt);
    virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
    void sceneBoundingBox();
    void checkHitBox();

    Ogre::Real mRotate;         // rotate constant
    Ogre::Real mMove;           // movement cosntant
    Ogre::SceneNode * mCamNode; // SceneNode the camera is currently attacjed to
    Ogre::Vector3 mDirection;   // value to move in correct direction
};

#endif
