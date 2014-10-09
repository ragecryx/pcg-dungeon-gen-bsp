#include "PCG-BSPDungeonGen\Corridor.h"


#include <cmath>


/*! Function that returns a list of points
 *  for each neighbouring grid cell of the
 *  function's center parameter
 */
std::vector<Vec2> GetNeighbours(Vec2 &center) {
    std::vector<Vec2> neighbours;
    neighbours.push_back( Vec2(center.x+1, center.y) );
    neighbours.push_back( Vec2(center.x-1, center.y) );
    neighbours.push_back( Vec2(center.x, center.y+1) );
    neighbours.push_back( Vec2(center.x, center.y-1) );
    return neighbours;
}


// Simplistic grid-based pathfinding
Path FindPath(Vec2 begin, Vec2 end) {

    // Create needed variables and init
    // with the starting point.
    Path result;
    result.push_back(begin);
    Vec2 current = begin;
    
    do {
        // Get neighbours
        Path neighbours = GetNeighbours(current);
        // Find nearest
        int nearestIndex;
        int nearestRange=1000;
        for(int i=0; i<4; ++i) {
            if( (std::abs(neighbours[i].x - end.x) + std::abs(neighbours[i].y - end.y)) < nearestRange ) {
                nearestRange = (std::abs(neighbours[i].x - end.x) + std::abs(neighbours[i].y - end.y));
                nearestIndex = i;
            }
        }
        // save up and continue...
        current = neighbours[nearestIndex];
        result.push_back(current);
    } while (current != end); //... until we reach the end point
    
    return result;
}


