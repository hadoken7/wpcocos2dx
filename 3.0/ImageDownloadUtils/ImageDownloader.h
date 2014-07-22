//
//  ImageDownloader.h
//  Poker
//
//  Created by WangPeng on 14-5-19.
//
//

#ifndef __Poker__ImageDownloader__
#define __Poker__ImageDownloader__

#include <iostream>
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"

using namespace cocos2d::network;
class ImageDownloader;

class ImageDownloaderDelegate {
public:
    virtual void downloadImageDone(bool success,const char * name,const char *url,ImageDownloader *downloader) = 0;
};

class ImageDownloader : public Ref {
    
public:
    static ImageDownloader * createWithUrlAndName(const char *url,const char *name,ImageDownloaderDelegate *delegate);
    virtual bool initWithUrlAndName(const char *url,const char *name,ImageDownloaderDelegate *delegate);
protected:
    
    void imageCallback(HttpClient* client, HttpResponse* response);
    
    std::string _url;
    std::string _name;
    ImageDownloaderDelegate *_delegate;
};

#endif /* defined(__Poker__ImageDownloader__) */
