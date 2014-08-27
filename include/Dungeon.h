#ifndef PCG_DUNGEON_H
#define PCG_DUNGEON_H



#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <random>
#include <string>

#include "AABB.h"
#include "Node.h"


typedef AABB Room;
typedef std::vector< Vec2 > Path;
typedef std::vector< std::vector<unsigned int> > Grid;


/*! Class representing a randomly generated dungeon
 */
class Dungeon {
    public:
        Dungeon(int width, int height, int unit_square);
        Dungeon(std::string seed, int width, int height, int unit_square);
        ~Dungeon();
    private:
        int mWidth;
        int mHeight;
        int mUnitSquare;
        std::mt19937 mRandGen;
        std::seed_seq mSeedSeq;
        std::string mSeedString;
        std::vector< Room > mRooms;
        std::vector< Path > mCorridors;
        Vec2 mEntrance;
        Vec2 mExit;
        Grid mGrid;
        Node<AABB> mRootNode;
    public:
        void Generate(void);
    private:
        void SplitSpace(Node<AABB>* node);
        void FindRoomsDigCorridors();
        void PlaceEntranceAndExit();
};



#endif
