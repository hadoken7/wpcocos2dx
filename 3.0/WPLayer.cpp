//
//  WPLayer.cpp
//  CrazyRun
//
//  Created by WangPeng on 13-11-7.
//
//

#include "WPLayer.h"
#include "WPScene.h"


WPLayer::~WPLayer()
{
    CC_SAFE_RELEASE(_layerArray);
    CC_SAFE_RELEASE(_scrollViewArray);
    removeWPTouchOneByOne();
    setCanOnKeyboardTouch(false);
}

WPLayer::WPLayer()
:_wpTouchListener(nullptr)
,_layerArray(nullptr)
,_scrollViewArray(nullptr)
,_wpKeyboardListener(nullptr)
,_isOpenTouch(false)
{
    
}

bool WPLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    _layerArray = __Array::create();
    _layerArray -> retain();
    
    _scrollViewArray = __Array::create();
    _scrollViewArray -> retain();
    
    
    return true;
}


void WPLayer::pushMenu(Menu *menu)
{
    if (!_layerArray -> containsObject(menu)) {
        _layerArray -> addObject(menu);
    }
}
void WPLayer::popMenu(cocos2d::Menu *menu)
{
    if (_layerArray -> containsObject(menu)) {
        _layerArray -> removeObject(menu);
    }
}

void WPLayer::pushScrollView(ScrollView * scrollView)
{
    if (!_scrollViewArray -> containsObject(scrollView)) {
        _scrollViewArray -> addObject(scrollView);
    }
}

void WPLayer::popScrollView(ScrollView * scrollView)
{
    if (_layerArray -> containsObject(scrollView)) {
        _layerArray -> removeObject(scrollView);
    }
}


void WPLayer::pushWPLayer(WPLayer *layer)
{
    WPScene * scene = (WPScene *)this -> getParent();
    if (scene) {
        bool isWPScene = dynamic_cast<WPScene*>(scene) != nullptr;
        CCASSERT(isWPScene,"WPLayer 's parent isn't a WPScene");
        scene -> pushLayer(layer);
    }
}

void WPLayer::popWPLayer()
{
    WPScene * scene = (WPScene *)this -> getParent();
    if (scene) {
        bool isWPScene = dynamic_cast<WPScene*>(scene) != nullptr;
        CCASSERT(isWPScene,"WPLayer 's parent isn't a WPScene");
        scene -> popLayer();
    }
}

void WPLayer::popWPLayer(WPLayer * layer)
{
    WPScene * scene = (WPScene *)this -> getParent();
    if (scene) {
        bool isWPScene = dynamic_cast<WPScene*>(scene) != nullptr;
        CCASSERT(isWPScene,"WPLayer 's parent isn't a WPScene");
        scene -> popLayer(layer);
    }
}

void WPLayer::replaceLayer(WPLayer *layer)
{
    WPScene * scene = (WPScene *)this -> getParent();
    if (scene) {
        bool isWPScene = dynamic_cast<WPScene*>(scene) != nullptr;
        CCASSERT(isWPScene,"WPLayer 's parent isn't a WPScene");
        scene -> replaceLayer(layer);
    }
}

void WPLayer::closeAllTouch()
{
    setTouchEnable(false);
}
void WPLayer::openAllTouch()
{
    setTouchEnable(true);
}

WPLayer * WPLayer::getTopLayer()
{
    WPScene * scene = (WPScene *)getParent();
    if (!scene) {
        return NULL;
    }
    bool isWPScene = dynamic_cast<WPScene*>(scene) != nullptr;
    CCASSERT(isWPScene,"WPLayer 's parent isn't a WPScene");
    return scene -> getTopLayer();
}

void WPLayer::setTouchEnable(bool touch)
{
    for (int i = 0; i < _layerArray -> count(); i++) {
        Menu * menu = (Menu *) _layerArray -> getObjectAtIndex(i);
        menu -> setEnabled(touch);
    }
    for (int i = 0 ; i < _scrollViewArray -> count(); i++) {
        ScrollView * scrollView = (ScrollView *)_scrollViewArray -> getObjectAtIndex(i);
        scrollView -> setTouchEnabled(touch);
    }
    if (touch) {
        if (_isOpenTouch) {
            setCanOnTouch(_isOpenTouch,_touchPriority);
        }
    }
    else {
        setCanOnTouch(false);
    }
}

void WPLayer::resetWPLayer(WPLayer *layer)
{
    WPScene * scene = (WPScene *)getParent();
    if (!scene) {
        CCASSERT(false,"WPLayer 's parent isn't a WPScene");
    }
    bool isWPScene = dynamic_cast<WPScene*>(scene) != nullptr;
    CCASSERT(isWPScene,"WPLayer 's parent isn't a WPScene");
    scene -> resetRootLayer(layer);
}

void WPLayer::setCanOnTouch(bool can,int priority)
{
    if (can) {
        addWPTouchOneByOne(priority);
    }
    else {
        removeWPTouchOneByOne();
    }
    _isOpenTouch = can;
    _touchPriority = priority;
}

void WPLayer::addWPTouchOneByOne(int priority)
{
    if (!_wpTouchListener) {
        _wpTouchListener = EventListenerTouchOneByOne::create();
        _wpTouchListener->setSwallowTouches(true);
        _wpTouchListener->onTouchBegan = CC_CALLBACK_2(WPLayer::onTouchBegan, this);
        _wpTouchListener->onTouchMoved = CC_CALLBACK_2(WPLayer::onTouchMoved, this);
        _wpTouchListener->onTouchEnded = CC_CALLBACK_2(WPLayer::onTouchEnded, this);
        _wpTouchListener->onTouchCancelled = CC_CALLBACK_2(WPLayer::onTouchCancelled, this);
        _eventDispatcher -> addEventListenerWithFixedPriority(_wpTouchListener, priority);
    }
}

void WPLayer::removeWPTouchOneByOne()
{
    if (_wpTouchListener) {
        _eventDispatcher -> removeEventListener(_wpTouchListener);
        _wpTouchListener = nullptr;
    }
}

void WPLayer::setCanOnKeyboardTouch(bool can)
{
    if (can) {
        if (!_wpKeyboardListener) {
            _wpKeyboardListener = EventListenerKeyboard::create();
            _wpKeyboardListener->onKeyPressed = CC_CALLBACK_2(WPLayer::onKeyPressed, this);
            _wpKeyboardListener->onKeyReleased = CC_CALLBACK_2(WPLayer::onKeyReleased, this);
            
            _eventDispatcher->addEventListenerWithSceneGraphPriority(_wpKeyboardListener, this);
        }
    }
    else if(_wpKeyboardListener){
        _eventDispatcher -> removeEventListener(_wpKeyboardListener);
        _wpKeyboardListener = nullptr;
    }
}
