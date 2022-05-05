#ifndef _JANKALI_H_
#define _JANKALI_H_
#include <vector>
#include <iostream>
#include "Betonski.h"

using namespace std;

class Jankali{
	friend ostream &operator << (ostream &os, const Jankali &jank);
	protected:
		string name;
		int power;
		Coordinate traps;
		vector<Betonski> subdued; 

	public:
		Jankali(string name);
		string getName() const;
		int getPower() const;
		void hunt(vector<Betonski *> betonskis);
		bool setTrap(const Coordinate &coord);
		void spoil();
		void spoil(JunkType type);
		void spoil(int pos);

};

#endif
