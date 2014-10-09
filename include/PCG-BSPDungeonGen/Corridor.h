#ifndef PCG_CORRIDOR_H
#define PCG_CORRIDOR_H



#include "Vec2.h"
#include <vector>


typedef std::vector< Vec2 > Path;
// Simplistic grid-based pathfinding
Path FindPath(Vec2 begin, Vec2 end);



#endif
