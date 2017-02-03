//
// Created by Denis Sancov on 13/01/2017.
//

#include "SDLTextBitmap.h"
#include <SDL_ttf.h>

using namespace csd;

SDLTextBitmap::SDLTextBitmap(SDL_Renderer *const renderer,
                             const std::string& text,
                             const std::string& fontPath,
                             unsigned short size,
                             SDL_Color color):SDLBitmap(renderer) {
    TTF_Font *font = TTF_OpenFont(fontPath.c_str(), size);
    if (font == nullptr) {
        throw std::invalid_argument("can't load font at path " + fontPath);
    }
    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (surface == nullptr) {
        throw std::invalid_argument("can't load presentRenderChanges text");
    }
    SDLBitmap::createTextureFromSurface(surface);


    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

