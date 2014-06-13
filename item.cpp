#include "item.h"
#include <cstdlib>

using namespace Ogre;

unsigned int Item::id = 0;
std::vector<Item*> Item::items = std::vector<Item*>();

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

void Item::setNode(SceneNode* node) {
    this->node = node;
}

std::string Item::getUniqueName(std::string prefix) {
    char buf[256];
    std::string idTag = std::string("") + id++;
    return prefix + idTag;
}
