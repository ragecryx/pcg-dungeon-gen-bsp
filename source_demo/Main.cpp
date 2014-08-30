#include <iostream>

#include <Dungeon.h>
#include <Node.h>
#include <AABB.h>
#include <Corridor.h>

using namespace std;

int main() {
	
	Dungeon d("test_seed", 60, 30, 12);
	do {
		d.Generate();
	} while( cin.get() );
	
	cin.get();
	
	return 0;
}





