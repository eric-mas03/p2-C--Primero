#include "Coordinate.h"

Coordinate::Coordinate(int row, int column){
	this->row = row;
	this->column = column;
}

Coordinate::Coordinate(){
	row = -1;
	column = -1;
}

int Coordinate::getRow() const{
	return row;
}
	
int Coordinate::getColumn() const{
	return column;
}
	
void Coordinate::setRow(int row){
	this->row = row;
}

void Coordinate::setColumn(int column){
	this->column = column;
}

bool Coordinate::compare(const Coordinate &coord) const{
	bool check = false;
	if(this->row == coord.getRow() && this->column == coord.getColumn()){
		check = true;
	}
	return check;
}

ostream& operator<<(ostream &os,const Coordinate &coord){
os << "[" << coord.row << "," << coord.column << "]";
return os;
}

