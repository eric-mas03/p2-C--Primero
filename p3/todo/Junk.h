#ifndef _JUNK_H_
#define _JUNK_H_
#include <iostream>
#include "Util.h"

using namespace std;

class Junk{
	friend ostream& operator<<(ostream &o, const Junk &junk);
	protected:
		JunkType type;
		int quantity;
		
	public:
		Junk();
		Junk(JunkType type, int quantity);
		JunkType getType() const;
		int getQuantity() const;
		char getTypeChar() const;
		int getValue() const;
};
#endif
