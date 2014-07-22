//
//  WPScene.h
//  CrazyRun
//
//  Created by WangPeng on 13-11-7.
//
//

#ifndef __CrazyRun__WPScene__
#define __CrazyRun__WPScene__

#include <iostream> 
#include "cocos2d.h"
#include "cocos-ext.h"
#include "../Layer/WPLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

/*
 *
 * 所有scene都要继承此scene 方便触摸管理
 * 
 *
 */

class WPScene :public CCScene ,public CCTouchDelegate
{
    
public:
    
    CREATE_FUNC(WPScene);
    //
    // 添加layer触碰的权限
    //
    void pushLayer(WPLayer * layer);
    //
    // 移除layer触碰权利
    //
    void popLayer();
    //
    // 替换
    //
    void replaceLayer(WPLayer * layer);
    
    virtual void onEnter();
    virtual void onExit();
    
    //
    // show hide Loading
    //
//    void showLoading();
//    void hideLoading();

protected:
    ~WPScene();
    virtual bool init();
private:
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    CCArray *getTouchLayer(CCTouch *pTouch);
    
    
    CCArray *_layerArray;
    
    CCMenu *_currentMenu;
    CCScrollView *_currentScrollView;
};

#endif /* defined(__CrazyRun__WPScene__) */
