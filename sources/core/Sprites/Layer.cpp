//
// Created by Denis Sancov on 12/01/2017.
//

#include "Layer.h"
#include "../GameSettings.h"
#include "../../GameDelegate.h"
#include <algorithm>

using namespace csd;

Layer::Layer() {
    _renderer = GameDelegate::sharedInstance().getGameEngine()->renderingSystem();
    _size = _renderer->getBounds().size;
}

Layer::Layer(Rect rect) {
    _position = rect.origin;
    _size = rect.size;
}

std::shared_ptr<GraphicsSystemInterface> Layer::getRenderer() const {
    return _renderer;
}

void Layer::setPosition(Point const point) {
    Point _previousPoint = _position;

    for (unsigned int i = 0; i < _collisionBoxes.size(); i++) {
        Rect box = _collisionBoxes[i];
        box.origin = Point {
                box.origin.x + point.x - _previousPoint.x,
                box.origin.y + point.y - _previousPoint.y
        };
        _collisionBoxes[i] = box;
    }
    _position = point;
}

Point Layer::getPosition() const {
    return _position;
}

void Layer::setSize(Size const size) {
    _size = size;
}

Size Layer::getSize() const {
    return _size;
}

void Layer::setHidden(bool const hidden) {
    _hidden = hidden;
}

bool Layer::isHidden() const {
    return _hidden;
}

void Layer::setZIndex(int const zIndex) {
    _zIndex = zIndex;
}

int Layer::getZIndex() const {
    return _zIndex;
}

void Layer::setAngle(double const angle) {
    _angle = angle;
}

double Layer::getAngle() const {
    return _angle;
}

void Layer::setVelocity(Point velocity) {
    _velocity = velocity;
    this->setPosition(Point{
            _position.x + _velocity.x,
            _position.y + _velocity.y
    });
}

Point Layer::getVelocity() const {
    return _velocity;
}

Rect Layer::getBoundingBox() const {
    return RectMake((Point) {_position}, (Size) {_size});
}

bool Layer::boundingBoxIntersects(std::shared_ptr<Layer> const layer) {
    return (!_hidden) ? RectIntersects(this->getBoundingBox(), layer->getBoundingBox()) : false;
}

const std::vector<Rect>& Layer::getCollisionBoxes() {
    return _collisionBoxes;
}

void Layer::setCollisionBoxes(std::vector<Rect> const &collisionBoxes) {
    _collisionBoxes.clear();
    _collisionBoxes.insert(_collisionBoxes.end(),collisionBoxes.begin(), collisionBoxes.end());
}

void Layer::resetCollisionBoxes() {
    _collisionBoxes.clear();
}

bool Layer::collisionBoxIntersection(std::shared_ptr<Layer> const layer) {
    if (_hidden) return false;

    auto targetCollisionBoxes = layer->getCollisionBoxes();
    bool collisionDetected = false;

    for (Rect collisionBox : _collisionBoxes) {
        for (Rect targetCollisionBox: targetCollisionBoxes) {
            if (RectIntersects(collisionBox, targetCollisionBox)) {
                collisionDetected = true;
                break;
            }
        }
        if (collisionDetected) {
            break;
        }
    }
    return collisionDetected;
}



void Layer::setTag(int const tag) {
    _tag = tag;
}

int Layer::getTag() const {
    return _tag;
}


void Layer::addSublayer(std::shared_ptr<Layer> const layer) {
    _sublayers.push_back(layer);
}

void Layer::removeSublayer(std::shared_ptr<Layer> const layer) {
    _sublayers.erase(std::remove(_sublayers.begin(), _sublayers.end(), layer), _sublayers.end());
}

void Layer::removeSublayer(unsigned long const index) {
    _sublayers.erase(_sublayers.begin() + index);
}

std::vector<std::shared_ptr<Layer>> Layer::getSublayers() const{
    return _sublayers;
}

void Layer::renderCopy() {
    if (_hidden) return;

    this->readyToRender();

    GameSettings &settings = GameSettings::sharedInstance();
    if (settings.drawBoundingBoxes) {
        _renderer->renderRect(this->getBoundingBox(), Color::Green());
    }

    if (settings.drawCollisionBoxes) {
        for (Rect rect : _collisionBoxes) {
            _renderer->renderRect(rect, Color::Red());
        }
    }

    if (_sublayers.size() > 0) {
        sort(_sublayers.begin(), _sublayers.end(), [](const std::shared_ptr<Layer> lhs, const std::shared_ptr<Layer> rhs) {
                 return lhs->getZIndex() < rhs->getZIndex();
             });
        for (std::shared_ptr<Layer> layer :  _sublayers) {
            layer->renderCopy();
        }
    }
}

Layer::~Layer() {
    _sublayers.clear();
}