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
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ArrayLayerMenu : public CCObject
{
public:
    CREATE_FUNC(ArrayLayerMenu);
    bool init(){return true;};
    CCLayer *_layer;
    bool _isMenu;
};

/*
 *
 * 所有Layer都要继承此Layer 方便触摸管理
 *
 *
 */

class WPLayer : public CCLayer {
    
public:
    CREATE_FUNC(WPLayer);
    virtual bool init();
    ~WPLayer();
    //
    // 添加触碰的menu
    //
    void pushMenu(CCMenu *menu);
    //
    // 添加触碰scrollerView
    //
    void pushScrollView(CCScrollView * scrollView);
    
    //
    // 替换页面
    //
    void replaceLayer(WPLayer *layer);
    
    
    //
    // 压栈
    //
    void pushWPLayer(WPLayer *layer);
    
    //
    // 弹栈
    //
    void popWPLayer();
    
    //
    // 获取当前触碰点下的menu 或者 scrollView;
    //
    CCArray *getTouchLayer(CCTouch *pTouch);
    
    virtual void setContentSize(CCSize size);
    
protected:
    CCArray *_layerArray;
    CCArray *_scrollViewArray;
    
    CCMenuItem *_menuItem;
    
    void clickedNone(CCMenuItem * menuItem);
};



#endif /* defined(__CrazyRun__WPLayer__) */
