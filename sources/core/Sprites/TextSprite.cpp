//
// Created by Denis Sancov on 13/01/2017.
//

#include "TextSprite.h"

using namespace csd;

TextSprite::TextSprite(std::string const& text) {
    setText(text);
}

void TextSprite::setText(std::string const& text) {
    _text = text;
    refreshBitmap();
}

std::string TextSprite::getText() const {
    return _text;
}

void TextSprite::setFontSize(unsigned short size) {
    _fontSize = size;
    refreshBitmap();
}

unsigned short TextSprite::getFontSize() const {
    return _fontSize;
}

void TextSprite::setFontPath(std::string const& fontPath) {
    _fontPath = fontPath;
    refreshBitmap();
}

std::string TextSprite::getFontPath() const {
    return _fontPath;
}

void TextSprite::setTextColor(Color const color) {
    _textColor = color;
    refreshBitmap();
}

Color TextSprite::getTextColor() const {
    return _textColor;
}

void TextSprite::refreshBitmap() {
    setBitmap(getRenderer()->bitmapWithText(_text, _fontPath, _fontSize, _textColor));
}

