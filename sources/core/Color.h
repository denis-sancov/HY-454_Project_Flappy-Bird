//
// Created by Denis Sancov on 15/01/2017.
//

#ifndef PROJECT_HY454_COLOR_H
#define PROJECT_HY454_COLOR_H

#include <cstdint>

namespace csd {

    class Color {
    public:
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255):_r(r), _g(g), _b(b), _a(a) { }

        uint8_t getR() const { return _r; };
        uint8_t getG() const { return _g; };
        uint8_t getB() const { return _b; };
        uint8_t getA() const { return _a; };



        static Color Clear()    { return Color(0, 0, 0, 0); }
        static Color Red()      { return Color(255, 0, 0);  };
        static Color Green()    { return Color(0, 255, 0);  };
        static Color Blue()     { return Color(0, 0, 255);  };

        static Color Black()    { return Color(0, 0, 0);  };
        static Color White()    { return Color(255, 255, 255);  };

    private:
        uint8_t _r = 0;
        uint8_t _g = 0;
        uint8_t _b = 0;
        uint8_t _a = 255;
    };
}


#endif //PROJECT_HY454_COLOR_H
