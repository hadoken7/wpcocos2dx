//
//  WPLayer.h
//  CrazyRun
//
//  Created by WangPeng on 13-11-7.
//
//

#ifndef __CrazyRun__WPLayer__
#define __CrazyRun__WPLayer__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

/*
 *
 * 所有Layer都要继承此Layer 方便触摸管理
 *
 *
 */

class WPLayer : public Layer {
    
public:
    CREATE_FUNC(WPLayer);
    virtual bool init();
    ~WPLayer();
    WPLayer();
    //
    // 添加触碰的menu
    //
    void pushMenu(Menu *menu);
    void popMenu(Menu *menu);
    //
    // 添加触碰scrollerView
    //
    void pushScrollView(ScrollView * scrollView);
    void popScrollView(ScrollView * scrollView);
    //
    // 替换页面
    //
    virtual void replaceLayer(WPLayer *layer);
    //
    // 压栈
    //
    virtual void pushWPLayer(WPLayer *layer);
    //
    // 弹栈
    //
    virtual void popWPLayer();
    //
    //
    //
    virtual void popWPLayer(WPLayer * layer);
    //
    // 关闭当前页触摸
    //
    virtual void closeAllTouch();
    //
    // 开启当前页面触摸
    //
    virtual void openAllTouch();
    //
    // 获取最顶层Layer
    //
    WPLayer * getTopLayer();
    //
    // 清空所有WPLayer , 并push新的WPLayer;
    //
    void resetWPLayer(WPLayer *layer);
    //
    // 添加,删除触摸
    //
    void setCanOnTouch(bool can,int priority = 1);
    //
    // 添加键盘监听(安卓)
    //
    void setCanOnKeyboardTouch(bool can);
    
    
protected:
    
    bool _isOpenTouch;
    int _touchPriority;
    
    virtual bool onTouchBegan(Touch* touch, Event* event){return true;};
    virtual void onTouchEnded(Touch* touch, Event* event){};
    virtual void onTouchCancelled(Touch* touch, Event* event){};
    virtual void onTouchMoved(Touch* touch, Event* event){};
    
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){};
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){};
    
    void addWPTouchOneByOne(int priority);
    void removeWPTouchOneByOne();
    
    
    EventListenerTouchOneByOne *_wpTouchListener;
    EventListenerKeyboard      *_wpKeyboardListener;
    __Array *_layerArray;
    __Array *_scrollViewArray;
    
    void setTouchEnable(bool touch);
};



#endif /* defined(__CrazyRun__WPLayer__) */
