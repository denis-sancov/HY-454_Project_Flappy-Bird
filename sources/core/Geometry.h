//
// Created by Denis Sancov on 14/11/2016.
//

#ifndef PROJECT_HY454_GEOMETRY_H
#define PROJECT_HY454_GEOMETRY_H

#include <iostream>

namespace csd {
    typedef struct _point {
        int x;
        int y;
    } Point;

    static inline Point PointZero() {
        return Point{0, 0};
    }

    static inline Point PointMake(int x, int y) {
        return Point{x, y};
    }


    typedef struct _size {
        int width;
        int height;
    } Size;

    static inline Size SizeMake(int width, int height) {
        return Size{width, height};
    }


    typedef struct _rect {
        Point origin;
        Size size;

        int left() const { return origin.x; }
        int right() const { return origin.x + size.width; }
        int top() const { return origin.y; }
        int bottom() const { return origin.y + size.height; }
    } Rect;

    static inline Rect RectMake(int x, int y, int width, int height) {
        Rect rect;
        rect.origin = (Point){x, y};
        rect.size = (Size){width, height};
        return rect;
    }
    static inline Rect RectMake(Point const point, Size const size) {
        return RectMake(point.x, point.y, size.width, size.height);
    }

    static inline bool RectIntersects(Rect const &a, Rect const &b) {
        return !(a.left() > b.right() || a.right() < b.left() ||
                 a.top() > b.bottom() || a.bottom() < b.top());
    }

    static inline bool RectContainsPoint(Rect rect, Point point) {
         return (point.x >= rect.left() && point.x <= rect.right()) &&
                (point.y >= rect.top() && point.y <= rect.bottom());
    }

    static inline void RectDebug(Rect &rect) {
        std::cout << "x =" << rect.origin.x << " y =" << rect.origin.y << std::endl;
        std::cout << "w =" << rect.size.width << " h =" << rect.size.height << std::endl;
    }
}

#endif //PROJECT_HY454_GEOMETRY_H
