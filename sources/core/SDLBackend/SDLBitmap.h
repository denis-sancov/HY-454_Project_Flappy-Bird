//
// Created by Denis Sancov on 13/01/2017.
//

#ifndef PROJECT_HY454_SDLBITMAP_H
#define PROJECT_HY454_SDLBITMAP_H


#include <SDL_render.h>
#include <string>
#include "../GameEngineAbstract/BitmapInterface.h"

namespace csd {

    class SDLBitmap : public BitmapInterface {
    public:
        SDLBitmap(SDL_Renderer *const renderer);
        SDLBitmap(SDL_Renderer *const renderer, const std::string &filePath);
        ~SDLBitmap();

        void renderCopy() override;

    private:
        SDL_Texture *_texture;
        SDL_Renderer *const _textureRenderer;
    protected:
        void createTextureFromSurface(SDL_Surface *surface);
    };
}


#endif //PROJECT_HY454_SDLBITMAP_H
