//
//  NetImageItem.cpp
//  Poker
//
//  Created by WangPeng on 14-4-16.
//
//

#include "NetImageItem.h"
#include "../Utils/CommonUtils.h"
#include "../Utils/PokerClient.h"
#include "../Utils/ImageUtils.h"

NetImageItem::~NetImageItem()
{
    ImageUtils::getInstance() -> removeImageDelegate(this);
}

NetImageItem * NetImageItem::createWithImage(const std::string &str)
{
    NetImageItem *pRet = new NetImageItem;
    if (pRet && pRet -> initWithImage(str)) {
        pRet -> autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void NetImageItem::setFullImageUrl(const std::string &imagerUrl,const std::string key)
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

void NetImageItem::setImageUrl(const std::string &imageurl,int gameid, char type)
{
    if (!imageurl.length()) {
        resumeDefaultImage();
        return;
    }
    string key = getImageUrlKey(imageurl, gameid, type);
    string url = getFullImageUrl(imageurl,gameid,type);
    setFullImageUrl(url, key);
}

void NetImageItem::setImageContentSize(Size size)
{
    _defaultSize = size;
    Sprite * normal = (Sprite *)getNormalImage();
    normal -> setScaleX(_defaultSize.width/normal -> getContentSize().width);
    normal -> setScaleY(_defaultSize.height/normal -> getContentSize().height);
}

void NetImageItem::resumeDefaultImage()
{
    _useDefaultImage = true;
    setTextureWithFilePath(_defaultImage);
}

bool NetImageItem::initWithImage(const std::string &str)
{
    if (!MenuItemImage::initWithNormalImage(str, str, "", NULL)) {
        return false;
    }
    _useDefaultImage = true;
    _defaultImage = str;
    _defaultSize = getNormalImage() -> getContentSize();
    return true;
}

void NetImageItem::imageDownloadDone(const char * key,bool success)
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

std::string NetImageItem::getImageUrlKey(const std::string &imageurl,int gameid, char type)
{
    std::string ans = "";
    ans += __String::createWithFormat("%d",gameid) -> getCString();
    ans += imageurl;
    ans += '_';
    ans += type;
    ans += ".jpg";
    return ans;
}

std::string NetImageItem::getFullImageUrl(const std::string &imageurl,int gameid, char type)
{
    std::string ans = kGET_SERVER_ADRESS ;
    ans += kDOWN_IMAGE_ADDRESS;
    ans += __String::createWithFormat("%d",gameid) -> getCString();
    ans += "/";
    ans += imageurl;
    ans += '_';
    ans += type;
    ans += ".jpg";
    return ans;
}

std::string NetImageItem::getFullImagePath(const std::string &imageName)
{
    return FileUtils::getInstance()->getWritablePath() + imageName;
}

void NetImageItem::setTextureWithFilePath(const std::string &path,bool net)
{
    Sprite * normal = (Sprite *)getNormalImage();
    normal -> setTexture(path);
    normal -> setScaleX(_defaultSize.width/normal -> getContentSize().width);
    normal -> setScaleY(_defaultSize.height/normal -> getContentSize().height);
    
    normal = (Sprite *)getSelectedImage();
    normal -> setTexture(path);
    normal -> setScaleX(_defaultSize.width/normal -> getContentSize().width);
    normal -> setScaleY(_defaultSize.height/normal -> getContentSize().height);
}