//
// Created by Denis Sancov on 03/01/2017.
//

#include "PauseScreen.h"

using namespace csd;

PauseScreen::PauseScreen():AbstractScreen() {
    auto layer = getLayer();

    int totalHeight = 0;

    _resumeButtonSprite = std::shared_ptr<ImageSprite>(new ImageSprite("Resources/Bitmaps/IconButtonResume.bmp"));
    layer->addSublayer(_resumeButtonSprite);
    totalHeight += _resumeButtonSprite->getSize().height;

    _menuButtonSprite = std::shared_ptr<ImageSprite>(new ImageSprite("Resources/Bitmaps/IconButtonMenu.bmp"));
    layer->addSublayer(_menuButtonSprite);
    totalHeight += _menuButtonSprite->getSize().height;


    _exitButtonSprite = std::shared_ptr<ImageSprite>(new ImageSprite("Resources/Bitmaps/ButtonExit.bmp"));
    layer->addSublayer(_exitButtonSprite);
    totalHeight += _exitButtonSprite->getSize().height;


    Size layerSize = layer->getSize();

    auto sublayers = layer->getSublayers();

    int y = static_cast<int>((layerSize.height - (totalHeight + sublayers.size() * 20)) / 2);

    for (auto sublayer : sublayers) {
        sublayer->setPosition(Point {
                (layerSize.width - sublayer->getSize().width) / 2,
                y
        });
        y += sublayer->getSize().height + 20;
    }
}

void PauseScreen::handleEvent(std::shared_ptr<Event> const eventPtr) {
    if (!dynamic_cast<csd::MouseEvent *>(eventPtr.get())) {
        return;
    }

    auto mouseEvent = std::dynamic_pointer_cast<MouseEvent>(eventPtr);

    if (mouseEvent->getEvent() != Event::PressedDown) {
        return;
    }

    Point mousePosition = mouseEvent->getPosition();

    if (RectContainsPoint(_resumeButtonSprite->getBoundingBox(), mousePosition)) {
        return onResumeButtonClickedCallback();
    }

    if (RectContainsPoint(_menuButtonSprite->getBoundingBox(), mousePosition)) {
        return onMenuButtonClickedCallback();
    }

    if (RectContainsPoint(_exitButtonSprite->getBoundingBox(), mousePosition)) {
        return onExitButtonClickedCallback();
    }
}