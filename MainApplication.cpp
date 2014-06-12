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
    mSceneMgr->setAmbientLight(ColourValue(0.75, 0.75, 0.75));
    
    ///=========================================================================
    // Create an Entity
    // Entity* ogreHead = mSceneMgr->createEntity("RZR", "RZR-002.mesh");
    Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
    // ogreHead->setMaterialName("MetalOgre/Skin");
    ogreHead->getSubEntity(0)->setMaterialName("CustomOgre/Eyes");
    ogreHead->getSubEntity(1)->setMaterialName("CustomOgre/Skin");
    ogreHead->getSubEntity(2)->setMaterialName("CustomOgre/Earring");
    ogreHead->getSubEntity(3)->setMaterialName("CustomOgre/Tusks");
    
    // Create a SceneNode and attach the Entity to it
    SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
    headNode->attachObject(ogreHead);
    headNode->scale(0.25, 0.25, 0.25);

    // Create a Light and set its pos
    Light* mainLight = mSceneMgr->createLight("MainLight");
    mainLight->setType(Light::LT_POINT);
    mainLight->setPosition(Vector3(250, 150, 250));
    mainLight->setDiffuseColour(ColourValue::White);
    mainLight->setSpecularColour(ColourValue::White);
}

bool MainApplication::processUnbufferedInput(const FrameEvent& evt)
{
    static bool mMouseDown = false; // if mouse button is pressed
    static Real mToggle = 0.0;      // time left until next toggle
    static Real mRotate = 0.13;     // rotation constant
    static Real mMove = 250;        // movement constant
    
    bool currMouse = mMouse->getMouseState().buttonDown(OIS::MB_Left);
    
    if(currMouse && !mMouseDown)
    {
        Light * light = mSceneMgr->getLight("MainLight");
        light->setVisible(!light->isVisible());
    }
    
    mMouseDown = currMouse;
    
    // mToggle -= evt.timeSinceLastFrame;
    
    return true;
}

bool MainApplication::frameRenderingQueued(const FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);

    if(!processUnbufferedInput(evt))
        return false;

    return ret;
}


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
