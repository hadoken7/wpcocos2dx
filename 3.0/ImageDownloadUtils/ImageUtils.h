//
//  ImageUtils.h
//  Poker
//
//  Created by WangPeng on 14-4-15.
//
//

#ifndef __Poker__ImageUtils__
#define __Poker__ImageUtils__

#include <iostream>
#include "cocos2d.h"
#include "ImageDownloader.h"
using namespace std;
using namespace cocos2d;

class ImageUtilsDelegate {
public:
    virtual void imageDownloadDone(const char * key,bool success) = 0;
};

class ImageUtils : public Ref ,public ImageDownloaderDelegate {
public:
    static ImageUtils * getInstance();
    
    std::string getFullNameImage(const char * imageName);
    
    bool getImageFileExistWithName(const char * imageName);
    
    void donwloadImage(const char * imageUrl,const char * imageName);
    
    void callBack(const char * ref,bool success);
    
    void addImageDelegate(ImageUtilsDelegate * delegate);
    void removeImageDelegate(ImageUtilsDelegate * delegate);
    
    virtual void downloadImageDone(bool success,const char * name,const char *url,ImageDownloader *downloader);

protected:
    vector<ImageUtilsDelegate *> _delegateVector;
    vector<std::string> _imageUrlVector;
};

#endif /* defined(__Poker__ImageUtils__) */
