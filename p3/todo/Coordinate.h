#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <iostream>

using namespace std;


class Coordinate{
	friend ostream& operator<<(ostream &o, const Coordinate &position);
	protected:
		int row, column;

	public:
		Coordinate();
		Coordinate(int row, int column);
		int getRow() const;
		int getColumn() const;
		void setRow(int row);
		void setColumn(int column);
		bool compare(const Coordinate &coord) const;
};
#endif
