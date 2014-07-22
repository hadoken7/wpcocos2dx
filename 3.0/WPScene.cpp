//
//  WPScene.cpp
//  CrazyRun
//
//  Created by WangPeng on 13-11-7.
//
//

#include "WPScene.h"

WPScene::~WPScene()
{
    CC_SAFE_RELEASE(_layerArray);
}

bool WPScene::init()
{
    if (!CCScene::init()) {
        return false;
    }
    _layerArray = __Array::create();
    _layerArray -> retain();
    return true;
}


void WPScene::pushLayer(WPLayer * layer)
{
    if (_layerArray -> count()) {
        WPLayer * lastLayer = (WPLayer *)_layerArray -> getLastObject();
        lastLayer -> closeAllTouch();
    }
    _layerArray -> addObject(layer);
    layer -> openAllTouch();
    this -> addChild(layer, (int)_layerArray -> count(), (int)_layerArray -> count());
}

void WPScene::popLayer()
{
    WPLayer * layer = (WPLayer *)_layerArray -> getLastObject();
    if (layer -> getParent() == this) {
        layer -> closeAllTouch();
        this -> removeChild(layer, true);
    }
    _layerArray -> removeLastObject();
    if (_layerArray -> count()) {
        WPLayer * lastLayer = (WPLayer *)_layerArray -> getLastObject();
        lastLayer -> openAllTouch();
    }
}

void WPScene::popLayer(WPLayer * layer)
{
    if (_layerArray -> containsObject(layer)) {
        if (layer -> getParent() == this) {
            layer -> closeAllTouch();
            this -> removeChild(layer, true);
        }
        _layerArray -> removeObject(layer);
    }
    if (_layerArray -> count()) {
        WPLayer * lastLayer = (WPLayer *)_layerArray -> getLastObject();
        lastLayer -> openAllTouch();
    }
}

void WPScene::replaceLayer(WPLayer * layer)
{
    WPLayer * last = (WPLayer *)_layerArray -> getLastObject();
    if (last) {
        last -> retain();
    }
    this -> popLayer();
    this -> pushLayer(layer);
    if (last) {
        last -> release();
    }
}

void WPScene::resetRootLayer(WPLayer * layer)
{
    while (_layerArray -> count()) {
        WPLayer * layer = (WPLayer *)_layerArray -> getLastObject();
        _layerArray -> removeLastObject();
        this -> removeChild(layer, true);
    }
    pushLayer(layer);
}

WPLayer * WPScene::getTopLayer()
{
    if (_layerArray -> count()) {
        return (WPLayer *)_layerArray -> getLastObject();
    }
    return NULL;
}
