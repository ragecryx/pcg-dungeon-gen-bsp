#include "PCG-BSPDungeonGen\AABB.h"


// Constructors
AABB::AABB() {
    mPosition.x = 0;
    mPosition.y = 0;
    mSize.x = 0;
    mSize.y = 0;
}

AABB::AABB(int x, int y, int w, int h) {
    mPosition.x = x;
    mPosition.y = y;
    mSize.x = w;
    mSize.y = h;
}

AABB::~AABB() { }



// Methods
int AABB::X() const {
    return mPosition.x;
}


int AABB::Y() const {
    return mPosition.y;
}


Vec2 AABB::getCenter() const {
    return Vec2(mPosition.x + mSize.x/2, mPosition.y + mSize.y/2);
}


int AABB::getHeight() const {
    return mSize.y;
}


int AABB::getVolume() const {
    return mSize.x * mSize.y;
}


int AABB::getWidth() const {
    return mSize.x;
}


void AABB::setPosition(int x, int y) {
    mPosition.x = x;
    mPosition.y = y;
}


void AABB::setSize(int w, int h) {
    mSize.x = w;
    mSize.y = h;
}


bool AABB::isInside(Vec2 &p) const {
	return ( p.x >= mPosition.x && p.x <= (mPosition.x+mSize.x) &&
			 p.y >= mPosition.y && p.y <= (mPosition.y+mSize.y) );
}


