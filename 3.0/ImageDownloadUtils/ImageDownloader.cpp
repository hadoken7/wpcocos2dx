//
//  ImageDownloader.cpp
//  Poker
//
//  Created by WangPeng on 14-5-19.
//
//

#include "ImageDownloader.h"


ImageDownloader * ImageDownloader::createWithUrlAndName(const char *url,const char *name,ImageDownloaderDelegate *delegate)
{
    ImageDownloader * pRet = new ImageDownloader();
    if (pRet && pRet -> initWithUrlAndName(url, name,delegate)) {
        pRet -> autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ImageDownloader::initWithUrlAndName(const char *url,const char *name,ImageDownloaderDelegate *delegate)
{
    _url = url;
    _name = name;
    if (_name.length() > 25) {
        CCLOG("%s",_name.c_str());
    }
    _delegate = delegate;
    if (!_url.length()) {
        return false;
    }
    HttpRequest * request = new HttpRequest;
    request -> setResponseCallback(this, httpresponse_selector(ImageDownloader::imageCallback));
    request -> setUrl(url);
    request -> setRequestType(HttpRequest::Type::GET);
    HttpClient::getInstance() -> send(request);
    return true;
}

void ImageDownloader::imageCallback(HttpClient* client, HttpResponse* response)
{
    bool success = true;
    if (response == NULL || response -> getResponseCode() != 200 || !response -> isSucceed()) {
        CCLOGERROR("(%s, %d) server return %d", __FILE__, __LINE__, response == NULL ? -1 : (int)response -> getResponseCode());
        success = false;
    }
    else {
        std::vector<char> *r_data = response -> getResponseData();
        
        unsigned char *data = new unsigned char [r_data -> size()];
        for (int i = 0; i < r_data -> size(); i++) {
            data[i]= r_data -> at(i);
        }
        Image * image = new Image();
        if (image -> initWithImageData(data, r_data -> size())){
            std::string fullpath = FileUtils::getInstance()->getWritablePath() + _name;
            image -> saveToFile(fullpath,false);
            image -> autorelease();
        }
        else {
            CC_SAFE_DELETE(image);
            success = false;
        }
        delete [] data;
    }
    if (_delegate) {
        _delegate -> downloadImageDone(success, _name.c_str(), _url.c_str(), this);
    }
}