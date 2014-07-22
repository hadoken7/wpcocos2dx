//
//  WPMenu.h
//  Poker
//
//  Created by WangPeng on 14-3-19.
//
//

#ifndef __Poker__WPMenu__
#define __Poker__WPMenu__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class WPMenu : public Menu  {
    
public:
    ~WPMenu();
    static WPMenu * create(int pro = 2);
    virtual bool init();
    bool initWithArray(const Vector<MenuItem*>& arrayOfItems);
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchCancelled(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    
    Point _startPoint;
    bool _isMoving;
    
    EventListenerTouchOneByOne *_listener;
    
    int _priority;
};

#endif /* defined(__Poker__WPMenu__) */
