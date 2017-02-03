//
// Created by Denis Sancov on 12/01/2017.
//

#ifndef PROJECT_HY454_SPRITE_H
#define PROJECT_HY454_SPRITE_H

#include "Layer.h"

namespace csd {

    class Sprite : public Layer {
    public:
        ~Sprite();
    private:
        std::shared_ptr<BitmapInterface> _bitmap;
        void removeBitmapReferenceIfNeeded();

    protected:
        void setBitmap(std::shared_ptr<BitmapInterface> bitmap);
        std::shared_ptr<BitmapInterface> getBitmap() const;

        void readyToRender() override;
    };
}


#endif //PROJECT_HY454_SPRITE_H
