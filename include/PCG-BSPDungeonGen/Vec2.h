#ifndef PCG_VEC2_H
#define PCG_VEC2_H



/*! Struct representing a point or vector in 2d space.
 */
typedef struct _Vec2 {
    /* Data */
    int x;
    int y;

    /* Constructors and Operators */
    _Vec2() {
        x=0;
        y=0;
    }

    _Vec2(int _x, int _y) {
        x=_x;
        y=_y;
    }

    _Vec2(const _Vec2& v) {
        x=v.x;
        y=v.y;
    }

    bool operator==(const _Vec2& rhs) const {
      return (x == rhs.x && y == rhs.y);
    }

    bool operator!=(const _Vec2& rhs) const {
      return (x != rhs.x || y != rhs.y);
    }
    
} Vec2;



#endif
