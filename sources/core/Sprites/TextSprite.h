//
// Created by Denis Sancov on 13/01/2017.
//

#ifndef PROJECT_HY454_TEXTSPRITE_H
#define PROJECT_HY454_TEXTSPRITE_H


#include "Sprite.h"

namespace csd {

    class TextSprite : public Sprite {
    public:
        TextSprite(std::string const& text);

        void setText(std::string const& text);
        std::string getText() const;

        void setFontSize(unsigned short size);
        unsigned short getFontSize() const;

        void setFontPath(std::string const& fontPath);
        std::string getFontPath() const;

        void setTextColor(Color const color);
        Color getTextColor() const;

    private:
        std::string      _text;
        unsigned short   _fontSize  = 30;
        std::string      _fontPath  = "Resources/Fonts/04B_19__.ttf";
        Color            _textColor = Color::White();

        void refreshBitmap();
    };
}


#endif //PROJECT_HY454_TEXTSPRITE_H
