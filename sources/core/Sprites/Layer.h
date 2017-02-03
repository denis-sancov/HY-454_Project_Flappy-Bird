//
// Created by Denis Sancov on 12/01/2017.
//

#ifndef PROJECT_HY454_LAYER_H
#define PROJECT_HY454_LAYER_H

#include <memory>
#include <vector>
#include "../Geometry.h"
#include "../GameEngineAbstract/GraphicsSystemInterface.h"

namespace csd {
    class Layer {
    public:
        //by default, the size of the layer will match the size of the context where it will be rendered
        Layer();

        Layer(Rect rect);

        virtual ~Layer();

        std::shared_ptr<GraphicsSystemInterface> getRenderer() const;

        void    setPosition(Point const point);
        Point   getPosition() const;

        void    setSize(Size const size);
        Size    getSize() const;

        void    setHidden(bool const hidden);
        bool    isHidden() const;

        void    setZIndex(int const zIndex);
        int     getZIndex() const;

        virtual void    setAngle(double angle);
        double          getAngle() const;

        virtual void    setVelocity(Point velocity);
        Point           getVelocity() const;

        virtual Rect    getBoundingBox() const;
        bool    boundingBoxIntersects(std::shared_ptr<Layer> const layer);

        const std::vector<Rect>& getCollisionBoxes();
        void setCollisionBoxes(std::vector<Rect> const & collisionBoxes);
        void resetCollisionBoxes();


        bool collisionBoxIntersection(std::shared_ptr<Layer> const sprite);



        void    setTag(int const tag);
        int     getTag() const;


        void    addSublayer(std::shared_ptr<Layer> const layer);
        void    removeSublayer(std::shared_ptr<Layer> const layer);

        void    removeSublayer(unsigned long const index);

        std::vector<std::shared_ptr<Layer>> getSublayers() const;

        void renderCopy();
    private:
        std::shared_ptr<GraphicsSystemInterface> _renderer;


        Point   _position        = Point{0, 0};
        Size    _size            = Size {0, 0};
        bool    _hidden          = false;
        int     _zIndex          = 0;
        double  _angle           = 0.f;
        Point   _velocity        = Point{0, 0};

        int     _tag             = 0;

        std::vector<Rect> _collisionBoxes;


        std::vector<std::shared_ptr<Layer>> _sublayers;

    protected:
        virtual void readyToRender() { };
    };
}

#endif //PROJECT_HY454_LAYER_H
