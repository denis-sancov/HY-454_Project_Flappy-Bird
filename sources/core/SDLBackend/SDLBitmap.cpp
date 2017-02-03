//
// Created by Denis Sancov on 13/01/2017.
//

#include "SDLBitmap.h"

using namespace csd;

SDLBitmap::SDLBitmap(SDL_Renderer *const renderer):_textureRenderer(renderer) { }

SDLBitmap::SDLBitmap(SDL_Renderer *const renderer, const std::string &filePath):_textureRenderer(renderer) {
    SDL_Surface *surface = SDL_LoadBMP(filePath.c_str());

    if (surface == nullptr) {
        throw std::invalid_argument("can't load bitmap at path " + filePath);
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
    this->createTextureFromSurface(surface);

    SDL_FreeSurface(surface);
}

void SDLBitmap::createTextureFromSurface(SDL_Surface *surface) {
    _texture = SDL_CreateTextureFromSurface(_textureRenderer, surface);
    if (_texture == nullptr) {
        throw std::invalid_argument("can't load texture, invalid surface");
    }
    _size = Size {
            surface->w, surface->h
    };
    _scaledSize = _size;
}

void SDLBitmap::renderCopy() {

    SDL_Rect renderQuad = SDL_Rect {
            getPosition().x, getPosition().y, getScaledSize().width, getScaledSize().height
    };

    SDL_Rect *clipRectPtr = nullptr;
    if (getRectToRender() != nullptr) {
        Rect tmp = *getRectToRender();
        clipRectPtr = new SDL_Rect {
                tmp.origin.x, tmp.origin.y, tmp.size.width, tmp.size.height
        };
        renderQuad.w = clipRectPtr->w;
        renderQuad.h = clipRectPtr->h;
    }

    SDL_RenderCopyEx(_textureRenderer, _texture, clipRectPtr, &renderQuad, getAngle(), nullptr, SDL_FLIP_NONE);
    if (clipRectPtr != nullptr) {
        delete clipRectPtr;
    }
}

SDLBitmap::~SDLBitmap() {
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
}