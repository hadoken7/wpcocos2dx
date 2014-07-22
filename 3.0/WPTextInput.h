//
//  WPTextInput.h
//  Poker
//
//  Created by YoceGames on 14-7-2.
//
//

#ifndef __Poker__WPTextInput__
#define __Poker__WPTextInput__

#include <iostream>
#include "ui/CocosGUI.h"
using namespace std;
using namespace cocos2d;

class WPTextInput : public ui::TextField {
public:
    
    WPTextInput();
    static WPTextInput * create(const std::string &placeholder, const std::string &fontName, int fontSize);
    //
    // 显示光标
    //
    void setShowCursor(bool show);
    //
    // 设置文字
    //
    virtual void setText(const std::string &text);
    
    virtual void update(float time);
    
    virtual void onEnter();
    virtual void onExit();
    
    //
    // 提示文字颜色
    //
    virtual void setPlaceHolderColor(const Color3B &color);
    //
    // 文字颜色
    //
    virtual void setTextColor(const Color3B &color);
    
    // 发送开启通知
    virtual void attachWithIMEEvent();
    // 发送关闭通知
    virtual void detachWithIMEEvent();
    // 设置为焦点
    void setFocus(bool focus);
protected:
    LayerColor * _cursorSprite;
    bool _showCursor;
    
};

#endif /* defined(__Poker__WPTextInput__) */
