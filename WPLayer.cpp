//
//  WPLayer.cpp
//  CrazyRun
//
//  Created by WangPeng on 13-11-7.
//
//

#include "WPLayer.h"
#include "../Scene/WPScene.h"


WPLayer::~WPLayer()
{
    CC_SAFE_RELEASE(_layerArray);
    CC_SAFE_RELEASE(_scrollViewArray);
}

bool WPLayer::init()
{
    if (!CCNode::init()) {
        return false;
    }
    _layerArray = CCArray::create();
    _layerArray -> retain();
    
    _scrollViewArray = CCArray::create();
    _scrollViewArray -> retain();
    
    CCMenu * menu = CCMenu::create();
    _menuItem = CCMenuItem::create(this, menu_selector(WPLayer::clickedNone));
    
    pushMenu(menu);
    return true;
}

void WPLayer::setContentSize(CCSize size)
{
    CCNode::setContentSize(size);
    _menuItem -> setContentSize(size);
}

void WPLayer::pushMenu(CCMenu *menu)
{
    _layerArray -> addObject(menu);
}

void WPLayer::pushScrollView(CCScrollView * scrollView)
{
    _scrollViewArray -> addObject(scrollView);
}


void WPLayer::pushWPLayer(WPLayer *layer)
{
    WPScene * scene = (WPScene *)this -> getParent();
    scene -> pushLayer(layer);
}

void WPLayer::popWPLayer()
{
    WPScene * scene = (WPScene *)this -> getParent();
    scene -> popLayer();
}

void WPLayer::replaceLayer(WPLayer *layer)
{
    WPScene * scene = (WPScene *)this -> getParent();
    scene -> replaceLayer(layer);
}

CCArray * WPLayer::getTouchLayer(CCTouch *pTouch)
{
    CCPoint point = pTouch -> getLocation();
    CCArray * array = CCArray::create();
    
    for (int i = _layerArray -> count() - 1 ; i >= 0; i --) {
        CCMenu *ansLayer = (CCMenu *)_layerArray -> objectAtIndex(i);
        if (ansLayer -> itemForTouch(pTouch)) {
            ArrayLayerMenu * t = ArrayLayerMenu::create();
            t -> _isMenu = true;
            t -> _layer = ansLayer;
            array -> addObject(t);
            break;

        }
    }
    for (int i = _scrollViewArray -> count() - 1 ; i >= 0; i --) {
        CCScrollView *ansLayer = (CCScrollView *)_scrollViewArray -> objectAtIndex(i);
        if (ansLayer -> boundingBox().containsPoint(point)) {
            ArrayLayerMenu * t = ArrayLayerMenu::create();
            t -> _isMenu = false;
            t -> _layer = ansLayer;
            array -> addObject(t);
            break;
        }
    }
    if (array -> count()) {
        return array;
    }
    return NULL;
}

void WPLayer::clickedNone(CCMenuItem * menuItem)
{
    CCLOG(" clicked None");
}
