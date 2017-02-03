//
// Created by Denis Sancov on 13/01/2017.
//

#include "ImageSprite.h"

using namespace csd;

ImageSprite::ImageSprite(std::string const& fileNamed) {
    this->setBitmapFromFile(fileNamed);
}

ImageSprite::ImageSprite(std::string const& fileNamed, Size const& frameSize) {
    setBitmapFromFile(fileNamed, frameSize);
}

void ImageSprite::setBitmapFromFile(std::string const& fileNamed) {
    setBitmap(getRenderer()->bitmapFromFile(fileNamed));
}

void ImageSprite::setBitmapFromFile(std::string const& fileNamed, Size const& frameSize) {
    setBitmapFromFile(fileNamed);
    if (_frameSize != nullptr) {
        delete _frameSize;
    }
    _frameSize = new Size {
            frameSize.width, frameSize.height
    };
}


void ImageSprite::setFrameToDisplay(unsigned short const frame) {
    if (frame > framesCount() || _frameSize == nullptr) return;

    if (_rectAreaToRender != nullptr) {
        delete _rectAreaToRender;
        _rectAreaToRender = nullptr;
    }
    _rectAreaToRender = new Rect {
            (frame * _frameSize->width), 0, *_frameSize
    };
}

unsigned short ImageSprite::framesCount() const {
    if (_frameSize == nullptr) return 1;

    return static_cast<unsigned short>((getSize().width / ((_frameSize->width == 0.f) ? 1.f : _frameSize->width)) - 1);
}

Size ImageSprite::getFrameSize() const {
    return *_frameSize;
}

Rect ImageSprite::getBoundingBox() const {
    if (_frameSize == nullptr) return Layer::getBoundingBox();
    return Rect {
            getPosition(),
            *_frameSize
    };
}

void ImageSprite::readyToRender() {
    if (getBitmap() != nullptr && _rectAreaToRender != nullptr) {
        getBitmap()->setRectToRender(*_rectAreaToRender);
    }
    Sprite::readyToRender();
}

ImageSprite::~ImageSprite() {
    if (_frameSize != nullptr) {
        delete _frameSize;
        _frameSize = nullptr;
    }

    if (_rectAreaToRender != nullptr) {
        delete _rectAreaToRender;
        _rectAreaToRender = nullptr;
    }
}