//
//  WPTextInput.cpp
//  Poker
//
//  Created by YoceGames on 14-7-2.
//
//

#include "WPTextInput.h"

WPTextInput::WPTextInput()
:_cursorSprite(nullptr)
,_showCursor(false)
{
    
}

WPTextInput * WPTextInput::create(const std::string &placeholder, const std::string &fontName, int fontSize)
{
    WPTextInput* widget = new WPTextInput();
    if (widget && widget->init())
    {
        widget->setTouchEnabled(true);
        widget->setPlaceHolder(placeholder);
        widget->setFontName(fontName);
        widget->setFontSize(fontSize);
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}


void WPTextInput::onEnter()
{
    ui::TextField::onEnter();
    if (_showCursor) {
        Blink * blink = Blink::create(10000, 10000);
        _cursorSprite -> runAction(blink);
    }
}

void WPTextInput::onExit()
{
    ui::TextField::onExit();
    if (_cursorSprite) {
        _cursorSprite -> stopAllActions();
    }
}


void WPTextInput::setShowCursor(bool show)
{
    if (_showCursor != show) {
        _showCursor = show;
        if (_showCursor) {
            if (!_cursorSprite) {
                _cursorSprite = LayerColor::create(Color4B(0, 118, 255, 255), 3, getFontSize() + 7);
                this -> addChild(_cursorSprite,3);
                Blink * blink = Blink::create(10000, 10000);
                _cursorSprite -> runAction(blink);
            }
        }
        else {
            if (_cursorSprite) {
                _cursorSprite -> setVisible(false);
                _cursorSprite -> stopAllActions();
            }
        }
    }
}

void WPTextInput::setText(const std::string &text)
{
    ui::TextField::setText(text);
    Size size = _textFieldRenderer->getContentSize();
    if (_cursorSprite) {
        _cursorSprite -> setPosition(size.width,0);
    }
}

void WPTextInput::update(float time)
{
    ui::TextField::update(time);
    if (getStringValue().length() > 0) {
        Size size = _textFieldRenderer->getContentSize();
        if (_cursorSprite) {
            _cursorSprite -> setPosition(size.width,0);
        }
    }
    else {
        if (_cursorSprite) {
            _cursorSprite -> setPosition(0,0);
        }
    }
}

void WPTextInput::setFocus(bool focus)
{
    if (_showCursor) {
        _cursorSprite -> setVisible(focus);
        if (focus) {
            _cursorSprite -> runAction(Blink::create(10000, 10000));
        }
        else {
            _cursorSprite -> stopAllActions();
        }
        
    }
}

void WPTextInput::setPlaceHolderColor(const Color3B &color)
{
    _textFieldRenderer -> setColorSpaceHolder(Color4B(color.r, color.g, color.b, 255));
    setColor(color);
}

void WPTextInput::setTextColor(const Color3B &color)
{
    _textFieldRenderer -> setTextColor(Color4B(color.r, color.g, color.b, 255));
}

//void WPTextInput::attachWithIME()
//{
//    ui::TextField::attachWithIME();
//    setFocus(true);
//}
//void WPTextInput::didNotSelectSelf()
//{
//    ui::TextField::didNotSelectSelf();
//    setFocus(false);
//}

void WPTextInput::attachWithIMEEvent()
{
    ui::TextField::attachWithIMEEvent();
    setFocus(true);
}
void WPTextInput::detachWithIMEEvent()
{
    ui::TextField::detachWithIMEEvent();
    setFocus(false);
}




