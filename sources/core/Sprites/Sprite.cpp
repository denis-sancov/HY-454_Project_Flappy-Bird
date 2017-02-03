//
// Created by Denis Sancov on 12/01/2017.
//

#include "Sprite.h"

using namespace csd;

void Sprite::removeBitmapReferenceIfNeeded() {
    if (_bitmap != nullptr) {
        _bitmap = nullptr;
    }
}

void Sprite::setBitmap(std::shared_ptr<BitmapInterface> bitmap) {
    removeBitmapReferenceIfNeeded();
    _bitmap = bitmap;
    setSize(_bitmap->getOriginalSize());
}

std::shared_ptr<BitmapInterface> Sprite::getBitmap() const {
    return _bitmap;
}

void Sprite::readyToRender() {
    Layer::readyToRender();

    _bitmap->setAngle(getAngle());
    _bitmap->setPosition(getPosition());
    _bitmap->setScaledSize(getSize());
    _bitmap->renderCopy();
}

Sprite::~Sprite() {
    removeBitmapReferenceIfNeeded();
}
