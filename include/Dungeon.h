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
        Dungeon(std::string seed, int width, int height, int unit_square);
        ~Dungeon();
		enum TILE_TYPE { Empty=0, Floor=1, Corridor=2, Entrance=3, Exit=4, Door=5, Treasure=6, Monster=7, Trap=8 };
    private:
        int mWidth;
        int mHeight;
        int mUnitSquare;
        std::mt19937 mRandGen;
		std::uniform_real_distribution<float> mUniDistr;
        std::seed_seq mSeedSeq;
        std::string mSeedString;
        std::vector< Room > mRooms;
        std::vector< Path > mCorridors;
		std::vector< Vec2 > mTreasures;
		std::vector< Vec2 > mMonsters;
		std::vector< Vec2 > mTraps;
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
		void BakeFloor();
		void PlaceDoors();
		void PlaceTreasureAndMonsters();
		void BakeDetails();
};



#endif
