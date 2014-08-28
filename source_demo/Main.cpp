#include <iostream>

#include <Dungeon.h>
#include <Node.h>
#include <AABB.h>
#include <Corridor.h>

using namespace std;

int main() {
	
	Dungeon d(40, 30, 12);
	d.Generate();
	
	cin.get();
	
	return 0;
}





