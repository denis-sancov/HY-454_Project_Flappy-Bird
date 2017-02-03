//
// Created by Denis on 1/2/2017.
//

#include <chrono>
#include "PipeBarrierSprite.h"
#include "../../../core/GameSettings.h"

using namespace csd;

PipeBarrierSprite::PipeBarrierSprite(PipeType type):BarrierInterface() {
    auto renderer = getRenderer();

    _topPipeBitmap = renderer->bitmapFromFile("Resources/Bitmaps/PipeTop.bmp");
    _bottomPipeBitmap = renderer->bitmapFromFile("Resources/Bitmaps/PipeBottom.bmp");

    _pipeType = type;

    GameSettings& settings = GameSettings::sharedInstance();

    int heightBetweenPipes = settings.heightBetweenPipes;
    int minPipeHeight = settings.minPipeHeight;


    auto t = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generatorEngine;
    generatorEngine.seed(static_cast<unsigned int>(t));

    std::uniform_int_distribution<int> dist6 = std::uniform_int_distribution<int>(
            minPipeHeight, static_cast<unsigned int>(getSize().height/2)
    );


    int topPipeHeight = dist6(generatorEngine);

    std::function<int(int, int)> heightCalculation;

    switch (type) {
        case PipeTypeGroup: {
            _amountOfPipePairsToGenerate = settings.numberOfPipesPairsPerGroup;
            heightCalculation = [](int index, int height) {
                return height;
            };
            _points = 5;
            break;
        }
        case PipeTypeGroupStairs:
        case PipeTypeGroupPyramide: {

            std::bernoulli_distribution bernoulliDistribution(0.5);
            bool inverse = bernoulliDistribution(generatorEngine);

            topPipeHeight = (inverse) ? (topPipeHeight + (20 * _amountOfPipePairsToGenerate)) : topPipeHeight;


            if (_pipeType == PipeTypeGroupStairs) {

                _amountOfPipePairsToGenerate = settings.numberOfPipesPairsPerStairsGroup;
                heightCalculation = [inverse](int index, int height) {
                    return (inverse) ? height - 20 : height + 20;
                };
                _points = 10;
            } else {

                _amountOfPipePairsToGenerate = settings.numberOfPipesPairsPerPyramideGroup;
                heightCalculation = [inverse, this](int index, int height) {
                    if ((index+1) > _amountOfPipePairsToGenerate / 2) {
                        return (inverse) ? height + 20 : height - 20;
                    } else {
                        return (inverse) ? height - 20 : height + 20;
                    }
                };
                _points = 15;
            }

            break;
        }
        default: {
            _amountOfPipePairsToGenerate = 1;
            heightCalculation = [](int index, int height) {
                return height;
            };
            _points = 1;
            break;
        }
    }

    int xPosition = getPosition().x;
    int pipeWidth = _topPipeBitmap->getOriginalSize().width;

    Rect rect;

    std::vector<Rect> collisionBoxes;

    int offsetBetweenPipes = 5;

    for (int i = 0; i < _amountOfPipePairsToGenerate; ++i) {
        rect.origin = {
                xPosition + i * (pipeWidth + offsetBetweenPipes), 0
        };
        rect.size = {
                pipeWidth, topPipeHeight
        };
        collisionBoxes.push_back(rect);

        rect.size = {
                pipeWidth, getSize().height - topPipeHeight - heightBetweenPipes
        };
        rect.origin = {
                rect.origin.x,
                getSize().height - rect.size.height
        };
        collisionBoxes.push_back(rect);
        topPipeHeight = heightCalculation(i, topPipeHeight);
    }
    this->setSize(Size{
            (pipeWidth + offsetBetweenPipes) * static_cast<int>(_amountOfPipePairsToGenerate) - offsetBetweenPipes,
            this->getSize().height
    });

    this->setCollisionBoxes(collisionBoxes);
    this->setPassed(false);
}




PipeBarrierSprite::PipeType PipeBarrierSprite::getType() const {
    return _pipeType;
}

void PipeBarrierSprite::readyToRender() {
    Layer::readyToRender();


    std::vector<Rect> collisionBoxes = getCollisionBoxes();

    Rect rectToRender;
    for (int i = 0; i < collisionBoxes.size(); i+=2) {

        /*
         *      Top pipe
         */

        _topPipeBitmap->setPosition(collisionBoxes[i].origin);

        rectToRender = RectMake(
                Point {0, _topPipeBitmap->getOriginalSize().height - collisionBoxes[i].size.height},
                collisionBoxes[i].size
        );
        _topPipeBitmap->setRectToRender(rectToRender);
        _topPipeBitmap->renderCopy();


        /*
         *      Bottom pipe
         */

        _bottomPipeBitmap->setPosition(collisionBoxes[i+1].origin);

        rectToRender = RectMake(
                PointZero(),
                collisionBoxes[i + 1].size
        );
        _bottomPipeBitmap->setRectToRender(rectToRender);
        _bottomPipeBitmap->renderCopy();
    }
}

unsigned int PipeBarrierSprite::getScoreForPassing() const {
    return _points;
}

PipeBarrierSprite::~PipeBarrierSprite() {
    if (_topPipeBitmap != nullptr) {
        _topPipeBitmap = nullptr;
    }
    if (_bottomPipeBitmap != nullptr) {
        _bottomPipeBitmap = nullptr;
    }
}
