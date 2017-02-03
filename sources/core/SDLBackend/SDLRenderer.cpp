//
// Created by Denis Sancov on 16/11/2016.
//

#include <stdexcept>
#include "SDLRenderer.h"
#include "SDLBitmap.h"
#include "SDLTextBitmap.h"

using namespace csd;

SDLRenderer::SDLRenderer() {
    _window = SDL_CreateWindow(NULL,  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (_window == nullptr) {
        throw std::invalid_argument("can't create window: " + std::string(SDL_GetError()));
    }
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == NULL) {
        throw std::invalid_argument("can't create renderer: " + std::string(SDL_GetError()));
    }

    _id = SDL_GetWindowID(_window);

    int width, height;
    SDL_GL_GetDrawableSize(_window, &width, &height);
    if (width > 1920) {
        width = 1920;
    }
    if (height > 1080) {
        height = 1080;
    }

    _bounds = csd::Rect{0, 0, width, height};

    SDL_RenderSetLogicalSize(_renderer, width, height);
}

std::shared_ptr<BitmapInterface> SDLRenderer::bitmapFromFile(std::string const &fileNamed) {
    std::shared_ptr<BitmapInterface> bitmap;

    if (_cachedBitmaps.find(fileNamed) == _cachedBitmaps.end() ) {
        bitmap = std::shared_ptr<BitmapInterface>(new SDLBitmap(_renderer, fileNamed));
        _cachedBitmaps.emplace(fileNamed, bitmap);
    } else {
        bitmap = _cachedBitmaps.at(fileNamed);
    }

    return bitmap;
}

std::shared_ptr<BitmapInterface> SDLRenderer::bitmapWithText(std::string const &text,
                                                             const std::string& fontPath,
                                                             unsigned short size,
                                                             Color color) {
    SDL_Color sdlColor = SDL_Color {
            color.getR(), color.getG(), color.getB(), color.getA()
    };
    return std::shared_ptr<BitmapInterface>(new SDLTextBitmap(_renderer, text, fontPath, size, sdlColor));
}

void SDLRenderer::clear() {
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(_renderer);
}

void SDLRenderer::fillRect(Rect const &rect, Color const &backgroundColor) {
    SDL_Rect rectToDraw = SDL_Rect{
            rect.origin.x, rect.origin.y, rect.size.width, rect.size.height
    };

    SDL_SetRenderDrawColor(_renderer, backgroundColor.getR(), backgroundColor.getG(), backgroundColor.getB(), backgroundColor.getA());
    SDL_RenderFillRect(_renderer, &rectToDraw);
}

void SDLRenderer::renderRect(Rect const &rect, Color const &borderColor) {
    SDL_Rect rectToDraw = SDL_Rect{
            rect.origin.x, rect.origin.y, rect.size.width, rect.size.height
    };

    SDL_SetRenderDrawColor(_renderer, borderColor.getR(), borderColor.getG(), borderColor.getB(), borderColor.getA());
    SDL_RenderDrawRect(_renderer, &rectToDraw);
}

void SDLRenderer::presentRenderedDataOnScreen() {
    SDL_RenderPresent(_renderer);
}

SDLRenderer::~SDLRenderer() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = nullptr;
    _window = nullptr;
}
