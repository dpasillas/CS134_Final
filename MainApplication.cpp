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
#include <algorithm>
#include <iostream>

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
    // MeshManager::load("ogrehead.mesh");
	// Build your scene here
	// Set the scene's ambient light
    mSceneMgr->setAmbientLight(ColourValue(1.0, 1.0, 1.0));

    // Create an Entity
    Entity* playerEntity = mSceneMgr->createEntity("Player", "RZR-002.mesh");

    // Create a SceneNode and attach the Entity to it
    SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode", Vector3(0, 0, 0));
    sceneNode->attachObject(playerEntity);
    sceneNode->scale(3, 3, 3);          // set size of the player
    sceneNode->yaw(Degree(90));         // make player face ->
    sceneNode->roll(Degree(90));        // get top down view

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

    CollectibleSpawner::cs = new CollectibleSpawner(mSceneMgr);
    EnemySpawner::es = new EnemySpawner(mSceneMgr,Vector3(240,0,0),0);
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
//-------------------------------------------------------------------------------------
bool MainApplication::frameRenderingQueued(const FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;
    if(mShutDown)
        return false;

    if(Collectible::score < 0 && CollectibleSpawner::cs && EnemySpawner::es)
    {
        Item::queueForDeletion(CollectibleSpawner::cs);
        CollectibleSpawner::cs = 0;
        Item::queueForDeletion(EnemySpawner::es);
        EnemySpawner::es = 0;
    }
    if(Collectible::score >= 100 && EnemySpawner::es && EnemySpawner::es->mode == 0)
    {
        Collectible::score = 0;
        Item::queueForDeletion(EnemySpawner::es);
        EnemySpawner::es = new EnemySpawner(mSceneMgr,Vector3(240,0,0),1);
    }
    if(Collectible::score >= 100 && CollectibleSpawner::cs && EnemySpawner::es && EnemySpawner::es->mode == 1)
    {
        Item::queueForDeletion(CollectibleSpawner::cs);
        CollectibleSpawner::cs = 0;
        Item::queueForDeletion(EnemySpawner::es);
        EnemySpawner::es = 0;
    }

    // Capture input to respond
    mKeyboard->capture();
    mMouse->capture();
    mTrayMgr->frameRenderingQueued(evt);

    // Update ogre position
    mSceneMgr->getSceneNode("PlayerNode")->translate(mDirection * evt.timeSinceLastFrame, Node::TS_WORLD);

    Item::updateAll(evt.timeSinceLastFrame);
    Item::checkCollisions(mSceneMgr);
    Item::cleanup();
    
    sceneBoundingBox();

    return BaseApplication::frameRenderingQueued(evt);
}
//-------------------------------------------------------------------------------------
void MainApplication::sceneBoundingBox()
{
    Vector3 mDistance(mSceneMgr->getSceneNode("PlayerNode")->getPosition());
    if(mDistance.x <= MIN_X)
    {
        //mDirection.x = std::max(0.,(double)mDirection.x);
        mSceneMgr->getSceneNode("PlayerNode")->setPosition(Vector3(MIN_X, mDistance.y, mDistance.z));
    }
    if(mDistance.x >= MAX_X)
    {
        //mDirection.x = std::min(0.,(double)mDirection.x);
        mSceneMgr->getSceneNode("PlayerNode")->setPosition(Vector3(MAX_X, mDistance.y, mDistance.z));
    }
    if(mDistance.y <= MIN_Y)
    {
        //mDirection.y = std::max(0.,(double)mDirection.y);
        mSceneMgr->getSceneNode("PlayerNode")->setPosition(Vector3(mDistance.x, MIN_Y, mDistance.z));
    }
    if(mDistance.y >= MAX_Y)
    {
        //mDirection.y = std::min(0.,(double)mDirection.y);
        mSceneMgr->getSceneNode("PlayerNode")->setPosition(Vector3(mDistance.x, MAX_Y, mDistance.z));
    }
}
//-------------------------------------------------------------------------------------
// void MainApplication::checkHitBox()
// {
//     Vector3 playerPos(mSceneMgr->getSceneNode("PlayerNode")->getPosition());
//     Vector3 collectiblePos(500, 0, 0);
//     for(int i = 0; i < collectibleNames.size(); ++i)
//     {
        
//     }
// }
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
            mDirection.y += mMove;
            break;

        case OIS::KC_A:
            mDirection.x -= mMove;
            break;

        case OIS::KC_S:
            mDirection.y -= mMove;
            break;

        case OIS::KC_D:
            mDirection.x += mMove;
            break;

        case OIS::KC_SPACE:
            new Projectile(mSceneMgr, mSceneMgr->getSceneNode("PlayerNode")->getPosition());

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
            mDirection.y -= mMove;
            break;

        case OIS::KC_A:
            mDirection.x += mMove;
            break;

        case OIS::KC_S:
            mDirection.y += mMove;
            break;

        case OIS::KC_D:
            mDirection.x -= mMove;
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
