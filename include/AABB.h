#ifndef PCG_AABB_H
#define PCG_AABB_H



#include "Vec2.h"


/*! Class for Axis-Aligned Bounding Box
 *  Instances of this class are used to represent
 *  a region in 2d space.
 */
class AABB {
    public:
        AABB();
        AABB(int x, int y, int w, int h);
        ~AABB();
    private:
        Vec2 mPosition;
        Vec2 mSize;
    public:
        int getWidth() const;
        int getHeight() const;
        int getVolume() const;
        Vec2 getCenter() const;
        int X() const;
        int Y() const;
        void setPosition(int x, int y);
        void setSize(int w, int h);
};



#endif
