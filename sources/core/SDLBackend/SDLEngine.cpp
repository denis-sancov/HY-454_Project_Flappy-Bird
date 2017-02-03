//
// Created by Denis Sancov on 14/11/2016.
//

#include "SDLEngine.h"
#include "SDLSoundSystem.h"
#include "SDLRenderer.h"
#include <SDL_ttf.h>

using namespace csd;

void SDLEngine::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw std::invalid_argument("Can't init SDLBackend system");
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear")) {
        std::cout << "Warning: Linear texture filtering not enabled!";
    }
    if(TTF_Init() == -1) {
        throw std::invalid_argument("SDL_ttf could not be initialized!");
    }

    _graphicsSystem  =  std::shared_ptr<GraphicsSystemInterface>(new SDLRenderer());
    _soundSystem     =  std::shared_ptr<SoundSystemInterface>(new SDLSoundSystem());
}

void SDLEngine::setCursorHidden(bool hidden) {
    SDL_ShowCursor((hidden) ? SDL_DISABLE : SDL_ENABLE);
}

void SDLEngine::pollEvent(std::function<void(std::shared_ptr<Event> const eventPtr)> eventLambda) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        Event *event = nullptr;
        switch (e.type) {
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP: {
                int x, y;
                SDL_GetMouseState( &x, &y );
                Point mousePosition = {x, y};
                event = new MouseEvent(
                        (e.type == SDL_MOUSEBUTTONUP) ? MouseEvent::PressedUp : MouseEvent::PressedDown,
                        mousePosition
                );
                break;
            }
            case SDL_KEYDOWN:
            case SDL_KEYUP: {
                event = new KeyboardEvent(
                        (e.type == SDL_KEYUP) ? KeyboardEvent::PressedUp : KeyboardEvent::PressedDown,
                        static_cast<unsigned int>(e.key.keysym.scancode)
                );
                break;
            }

            case SDL_QUIT: {
                event = new TerminateGameEvent();
                break;
            }
            default: {
                break;
            }
        }

        if (event != nullptr) {
            eventLambda(std::shared_ptr<Event>(event));
        }
    }
}

void SDLEngine::delay(uint32_t ms) {
    SDL_Delay(ms);
}

void SDLEngine::terminate() {
    TTF_Quit();
    SDL_Quit();
}