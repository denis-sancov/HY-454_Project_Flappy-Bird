//
// Created by Denis Sancov on 30/12/2016.
//

#include "StartScreen.h"
#include "../../core/Sprites/TextSprite.h"

using namespace csd;


StartScreen::StartScreen():AbstractScreen() {

    auto layer = getLayer();
    Size layerSize = layer->getSize();


    int totalHeight = 0;

    auto logoSprite = std::shared_ptr<ImageSprite>(new ImageSprite("Resources/Bitmaps/FlappyBirdLogo.bmp"));
    layer->addSublayer(logoSprite);
    totalHeight += logoSprite->getSize().height;


    _buttonSprite = std::shared_ptr<ImageSprite>(new ImageSprite("Resources/Bitmaps/IconButtonPlay.bmp"));
    layer->addSublayer(_buttonSprite);
    totalHeight += _buttonSprite->getSize().height;

    _exitButtonSprite = std::shared_ptr<ImageSprite>(new ImageSprite("Resources/Bitmaps/ButtonExit.bmp"));
    layer->addSublayer(_exitButtonSprite);
    totalHeight += _exitButtonSprite->getSize().height;


    std::vector<std::string> copyrightStrings = {
            "Denis Sancov AM-920",
            "University of Crete",
            "Department of Computer Science",
            "CS-454. Development of Intelligent Interfaces and Games",
            "Team Project, Fall Semester 2016"
    };

    for (std::string line : copyrightStrings) {
        auto textSprite = std::shared_ptr<TextSprite>(new TextSprite(line));
        textSprite->setTextColor(Color(43, 43, 43));
        textSprite->setFontSize(15);

        totalHeight += textSprite->getSize().height;

        layer->addSublayer(textSprite);
    }

    int initialY = (layerSize.height - (totalHeight + 120)) / 2;

    auto sublayers = layer->getSublayers();
    for (int i = 0; i < sublayers.size(); i++) {
        auto sublayer = sublayers[i];
        Point point = Point {
                (layerSize.width - sublayer->getSize().width) / 2,
                initialY
        };
        sublayer->setPosition(point);

        initialY += sublayer->getSize().height;

        switch (i) {
            case 0: initialY += 40; break;
            case 1: initialY += 30; break;
            case 2: initialY += 50; break;
            default: break;
        }
    }
}

void StartScreen::handleEvent(std::shared_ptr<Event> const eventPtr) {
    if (!dynamic_cast<csd::MouseEvent *>(eventPtr.get())) {
        return;
    }

    auto mouseEvent = std::dynamic_pointer_cast<MouseEvent>(eventPtr);
    if (mouseEvent->getEvent() != Event::PressedDown) {
        return;
    }

    Point mousePosition = mouseEvent->getPosition();
    if (RectContainsPoint(_buttonSprite->getBoundingBox(), mousePosition)) {
        if (onStartButtonClickedCallback) {
            onStartButtonClickedCallback();
        }
    }

    if (RectContainsPoint(_exitButtonSprite->getBoundingBox(), mousePosition)) {
        if (onExitButtonClickedCallback) {
            onExitButtonClickedCallback();
        }
    }
}

