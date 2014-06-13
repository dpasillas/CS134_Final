#include "item.h"
#include <cstdlib>
#include <iostream>

using namespace Ogre;

unsigned int Item::id = 0;
std::vector<Item*> Item::items = std::vector<Item*>();
Item::ItemListener* Item::listener = new ItemListener();
std::map<std::string, Item*> Item::itemsByName = std::map<std::string, Item*>();
std::queue<Item*> Item::deletionQueue = std::queue<Item*>();

Item::Item(SceneManager* mSceneMgr) : mSceneMgr(mSceneMgr) {

    // Create an Entity
    char buf[256];
    std::string idTag = std::string("") + id++;
    
    items.push_back(this);
}

void Item::updateAll(Real dt) {
    for(int i = 0, _i = items.size(); i < _i; ++i) {
        Item* p = items[i];
        p->update(dt);
    }
}

void Item::init() {
    name = getUniqueName(getPrefix());   
    itemsByName[name];
}

void Item::setNode(SceneNode* node) {
    this->node = node;
}

std::string Item::getUniqueName(std::string prefix) {
    char buf[256];
    std::string idTag = std::string("") + id++;
    return prefix + idTag;
}

void Item::checkCollisions(SceneManager* mSceneMgr) {
    IntersectionSceneQuery* query = mSceneMgr->createIntersectionQuery();
    query->execute(listener);

    mSceneMgr->destroyQuery(query);    
}

Item* Item::findByName(std::string name) {
    if(itemsByName.count(name))
        return itemsByName[name];
    return 0;
}

bool Item::ItemListener::queryResult(Ogre::MovableObject *first, Ogre::MovableObject *second) {
    std::string fname = first->getName();
    std::string sname = second->getName();
    if(fname == "Player") {
        Item* item = Item::findByName(sname);
        if(item)
            return item->playerCollision();
    } else if(sname == "Player") {
        Item* item = Item::findByName(fname);
        if(item)
            return item->playerCollision();
    }
    return true;
}


bool Item::ItemListener::queryResult(Ogre::MovableObject*, Ogre::SceneQuery::WorldFragment*) {
    return true;
}
