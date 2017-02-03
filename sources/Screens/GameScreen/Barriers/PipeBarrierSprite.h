//
// Created by Denis on 1/2/2017.
//

#ifndef PROJECT_HY454_PIPEBARRIERSPRITE_H
#define PROJECT_HY454_PIPEBARRIERSPRITE_H

#include "BarrierInterface.h"
#include "../../../core/GameEngineAbstract/BitmapInterface.h"
#include <random>

namespace csd {

    class PipeBarrierSprite : public BarrierInterface {
    public:
        typedef enum _pipeType {
            PipeTypeClassic = 1,
            PipeTypeGroup,
            PipeTypeGroupStairs,
            PipeTypeGroupPyramide
        } PipeType;

        PipeBarrierSprite(PipeType type = PipeTypeClassic);
        ~PipeBarrierSprite();

        PipeType getType() const;

        unsigned int getScoreForPassing() const override;
    private:
        PipeType _pipeType = PipeTypeClassic;

        std::shared_ptr<BitmapInterface> _topPipeBitmap, _bottomPipeBitmap;

        unsigned int _amountOfPipePairsToGenerate = 0;
        unsigned int _points = 0;

        bool reverse = false;
    protected:
        void readyToRender() override;
    };
}


#endif //PROJECT_HY454_PIPEBARRIERSPRITE_H
