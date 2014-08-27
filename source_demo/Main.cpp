#include <iostream>

#include <Dungeon.h>
#include <Node.h>
#include <AABB.h>
#include <Corridor.h>

using namespace std;

int main() {

	Vec2 asd;
	asd.x = 5;
	asd.y = 6;
	
	AABB region(0,0,140,200);
	cout << "Area: " << region.getVolume() << endl;
	cout << "Center: (x,y) (" << region.getCenter().x << "," << region.getCenter().y << ")" << endl << endl;
	
	Dungeon d(40, 30, 12);
	d.Generate();
	
	cin.get();
	
	return 0;
}





