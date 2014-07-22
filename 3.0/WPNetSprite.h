//
//  WPNetSprite.cpp
//  Poker
//
//  Created by WangPeng on 14-7-7.
//

#ifndef __Poker__WPNetSprite__
#define __Poker__WPNetSprite__

#include <iostream>
#include "cocos2d.h"
#include "../Utils/ImageUtils.h"
using namespace std;
using namespace cocos2d;
//
// 下载图片,并在下载完成后显示
//
class WPNetSprite : public Sprite ,public ImageUtilsDelegate{
public:
    ~WPNetSprite();
    // 创建透明
    CREATE_FUNC(WPNetSprite);
    virtual bool init();
    // 以固定图片创建
    static WPNetSprite* create(const std::string& filename);
    virtual bool initWithFile(const std::string& filename);
    //
    // 图片下载回调
    //
    virtual void imageDownloadDone(const char * key,bool success);
    //
    // 设置图片全路径,以及唯一key(默认使用图片命)
    //
    void setFullImageUrl(const std::string &imagerUrl,const std::string key);
    //
    // 设置图片大小
    //
    void setImageContentSize(Size size);
    //
    // 恢复默认图片
    //
    void resumeDefaultImage();
protected:
    //
    // 本地文件
    //
    std::string getFullImagePath(const std::string &imageName);
    //
    // 设置纹理
    //
    void setTextureWithFilePath(const std::string &path,bool net = false);
    //
    // 默认图片 大小
    //
    std::string _defaultImage;
    Size _defaultSize;
    bool _useDefaultImage;
    std::string _imageUrlKey;
};

#endif /* defined(__Poker__WPNetSprite__) */
