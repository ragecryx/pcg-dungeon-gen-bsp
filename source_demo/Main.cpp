#include <iostream>

#include <PCG-BSPDungeonGen\Dungeon.h>
#include <PCG-BSPDungeonGen\Node.h>
#include <PCG-BSPDungeonGen\AABB.h>
#include <PCG-BSPDungeonGen\Corridor.h>

using namespace std;

int main() {
	
	Dungeon d("test_seed", 60, 30, 12);
	//do {
		d.Generate();
	//} while( cin.get() );

	Grid g = d.GetGrid();
	if(g.size()==30 && g[0].size()==60)
		cout << "d.GetGrid() is working!" << endl;
	else
		cout << "Something wrong with d.GetGrid()!!!" << endl;

	cout << endl;

	// re-print grid
	for(Grid::iterator it=g.begin(); it!=g.end(); ++it) {
		for(GridLine::iterator itL = it->begin(); itL!=it->end(); ++itL)
			cout << *itL;
		cout << endl;
	}
	
	cin.get();
	
	return 0;
}





