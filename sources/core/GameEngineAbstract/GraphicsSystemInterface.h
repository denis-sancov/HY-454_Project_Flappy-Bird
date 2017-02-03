//
// Created by Denis Sancov on 14/01/2017.
//

#ifndef PROJECT_HY454_GRAPHICSSYSTEMINTERFACE_H
#define PROJECT_HY454_GRAPHICSSYSTEMINTERFACE_H

#include <memory>
#include <map>
#include "BitmapInterface.h"
#include "../Geometry.h"
#include "../Color.h"

namespace csd {

    class GraphicsSystemInterface {
    public:
        int getID() const {
            return _id;
        }

        Rect getBounds() const {
            return _bounds;
        }

        virtual std::shared_ptr<BitmapInterface> bitmapFromFile(std::string const &fileNamed) = 0;
        virtual std::shared_ptr<BitmapInterface> bitmapWithText(std::string const &text,
                                                                const std::string& fontPath,
                                                                unsigned short size,
                                                                Color color) = 0;

        virtual void clear() = 0;

        virtual void fillRect(Rect const &rect, Color const &backgroundColor) = 0;
        virtual void renderRect(Rect const &rect, Color const &borderColor) = 0;

        void renderBitmapCopy(std::shared_ptr<BitmapInterface> bitmap) {
            bitmap->renderCopy();
        }

        void releaseUnusedBitmaps() {
            for (auto it = _cachedBitmaps.cbegin(); it != _cachedBitmaps.cend();) {
                it = (it->second.use_count() == 1) ? _cachedBitmaps.erase(it) : ++it;
            }
        }

        virtual void presentRenderedDataOnScreen() = 0;

    protected:
        int _id = -1;
        Rect _bounds;

        std::map<std::string, std::shared_ptr<BitmapInterface>> _cachedBitmaps;

        GraphicsSystemInterface() { };
        GraphicsSystemInterface(GraphicsSystemInterface const &) {}
        void operator=(GraphicsSystemInterface const &) {};
    };
}



#endif //PROJECT_HY454_GRAPHICSSYSTEMINTERFACE_H
