//
//  WPNetSprite.cpp
//  Poker
//
//  Created by WangPeng on 14-7-7.
//

#include "WPNetSprite.h"

WPNetSprite::~WPNetSprite()
{
    ImageUtils::getInstance() -> removeImageDelegate(this);
}

bool WPNetSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    _useDefaultImage = true;
    _defaultImage = "";
    _defaultSize = Size::ZERO;
    return true;
}
// 以固定图片创建
WPNetSprite* WPNetSprite::create(const std::string& filename)
{
    WPNetSprite *sprite = new WPNetSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
    }
    else {
        CC_SAFE_DELETE(sprite);
    }
    return sprite;
}

bool WPNetSprite::initWithFile(const std::string& filename)
{
    if (!Sprite::initWithFile(filename)) {
        return false;
    }
    _useDefaultImage = true;
    _defaultImage = filename;
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(_defaultImage);
    if (texture){
//        _defaultSize = texture->getContentSize();
    }
    return true;
}

void WPNetSprite::imageDownloadDone(const char * key,bool success)
{
    if (key == _imageUrlKey) {
        if (success) {
            _useDefaultImage = false;
            setTextureWithFilePath(getFullImagePath(key),true);
        }
        else {
            //下载失败
        }
    }
}

void WPNetSprite::setFullImageUrl(const std::string &imagerUrl,const std::string key)
{
    if (!imagerUrl.length()) {
        resumeDefaultImage();
        return;
    }
    //
    // 路径全称
    //
    string filePath = getFullImagePath(key);
    //
    // 是否已经下载
    //
    bool hasDone = ImageUtils::getInstance() -> getImageFileExistWithName(key.c_str());
    if (hasDone) {
        _useDefaultImage = false;
        setTextureWithFilePath(filePath);
    }
    else {
        if (_imageUrlKey != key) {
            _imageUrlKey = key;
            // 下载
            ImageUtils::getInstance() -> addImageDelegate(this);
            ImageUtils::getInstance() -> donwloadImage(imagerUrl.c_str(),_imageUrlKey.c_str());
            //
            if (!_useDefaultImage) {
                resumeDefaultImage();
            }
        }
    }
}

void WPNetSprite::setTextureWithFilePath(const std::string &path,bool net)
{
    setTexture(path);
    if (!_defaultSize.equals(Size::ZERO)) {
        setImageContentSize(_defaultSize);
    }
}

//
// 设置图片大小
//
void WPNetSprite::setImageContentSize(Size size)
{
    _defaultSize = size;
    this -> setScaleX(_defaultSize.width/this -> getContentSize().width);
    this -> setScaleY(_defaultSize.height/this -> getContentSize().height);
}
//
// 恢复默认图片
//
void WPNetSprite::resumeDefaultImage()
{
    _useDefaultImage = true;
    setTextureWithFilePath(_defaultImage);
}

std::string WPNetSprite::getFullImagePath(const std::string &imageName)
{
    return FileUtils::getInstance()->getWritablePath() + imageName;
}
