//
//  WPMenu.cpp
//  Poker
//
//  Created by WangPeng on 14-3-19.
//
//

#include "WPMenu.h"

#define kDISTANCE_SEQ      40

WPMenu::~WPMenu()
{
    _eventDispatcher -> removeEventListener(_listener);
}


WPMenu * WPMenu::create(int priority)
{
    WPMenu * pRet = new WPMenu;
    pRet -> _priority = priority;
    if (pRet && pRet -> init()) {
        pRet -> autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool WPMenu::init()
{
    return initWithArray(Vector<MenuItem*>());
}

bool WPMenu::initWithArray(const Vector<MenuItem*>& arrayOfItems)
{
    if (Layer::init())
    {
        _enabled = true;
        // menu in the center of the screen
        Size s = Director::getInstance()->getWinSize();
        
        this->ignoreAnchorPointForPosition(true);
        
        setAnchorPoint(Point(0.5f, 0.5f));
        this->setContentSize(s);
        
        setPosition(Point(s.width/2, s.height/2));
        
        int z=0;
        
        for (auto& item : arrayOfItems)
        {
            this->addChild(item, z);
            z++;
        }
        
        _selectedItem = nullptr;
        _state = Menu::State::WAITING;
        
        // enable cascade color and opacity on menus
        setCascadeColorEnabled(true);
        setCascadeOpacityEnabled(true);
        
        
        _listener = EventListenerTouchOneByOne::create();
        _listener->setSwallowTouches(true);
        
        _listener->onTouchBegan = CC_CALLBACK_2(Menu::onTouchBegan, this);
        _listener->onTouchMoved = CC_CALLBACK_2(Menu::onTouchMoved, this);
        _listener->onTouchEnded = CC_CALLBACK_2(Menu::onTouchEnded, this);
        _listener->onTouchCancelled = CC_CALLBACK_2(Menu::onTouchCancelled, this);
        _eventDispatcher -> addEventListenerWithFixedPriority(_listener, _priority);

        return true;
    }
    return false;
}

void WPMenu::onEnter()
{
    Menu::onEnter();
}

void WPMenu::onExit()
{
    Menu::onExit();
}

bool WPMenu::onTouchBegan(Touch* touch, Event* event)
{
    bool ans = Menu::onTouchBegan(touch, event);
    if (ans) {
        _startPoint = touch->getLocationInView();
    }
    return ans;
}

void WPMenu::onTouchEnded(Touch* touch, Event* event)
{
    this -> retain();
    if (!_isMoving) {
        Menu::onTouchEnded(touch,event);
    }
    else {
        if (_selectedItem)
        {
            _selectedItem->unselected();
        }
        _state = Menu::State::WAITING;
    }
    _isMoving = false;
    this -> release();
}

void WPMenu::onTouchCancelled(Touch* touch, Event* event)
{
    Menu::onTouchCancelled(touch,event);
}

void WPMenu::onTouchMoved(Touch* touch, Event* event)
{
    if (!_isMoving) {
        Point endPoint = touch -> getLocationInView();
        float dis = (endPoint.getDistanceSq(_startPoint));
        if (dis > kDISTANCE_SEQ) {
            _isMoving = true;
        }
        else {
            Menu::onTouchMoved(touch,event);
        }
    }
}