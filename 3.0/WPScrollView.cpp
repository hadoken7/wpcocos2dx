//
//  WPScrollView.cpp
//  Poker
//
//  Created by 王鹏 on 14-3-26.
//
//

#include "WPScrollView.h"
#include "../Utils/CommonUtils.h"


void WPScrollViewDelegate::scrollViewMoved(Touch* touch)
{
    
}


WPScrollView::~WPScrollView()
{
    _eventDispatcher -> removeEventListener(_touchListener);
}

bool WPScrollView::init()
{
//    if (!LayerColor::initWithColor(Color4B(100, 100, 100, 100),  kWIN_SIZE_WIDTH, kWIN_SIZE_HEIGHT)) {
    if (!Layer::init()) {
        return false;
    }
    _openDelegate = true;
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = CC_CALLBACK_2(WPScrollView::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(WPScrollView::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(WPScrollView::onTouchEnded, this);
    _touchListener->onTouchCancelled = CC_CALLBACK_2(WPScrollView::onTouchCancelled, this);
    _eventDispatcher -> addEventListenerWithFixedPriority(_touchListener, 200);
    
    return true;
}

bool WPScrollView::onTouchBegan(Touch* touch, Event* event)
{
    _beganPoint = touch -> getLocation();
    _noBadTouch = true;
    if (_beganPoint.y >= 200) {
        _noBadTouch = false;
    }
    
    return true;
}
void WPScrollView::onTouchEnded(Touch* touch, Event* event)
{
    if (_openDelegate && _delegate != NULL ) {
        Point beginPoint = _beganPoint;
        Point endPoint = touch -> getLocation();
        float x = endPoint.x - _beganPoint.x;
        float y = endPoint.y - _beganPoint.y;
        float sin = y/sqrtf(x*x+y*y);
        float disSq = 80 * 80;
        float pointDisSq = (beginPoint - endPoint).getLengthSq();
        if (sin>=0.5 && pointDisSq > disSq)
        {
            if (_delegate) {//向上
                _delegate -> scrollViewUpMove();
            }
        }
        else if(sin>-0.5&&sin<0.5&&x>0 && pointDisSq > disSq){
            if (_delegate) {//向前
                _delegate -> scrollViewLeftToRight();
            }
        }
        else if (sin<=-0.5 && pointDisSq > disSq) {
            if (_delegate) {//向下
                _delegate -> scrollViewDownMove();
            }
        }
        else if (sin>-0.5&&sin<0.5&&x<0 && pointDisSq > disSq) {
            if (_delegate) {//向后
                _delegate -> scrollViewRightToLeft();
            }
        }
        else {
            if (_delegate) {
                _delegate -> scrollViewTip();
            }
        }
    }
}

void WPScrollView::onTouchCancelled(Touch* touch, Event* event)
{
    
}

void WPScrollView::onTouchMoved(Touch* touch, Event* event)
{
    if (_noBadTouch) {
        Point p = touch -> getLocation();
        if (p.y <= _beganPoint.y) {
            _noBadTouch = false;
        }
    }
}