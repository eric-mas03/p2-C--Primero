#ifndef _MAP_H_
#define _MAP_H_
#include <iostream>
#include <vector>
#include "Coordinate.h"
#include "Junk.h"

using namespace std;

class Map{
	friend ostream &operator << (ostream &os, const Map &map);
	protected:
		//definimos una matriz usando vector de vectores
		vector<vector<Junk>> junks;
		int rows, columns;
	public:
		Map(int rows, int columns);
		bool isInside(const Coordinate &coord) const;
		void putJunk(const Junk &junk, const Coordinate &cor);
		Junk getJunk(const Coordinate &coord) const;
		Junk collectJunk(const Coordinate &coord);
	
	};


#endif
