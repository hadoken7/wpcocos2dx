//
//  ImageUtils.cpp
//  Poker
//
//  Created by WangPeng on 14-4-15.
//
//

#include "ImageUtils.h"


static ImageUtils * _shared = NULL;

ImageUtils * ImageUtils::getInstance()
{
    if (!_shared) {
        _shared = new ImageUtils;
    }
    return _shared;
}


std::string ImageUtils::getFullNameImage(const char * imageName)
{
    std::string ans = FileUtils::getInstance() -> getWritablePath() + imageName;
    return ans;
}

bool ImageUtils::getImageFileExistWithName(const char *imageName)
{
    std::string fullname = getFullNameImage(imageName);
    return FileUtils::getInstance() -> isFileExist(fullname);
}

void ImageUtils::donwloadImage(const char * imageUrl,const char * imageName)
{
    for (int i = 0; i < _imageUrlVector.size(); i++) {
        if (imageName == _imageUrlVector.at(i)) {
            return;
        }
    }
    _imageUrlVector.push_back(imageName);
    ImageDownloader * downloader = ImageDownloader::createWithUrlAndName(imageUrl, imageName,(ImageDownloaderDelegate*)this);
    downloader -> retain();
}

void ImageUtils::downloadImageDone(bool success,const char * name,const char *url,ImageDownloader *downloader)
{
    callBack(name, success);
    downloader -> release();
}

void ImageUtils::callBack(const char *ref,bool success)
{
    std::string tmp = ref;
    vector<std::string>::iterator it;
    for (it = _imageUrlVector.begin(); it != _imageUrlVector.end(); it++) {
        if ((*it) == ref ) {
            _imageUrlVector.erase(it);
            break;
        }
    }
    for (int i = 0; i < _delegateVector.size(); i++) {
        ImageUtilsDelegate * delegate = _delegateVector.at(i);
        delegate -> imageDownloadDone(ref,success);
    }
}

void ImageUtils::addImageDelegate(ImageUtilsDelegate * delegate)
{
    bool find =false;
    for (int i = 0; i < _delegateVector.size(); i++) {
        find = (delegate == _delegateVector.at(i));
        if (find) {
            break;
        }
    }
    if (!find) {
        _delegateVector.push_back(delegate);
    }
}

void ImageUtils::removeImageDelegate(ImageUtilsDelegate * delegate)
{
    vector<ImageUtilsDelegate *>::iterator iter;
    for (iter = _delegateVector.begin(); iter != _delegateVector.end(); iter++) {
        if (delegate == (*iter)) {
            _delegateVector.erase(iter);
            break;
        }
    }
}