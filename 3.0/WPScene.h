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
#include "extensions/cocos-ext.h"
#include "WPLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

/*
 *
 * 所有scene都要继承此scene 方便触摸管理
 * 以及WPLayer之间的切换
 *
 */

class WPScene : public Scene
{
    
public:
    ~WPScene();
    virtual bool init();

    CREATE_FUNC(WPScene);
    //
    // 添加layer触碰的权限
    //
    void pushLayer(WPLayer * layer);
    //
    // 移除layer触碰权利
    //
    void popLayer();
    void popLayer(WPLayer * layer);
    //
    // 替换
    //
    void replaceLayer(WPLayer * layer);
    //
    // pop all layer and push new wplayer
    //
    void resetRootLayer(WPLayer * layer);
    //
    //
    //
    WPLayer * getTopLayer();

protected:
    
private:
    __Array *_layerArray;
};

#endif /* defined(__CrazyRun__WPScene__) */
