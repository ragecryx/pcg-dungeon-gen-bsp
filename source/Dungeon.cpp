#include "Dungeon.h"


#include <iostream>
#include <cmath>

#include "Corridor.h"


// Constructors
Dungeon::Dungeon(int width, int height, int unit_square) : mRootNode(nullptr, AABB(0,0,width,height)) {
    Dungeon("DeFaUlT_*_SeEd", width, height, unit_square);
}


Dungeon::Dungeon(std::string seed, int width, int height, int unit_square) : mRootNode(nullptr, AABB(0,0,width,height)) {
    mWidth = width;
    mHeight = height;
    mUnitSquare = unit_square;
    // init grid
    for(int i = 0; i<height; i++) {
        std::vector<unsigned int> line;
        for(int j = 0; j<width; j++) {
            line.push_back(0);
        }
        mGrid.push_back(line);
    }
	
	std::cout << "Grid height: " << mGrid.size();
    
    mSeedString = seed;
    mSeedSeq = std::seed_seq( mSeedString.begin(), mSeedString.end() );
    mRandGen = std::mt19937( mSeedSeq );
}


Dungeon::~Dungeon() { }



// Public Methods
void Dungeon::Generate() {
    SplitSpace(&mRootNode);
    FindRoomsDigCorridors();
    PlaceEntranceAndExit();
    std::cout << "Dungeon Generation complete!" << std::endl;
	
	#ifdef DEBUG
	std::cout << "Spitting the grid [" << mGrid.size() << "]: " << std::endl;
	for(int i = 0; i<mGrid.size(); i++)
		for(int j = 0; j<mGrid[i].size(); j++) {
			std::cout << mGrid[i][j];
		}
		std::cout << std::endl;
	#endif
}



// Private Methods
void Dungeon::SplitSpace(Node<AABB>* node) {
    
    float ratio = (float)node->GetData().getWidth() / node->GetData().getHeight();
    bool splitVertical = true;
    if(ratio < 1.0f)
        splitVertical = false;
        
    
    float split = (float)mRandGen() / 10000000000;
    do {
        split = (float)mRandGen() / 10000000000;
    } while (split < 0.4f || split > 0.6f);
    
    
    AABB subspaceA, subspaceB;
    
    if( splitVertical ) {
        int splitX = node->GetData().X() + (int)(split * node->GetData().getWidth());
        subspaceA = AABB( node->GetData().X(), node->GetData().Y(),
                          (int)(split * node->GetData().getWidth()), node->GetData().getHeight() );
        subspaceB = AABB( splitX, node->GetData().Y(), 
                          (int)((1-split) * node->GetData().getWidth()), node->GetData().getHeight() );
    } else {
        int splitY = node->GetData().Y() + (int)(split * node->GetData().getHeight());
        subspaceA = AABB( node->GetData().X(), node->GetData().Y(), 
                          node->GetData().getWidth(), (int)(split * node->GetData().getHeight()) );
        subspaceB = AABB( node->GetData().X(), splitY,
                          node->GetData().getWidth(), (int)((1-split) * node->GetData().getHeight()) );
    }
    
    #ifdef DEBUG
		std::cout << "Splitting [" << node->GetData().X() << ", " << node->GetData().Y() << ", " << node->GetData().getWidth() << ", " << node->GetData().getHeight() << "] into:" << std::endl;
		std::cout << "Space A: [" << subspaceA.X() << ", " << subspaceA.Y() << ", " << subspaceA.getWidth() << ", " << subspaceA.getHeight() << "]" << std::endl;
		std::cout << "Space B: [" << subspaceB.X() << ", " << subspaceB.Y() << ", " << subspaceB.getWidth() << ", " << subspaceB.getHeight() << "]" << std::endl;
		std::cout << std::endl;
    #endif
    
    node->MakeLeftChild(subspaceA);
    node->MakeRightChild(subspaceB);
    
    // Decide if we need to split more
    if( subspaceA.getWidth() > 7 && subspaceA.getHeight() > 6 )
        SplitSpace(node->GetLeftChild());
    if( subspaceB.getWidth() > 7 && subspaceB.getHeight() > 6 )
        SplitSpace(node->GetRightChild());
    
} // method ends here


void Dungeon::FindRoomsDigCorridors() {
    Node<AABB>::NodeIterator it(&mRootNode);
    
    // Iterate over bsp-tree and add Rooms that
    // adhere to the minimum size required
    while( it.Next() != false ) {
        if( it.IsLeaf() == true && it.GetData().getWidth() > 3 && it.GetData().getHeight() > 3 ) {
            mRooms.push_back( it.GetData() );
            #ifdef DEBUG
				std::cout << "Added [" << it.GetData().X() << ", " << it.GetData().Y() << ", " << it.GetData().getWidth() << ", " << it.GetData().getHeight() << "]" << std::endl;
            #endif
        }
    }
    
    it.Reset();
    
    // Re-iterate over bsp-tree and create
    // corridors using pathfind function (grid-based)
    while( it.Next() != false ) {
        if( !it.IsLeaf() ) {
            Path corridor = FindPath( it.GetNode()->GetLeftChild()->GetData().getCenter(), it.GetNode()->GetRightChild()->GetData().getCenter() );
            mCorridors.push_back(corridor);

            #ifdef DEBUG
                std::cout << "Corridor points from [" << it.GetNode()->GetLeftChild()->GetData().getCenter().x << ", " << it.GetNode()->GetLeftChild()->GetData().getCenter().y << "]" << std::endl;
                std::cout << " to [" << it.GetNode()->GetRightChild()->GetData().getCenter().x << ", " << it.GetNode()->GetRightChild()->GetData().getCenter().y << "]" << std::endl;
                for(Path::iterator itP = corridor.begin(); itP != corridor.end(); itP++) {
                    std::cout << itP->x << ", " << itP->y << std::endl;
                }
                std::cout << std::endl;
            #endif
        }
    }

} // method ends here


void Dungeon::PlaceEntranceAndExit() {

    int i, j; // i is the index of the room with the entrance
              // j is the index of the room with the exit
    i = j = 0;

    // Randomly choose room for each
    if( (float)mRandGen() / 10000000000 > 0.5f ) {
        i = floorf( (float)mRandGen() / 10000000000 * (mRooms.size() / 2.0f) );
        j = floorf( (mRooms.size() / 2.0f) + (float)mRandGen() / 10000000000 * (mRooms.size() / 2.0f) );
    } else {
        j = floorf( (float)mRandGen() / 10000000000 * (mRooms.size() / 2.0f) );
        i = floorf( (mRooms.size() / 2.0f) + (float)mRandGen() / 10000000000 * (mRooms.size() / 2.0f) );
    }
    
    // Set the center of the rooms as entrance and exit
    mEntrance = mRooms[i].getCenter();
    mExit = mRooms[j].getCenter();

    #ifdef DEBUG
        std::cout << "Entrance: [" << mEntrance.x << ", " << mEntrance.y << "]" << std::endl;
        std::cout << "Exit: [" << mExit.x << ", " << mExit.y << "]" << std::endl;
    #endif

}


