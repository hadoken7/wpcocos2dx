//
//  WPScrollView.h
//  Poker
//
//  Created by 王鹏 on 14-3-26.
//
//

#ifndef __Poker__WPScrollView__
#define __Poker__WPScrollView__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class WPScrollViewDelegate
{
public:
    virtual void scrollViewMoved(Touch* touch);
    virtual void scrollViewUpMove(){};
    virtual void scrollViewDownMove(){};
    virtual void scrollViewLeftToRight(){};
    virtual void scrollViewRightToLeft(){};
    virtual void scrollViewTip(){};
};

class WPScrollView : public Layer {
public:
    CREATE_FUNC(WPScrollView);
    ~WPScrollView();
    virtual bool init();
    //
    // 是否开启委托 默认开启
    //
    void openDelegate(bool open){
        _openDelegate = open;
    };
    void setDelegate(WPScrollViewDelegate * delegate){
        _delegate = delegate;
    };
    
protected:
    
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchCancelled(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    
    
    WPScrollViewDelegate *_delegate;
    
    EventListenerTouchOneByOne *_touchListener;
    
    // 向上滑动
    Point _beganPoint;
    bool _noBadTouch;
    // 委托开启
    bool _openDelegate;
    
};

#endif /* defined(__Poker__WPScrollView__) */
