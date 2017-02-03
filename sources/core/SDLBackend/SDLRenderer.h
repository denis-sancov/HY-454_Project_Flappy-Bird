//
// Created by Denis Sancov on 16/11/2016.
//

#ifndef PROJECT_HY454_SDLRENDERER_H
#define PROJECT_HY454_SDLRENDERER_H

#include "../GameEngineAbstract/GraphicsSystemInterface.h"
#include <SDL.h>

namespace csd {

    class SDLRenderer : public GraphicsSystemInterface {
    public:
        SDLRenderer();
        ~SDLRenderer();

        std::shared_ptr<BitmapInterface> bitmapFromFile(std::string const &fileNamed) override;
        std::shared_ptr<BitmapInterface> bitmapWithText(std::string const &text,
                                                        const std::string& fontPath,
                                                        unsigned short size,
                                                        Color color) override;

        void clear() override;

        void fillRect(Rect const &rect, Color const &backgroundColor) override;
        void renderRect(Rect const &rect, Color const &borderColor) override;
        void presentRenderedDataOnScreen() override;

    private:
        SDL_Window   *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;

        SDL_Rect  convertFromRect(Rect const &rect);
    };
}


#endif //PROJECT_HY454_SDLRENDERER_H
