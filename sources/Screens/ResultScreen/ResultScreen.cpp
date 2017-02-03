//
// Created by Denis Sancov on 30/12/2016.
//

#include "ResultScreen.h"
#include "../../core/GameSettings.h"
#include "../../core/UserGameData.h"
#include "../../core/Sprites/TextSprite.h"


using namespace csd;

ResultScreen::ResultScreen(unsigned int const score):AbstractScreen(), _score(score) {
    auto layer = getLayer();

    auto gameResultBackground = std::shared_ptr<ImageSprite>(new ImageSprite("Resources/Bitmaps/GameOverBackground.bmp"));
    layer->addSublayer(gameResultBackground);


    _okButtonSprite = std::shared_ptr<ImageSprite>(new ImageSprite("Resources/Bitmaps/okButtonBitmap.bmp"));
    layer->addSublayer(_okButtonSprite);

    int totalHeight = gameResultBackground->getSize().height + _okButtonSprite->getSize().height;


    int y = (layer->getSize().height - (totalHeight + 40)) / 2;
    auto sublayers = layer->getSublayers();

    for (auto sublayer : sublayers) {
        sublayer->setPosition(Point {
                (layer->getSize().width - sublayer->getSize().width) / 2,
                y
        });
        y += sublayer->getSize().height + 20;
    }



    GameSettings& settings = GameSettings::sharedInstance();

    std::string medalIcon;
    if (score >= settings.scoreForPlatinum) {
        medalIcon = "Resources/Bitmaps/IconBirdMedalPlatinum.bmp";
    } else if (score >= settings.scoreForGold) {
        medalIcon = "Resources/Bitmaps/IconBirdMedalGold.bmp";
    } else if (score >= settings.scoreForSilver) {
        medalIcon = "Resources/Bitmaps/IconBirdMedalSilver.bmp";
    } else if (score > settings.scoreForBronze) {
        medalIcon = "Resources/Bitmaps/IconBirdMedalBronze.bmp";
    }

    if (medalIcon.length() > 0) {
        auto medalSprite = std::shared_ptr<ImageSprite>(new ImageSprite(medalIcon));
        medalSprite->setPosition((Point) {
                gameResultBackground->getPosition().x + 40,
                gameResultBackground->getPosition().y + gameResultBackground->getSize().height -
                medalSprite->getSize().height - 35
        });
        layer->addSublayer(medalSprite);
    }



    auto currentScoreSprite = std::shared_ptr<TextSprite>(new TextSprite(std::to_string(score)));
    currentScoreSprite->setFontSize(40);
    currentScoreSprite->setZIndex(2);
    currentScoreSprite->setTextColor(Color::White());
    currentScoreSprite->setPosition(Point {
            gameResultBackground->getPosition().x + gameResultBackground->getSize().width - currentScoreSprite->getSize().width - 30,
            gameResultBackground->getPosition().y + 145
    });
    layer->addSublayer(currentScoreSprite);



    bool newBestScore = false;

    unsigned int bestScore = 0;

    UserGameData& userGameData = UserGameData::sharedInstance();
    bestScore = userGameData.getPreviousBestScore();
    if (score > bestScore) {
        bestScore = score;
        userGameData.setBestScore(score);
        newBestScore = true;
    }

    auto bestScoreSprite = std::shared_ptr<TextSprite>(new TextSprite(std::to_string(bestScore)));
    bestScoreSprite->setFontSize(40);
    bestScoreSprite->setZIndex(2);
    bestScoreSprite->setTextColor(Color::White());
    bestScoreSprite->setPosition((Point){
            gameResultBackground->getPosition().x + gameResultBackground->getSize().width - bestScoreSprite->getSize().width - 30,
            gameResultBackground->getPosition().y + gameResultBackground->getSize().height - 60
    });
    layer->addSublayer(bestScoreSprite);


    if (newBestScore) {
        auto newBestScoreSprite = std::shared_ptr<ImageSprite>(new ImageSprite("Resources/Bitmaps/NewScoreBitmap.bmp"));
        newBestScoreSprite->setPosition((Point) {
                gameResultBackground->getPosition().x + gameResultBackground->getSize().width -
                newBestScoreSprite->getSize().width - 90,
                bestScoreSprite->getPosition().y - newBestScoreSprite->getSize().height - 2
        });
        layer->addSublayer(newBestScoreSprite);
    }
}




void ResultScreen::handleEvent(std::shared_ptr<Event> const eventPtr) {
    if (!dynamic_cast<csd::MouseEvent *>(eventPtr.get())) {
        return;
    }
    auto mouseEvent = std::dynamic_pointer_cast<MouseEvent>(eventPtr);

    if (mouseEvent->getEvent() == Event::PressedDown) {
        return;
    }
    Point mousePosition = mouseEvent->getPosition();
    if (RectContainsPoint(_okButtonSprite->getBoundingBox(), mousePosition)) {
        if (onOKButtonClicked) {
            onOKButtonClicked();
        }
    }
}
