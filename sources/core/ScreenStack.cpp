//
// Created by Denis Sancov on 30/12/2016.
//

#include "ScreenStack.h"

using namespace csd;

ScreenStack::ScreenStack(std::shared_ptr<AbstractScreen> const rootScreen):AbstractScreen() {
    pushScreen(rootScreen);
}

void ScreenStack::pushScreen(std::shared_ptr<AbstractScreen> const screen) {
    if (screen.get() == nullptr) {
        throw std::invalid_argument("Screen can't be null");
    }
    if (_container.size() > 0) {
        _container.back()->setPause(true);
    }
    _container.push_back(screen);
    screen->setPause(false);
}

void ScreenStack::pop() {
    _container.pop_back();
    if (_container.size() > 0) {
        _container.back()->setPause(false);
    }
}

std::shared_ptr<AbstractScreen> ScreenStack::getTopScreen() const{
    return _container.back();
}

std::shared_ptr<AbstractScreen> ScreenStack::getScreenAtIndex(unsigned int index) const {
    return _container.at(index);
}

void ScreenStack::handleEvent(std::shared_ptr<Event> const eventPtr) {
    for (std::shared_ptr<AbstractScreen> screen : _container) {
        if (!screen->isPaused()) {
            screen->handleEvent(eventPtr);
        }
    }
}

void ScreenStack::handleGameLoop() {
    AbstractScreen::handleGameLoop();
    for (std::shared_ptr<AbstractScreen> screen : _container) {
        if (!screen->isPaused() || screen->allowRenderDuringThePause()) {
            screen->handleGameLoop();
        }
    }
}