#include "item.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace Ogre;

unsigned int Item::id = 0;
//std::vector<Item*> Item::items = std::vector<Item*>();
Item::ItemListener* Item::listener = new ItemListener();
std::map<std::string, Item*> Item::itemsByName = std::map<std::string, Item*>();
std::queue<Item*> Item::deletionQueue = std::queue<Item*>();

Item::Item(SceneManager* mSceneMgr) : mSceneMgr(mSceneMgr) {

    // Create an Entity
    char buf[256];
    std::string idTag = std::string("") + id++;
    
    //items.push_back(this);
}

void Item::updateAll(Real dt) {

    for(std::map<std::string, Item*>::iterator it = itemsByName.begin(); it != itemsByName.end(); ++it) {
        if(it->second)
            it->second->update(dt);
    }
    /*for(int i = 0, _i = items.size(); i < _i; ++i) {
        Item* p = items[i];
        p->update(dt);
    }*/
}

void Item::init() {
    name = getUniqueName(getPrefix());   
    itemsByName[name] = this;
}

void Item::queueForDeletion(Item* item) {
    deletionQueue.push(item);
}

void Item::setNode(SceneNode* node) {
    this->node = node;
}

std::string Item::getUniqueName(std::string prefix) {
    char buf[256];
    sprintf(buf, "%i", id++);
    std::string idTag = std::string("") + buf;
    return prefix + idTag;
}

void Item::checkCollisions(SceneManager* mSceneMgr) {
    IntersectionSceneQuery* query = mSceneMgr->createIntersectionQuery();
    query->execute(listener);

    mSceneMgr->destroyQuery(query);    
}

void Item::cleanup() {
    while(!deletionQueue.empty()) {
        Item *item = deletionQueue.front();
        deletionQueue.pop();
        itemsByName.erase(item->name);
        //items.erase(item);
        
        item->mSceneMgr->destroyMovableObject(item->node->getAttachedObject(0));
        delete item;
    }
}

Item* Item::findByName(std::string name) {
    if(itemsByName.count(name))
        return itemsByName[name];
    return 0;
}

bool Item::playerCollision() {
    return true;
}

bool Item::enemyCollision(Item* enemy) {
    return true;
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
    
    std::string fsname = fname.substr(0,std::min(5,(int)fname.size()));
    std::string ssname = sname.substr(0,std::min(5,(int)sname.size()));
    
    if(fsname == "Enemy") {
        Item* item = Item::findByName(sname);
        Item* enemy = Item::findByName(fname);
        if(item && enemy)
            return item->enemyCollision(enemy);
    } else if (ssname == "Enemy") {
        Item* item = Item::findByName(fname);
        Item* enemy = Item::findByName(sname);
        if(item && enemy)
            return item->enemyCollision(enemy);
    }
    return true;
}


bool Item::ItemListener::queryResult(Ogre::MovableObject*, Ogre::SceneQuery::WorldFragment*) {
    return true;
}
