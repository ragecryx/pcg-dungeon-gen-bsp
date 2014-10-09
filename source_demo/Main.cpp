#include <iostream>

#include <PCG-BSPDungeonGen\Dungeon.h>
#include <PCG-BSPDungeonGen\Node.h>
#include <PCG-BSPDungeonGen\AABB.h>
#include <PCG-BSPDungeonGen\Corridor.h>

using namespace std;

int main() {
	
	Dungeon d("test_seed", 60, 30, 12);
	do {
		d.Generate();
	} while( cin.get() );
	
	cin.get();
	
	return 0;
}





