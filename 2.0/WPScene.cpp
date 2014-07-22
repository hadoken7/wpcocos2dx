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
    _currentMenu = NULL;
    _currentScrollView = NULL;
    _layerArray = CCArray::create();
    _layerArray -> retain();
    return true;
}

void WPScene::onEnter()
{
    CCScene::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1023, true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, -1023);
}
void WPScene::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCScene::onExit();
    
}



void WPScene::pushLayer(WPLayer * layer)
{
    _currentMenu = NULL;
    _currentScrollView = NULL;
    _layerArray -> addObject(layer);
    this -> addChild(layer, _layerArray -> count(), _layerArray -> count());
}



void WPScene::popLayer()
{
    WPLayer * layer = (WPLayer *)_layerArray -> lastObject();
    _currentMenu = NULL;
    _currentScrollView = NULL;
    _layerArray -> removeLastObject();
    this -> removeChild(layer, true);
}

void WPScene::replaceLayer(WPLayer * layer)
{
    this -> popLayer();
    this -> pushLayer(layer);
}

CCArray *WPScene::getTouchLayer(CCTouch *pTouch)
{
    WPLayer *wpLayer = (WPLayer *)_layerArray -> lastObject();
    if (wpLayer) {
        return wpLayer -> getTouchLayer(pTouch);
    }
    
    return NULL;
}


bool WPScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
    _currentMenu = NULL;
    _currentScrollView = NULL;
    CCArray * array = getTouchLayer(pTouch);
    if (array) {
        for (int i = 0; i < array -> count(); i ++) {
            ArrayLayerMenu * t = (ArrayLayerMenu *) array -> objectAtIndex(i);
            if (t -> _isMenu) {
                _currentMenu = (CCMenu *)t -> _layer;
            }
            else {
                _currentScrollView = (CCScrollView *)t -> _layer;
            }
        }
        
    }
    bool menuTouch = false,scrollTouch = false;
    if (_currentScrollView) {
        if(!_currentScrollView -> ccTouchBegan(pTouch, pEvent)){
            _currentScrollView = NULL;
        }
        else {
            scrollTouch = true;
        }
    }
    if (_currentMenu) {
        if(!_currentMenu -> ccTouchBegan(pTouch, pEvent)){
            _currentMenu = NULL;
        }
        else {
            menuTouch = true;
        }
    }
    return true;
}

void WPScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (_currentScrollView) {
        _currentScrollView -> ccTouchMoved(pTouch, pEvent);
        CCPoint sp = pTouch -> getStartLocationInView();
        CCPoint ep = pTouch -> getLocationInView();
        float dis = 10;
        bool s = ccpDistanceSQ(sp, ep) > dis * dis;
        if (_currentMenu && s) {
            _currentMenu -> ccTouchCancelled(pTouch, pEvent);
            _currentMenu = NULL;
        }
    }
    else {
        if (_currentMenu) {
            _currentMenu -> ccTouchMoved(pTouch, pEvent);
        }
    }
    
}
void WPScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (_currentMenu) {
        _currentMenu -> ccTouchEnded(pTouch, pEvent);
    }
    if (_currentScrollView) {
        _currentScrollView -> ccTouchEnded(pTouch, pEvent);
    }
}
void WPScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (_currentMenu) {
        _currentMenu -> ccTouchCancelled(pTouch, pEvent);
    }
    if (_currentScrollView) {
        _currentScrollView -> ccTouchCancelled(pTouch, pEvent);
    }
}




void WPScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCLOG(" ccTouchesBegan ");
}
void WPScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCLOG(" ccTouchesMoved ");
}
void WPScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCLOG(" ccTouchesEnded ");
}
void WPScene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    CCLOG(" ccTouchesCancelled ");
}

