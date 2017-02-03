//
// Created by Denis Sancov on 13/01/2017.
//

#ifndef PROJECT_HY454_IMAGESPRITE_H
#define PROJECT_HY454_IMAGESPRITE_H

#include "Sprite.h"

namespace csd {

    class ImageSprite : public Sprite {
    public:
        ImageSprite(std::string const& fileNamed);
        ImageSprite(std::string const& fileNamed, Size const& frameSize);
        ~ImageSprite();

        void setBitmapFromFile(std::string const& fileNamed);
        void setBitmapFromFile(std::string const& fileNamed, Size const& frameSize);

        void setFrameToDisplay(unsigned short const frame);

        unsigned short framesCount() const;
        Size getFrameSize() const;

        Rect    getBoundingBox() const override;

    private:
        Size *_frameSize = nullptr;
        Rect *_rectAreaToRender = nullptr;
    protected:
        void readyToRender() override;
    };
}


#endif //PROJECT_HY454_IMAGESPRITE_H
