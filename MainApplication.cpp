/*
-----------------------------------------------------------------------------
Filename:    %ProjectName:l%.%CppSourceSuffix%
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

#include "MainApplication.h"

#define MIN_Y -180
#define MAX_Y 180
#define MIN_X -225
#define MAX_X 225

using namespace Ogre;

//-------------------------------------------------------------------------------------
MainApplication::MainApplication(void)
{
}
//-------------------------------------------------------------------------------------
MainApplication::~MainApplication(void)
{
}
//-------------------------------------------------------------------------------------
void MainApplication::createScene(void)
{
	// Build your scene here
	// Set the scene's ambient light
    mSceneMgr->setAmbientLight(ColourValue(1.0, 1.0, 1.0));

    // Create an Entity
    Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
            ogreHead->getSubEntity(0)->setMaterialName("CustomOgre/Eyes");
            ogreHead->getSubEntity(1)->setMaterialName("CustomOgre/Skin");
            ogreHead->getSubEntity(2)->setMaterialName("CustomOgre/Earring");
            ogreHead->getSubEntity(3)->setMaterialName("CustomOgre/Tusks");
    
    // Create a SceneNode and attach the Entity to it
    SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("OgreNode", Vector3(0, 0, 0));
    sceneNode->attachObject(ogreHead);
    sceneNode->scale(0.75, 0.75, 0.75);  // make ogre smaller
    sceneNode->yaw(Degree(90));          // make ogre face sideways

    // Create a Light and set its pos
    Light* mainLight = mSceneMgr->createLight("MainLight");
    mainLight->setType(Light::LT_POINT);
    mainLight->setPosition(Vector3(250, 150, 250));
    mainLight->setDiffuseColour(ColourValue::White);
    mainLight->setSpecularColour(ColourValue::White);

    // create the second camera node and pitch node
    sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode", Vector3(0, 0, 400));
    sceneNode = sceneNode->createChildSceneNode("PitchNode");
    sceneNode->attachObject(mCamera);
}
//-------------------------------------------------------------------------------------
void MainApplication::createFrameListener(void)
{
    BaseApplication::createFrameListener();

    // Populate the camera container
    mCamNode = mCamera->getParentSceneNode();

    // set the rotation and move speed
    mRotate = 0.13;
    mMove = 250;

    mDirection = Vector3::ZERO;
}

bool MainApplication::frameRenderingQueued(const FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;
    if(mShutDown)
        return false;

    // Capture input to respond
    mKeyboard->capture();
    mMouse->capture();
    mTrayMgr->frameRenderingQueued(evt);
    // mCamNode->translate(mDirection * evt.timeSinceLastFrame, Node::TS_LOCAL);

    mSceneMgr->getSceneNode("OgreNode")->translate(mDirection * evt.timeSinceLastFrame, Node::TS_WORLD);
    Vector3 mDistance(mSceneMgr->getSceneNode("OgreNode")->getPosition());
    if(mDistance.x <= MIN_X)
    {
        mDirection.x = 0;
        mSceneMgr->getSceneNode("OgreNode")->setPosition(Vector3(MIN_X, mDistance.y, mDistance.z));
    }
    if(mDistance.x >= MAX_X)
    {
        mDirection.x = 0;
        mSceneMgr->getSceneNode("OgreNode")->setPosition(Vector3(MAX_X, mDistance.y, mDistance.z));
    }
    if(mDistance.y <= MIN_Y)
    {
        mDirection.y = 0;
        mSceneMgr->getSceneNode("OgreNode")->setPosition(Vector3(mDistance.x, MIN_Y, mDistance.z));
    }
    if(mDistance.y >= MAX_Y)
    {
        mDirection.y = 0;
        mSceneMgr->getSceneNode("OgreNode")->setPosition(Vector3(mDistance.x, MAX_Y, mDistance.z));
    }

    return true;
}

//-------------------------------------------------------------------------------------
// OIS::Keylistener
bool MainApplication::keyPressed(const OIS::KeyEvent& evt)
{
    switch(evt.key)
    {
        case OIS::KC_ESCAPE:
            mShutDown = true;
            break;

        case OIS::KC_W:
            mDirection.y = mMove;
            break;

        case OIS::KC_A:
            mDirection.x = -mMove;
            break;

        case OIS::KC_S:
            mDirection.y = -mMove;
            break;

        case OIS::KC_D:
            mDirection.x = mMove;
            break;

        default:
            break;
    }
    return true;
}
//-------------------------------------------------------------------------------------
bool MainApplication::keyReleased(const OIS::KeyEvent& evt)
{
    switch(evt.key)
    {
        case OIS::KC_W:
            mDirection.y = 0;
            break;

        case OIS::KC_A:
            mDirection.x = 0;
            break;

        case OIS::KC_S:
            mDirection.y = 0;
            break;

        case OIS::KC_D:
            mDirection.x = 0;
            break;

        default:
            break;
    }
    return true;
}
//-------------------------------------------------------------------------------------
bool MainApplication::mouseMoved(const OIS::MouseEvent& evt)
{
    return true;
}
//-------------------------------------------------------------------------------------
bool MainApplication::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
    return true;
}
//-------------------------------------------------------------------------------------
bool MainApplication::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
    return true;
}
//-------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

    int main(int argc, char *argv[])
    {
        // Create application object
        MainApplication app;

        try {
            app.go();
        } catch( Exception& e ) {
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
