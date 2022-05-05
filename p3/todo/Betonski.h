#ifndef _BETONSKI_H_
#define _BETONSKI_H_
#include <vector>
#include <iostream>
#include "Coordinate.h"
#include "Map.h"
#include "Util.h"
#include "Junk.h"

using namespace std;

class Betonski{
	friend ostream &operator << (ostream &os, const Betonski &bet);
	protected:
		string name;
		int anger;
		bool captured;
		vector<Junk> bag;
		Coordinate position;
			
	public:
		Betonski(string name);
		string getName() const;
		int getAnger() const;
		bool isCaptured() const;
		Coordinate getPosition() const;
		void capture();
		void setPosition(const Coordinate &coord);
		int calculateValue() const;
		int calculateValue(JunkType type) const;
		int spoliation();
		int spoliation(JunkType type);
		int extract(const Map &map);
		bool move(const Map &map);
};
	
#endif
