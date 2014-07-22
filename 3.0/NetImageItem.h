//
//  NetImageItem.h
//  Poker
//
//  Created by WangPeng on 14-4-16.
//
//

#ifndef __Poker__NetImageItem__
#define __Poker__NetImageItem__

#include <iostream>
#include "cocos2d.h"
#include "../Utils/ImageUtils.h"
using namespace std;
using namespace cocos2d;
//
// 下载图片,并在下载完成后显示
//
class NetImageItem : public MenuItemImage ,public ImageUtilsDelegate{
public:
    ~NetImageItem();
    //
    // 创建并设置默认图片
    //
    static NetImageItem * createWithImage(const std::string &str);
    //
    // 设置图片全路径,以及唯一key(默认使用图片命)
    //
    void setFullImageUrl(const std::string &imagerUrl,const std::string key);
    //
    // 设置图片头像路径,玩家id ,char 'c'(针对头像下载)
    // @param imageurl          玩家头像地址
    // @param gameid            玩家id
    // @param type              '0' 代表小头像, '1' 代表大头像
    //
    void setImageUrl(const std::string &imageurl,int gameid, char type);
    //
    // 图片下载完成后回调
    //
    virtual void imageDownloadDone(const char * key,bool success);
    //
    // 生成key
    //
    static std::string getImageUrlKey(const std::string &imageurl,int gameid, char type);
    //
    // 设置图片大小
    //
    void setImageContentSize(Size size);
    //
    // 恢复默认图片
    //
    void resumeDefaultImage();
protected:
    virtual bool initWithImage(const std::string &str);
    std::string _imageUrlKey;
    //
    // 拼接字符串
    //
    std::string getFullImageUrl(const std::string &imageurl,int gameid, char type);
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
};

#endif /* defined(__Poker__NetImageItem__) */
