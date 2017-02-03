//
// Created by Denis Sancov on 14/11/2016.
//

#include "AbstractScreen.h"
#include "AnimatorManager.h"

using namespace csd;

AbstractScreen::AbstractScreen() { }

const std::shared_ptr<Layer> AbstractScreen::getLayer() {
    if (_layer.get() == nullptr) {
        _layer = std::shared_ptr<Layer>(new Layer());
    }
    return _layer;
}

void AbstractScreen::setPause(bool pause) {
    _paused = pause;
}

bool AbstractScreen::isPaused() const {
    return _paused;
}

void AbstractScreen::handleGameLoop() {
    if (_layer.get() != nullptr) {
        _layer->renderCopy();
    }
}

bool AbstractScreen::allowRenderDuringThePause() {
    return false;
}