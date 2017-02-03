//
// Created by Denis Sancov on 13/01/2017.
//

#ifndef PROJECT_HY454_SDLTEXTBITMAP_H
#define PROJECT_HY454_SDLTEXTBITMAP_H

#include "SDLBitmap.h"

namespace csd {

    class SDLTextBitmap : public SDLBitmap {
    public:
        SDLTextBitmap(SDL_Renderer *const renderer,
                      const std::string& text,
                      const std::string& fontPath,
                      unsigned short size,
                      SDL_Color color);
    };
}


#endif //PROJECT_HY454_SDLTEXTBITMAP_H
