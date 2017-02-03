//
// Created by Denis Sancov on 13/01/2017.
//

#ifndef PROJECT_HY454_BITMAPINTERFACE_H
#define PROJECT_HY454_BITMAPINTERFACE_H

#include "../Geometry.h"

namespace csd {
    class BitmapInterface {
    public:
        virtual ~BitmapInterface() { }

        Size  getOriginalSize() const  { return _size; }

        void  setScaledSize(Size const &size)  { _scaledSize = size; }
        Size  getScaledSize() const           { return _scaledSize; }


        void   setPosition(Point const &origin) { _origin = origin; }
        Point  getPosition() const             { return _origin; }

        void   setAngle(double angle)   { _angle = angle; };
        double getAngle() const          { return _angle; }

        void   setRectToRender(Rect const &rect) { _rectToRender = &rect; }
        const  Rect *getRectToRender() const     { return _rectToRender; }

        virtual void renderCopy() = 0;

    protected:
        Size  _size         = Size{0, 0};
        Size  _scaledSize   = Size{0, 0};

        Point _origin = Point{0, 0};
        const Rect *_rectToRender = nullptr;
        double _angle = 0.f;
    };
}


#endif //PROJECT_HY454_BITMAPINTERFACE_H
