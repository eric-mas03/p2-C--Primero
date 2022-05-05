#include "Map.h"

Map::Map(int rows, int columns){
	if(rows < 5 || columns < 5){
		throw EXCEPTION_SIZE;		
	}
	this->rows = rows;
	this->columns = columns;
		
		Junk junco;
		vector<Junk> fila;
		
		for(int i = 1; i<=columns; i++){
			fila.push_back(junco);
		}
		for(int i = 1; i<=rows; i++){
			junks.push_back(fila);
		}
		
	}
	
bool Map::isInside(const Coordinate &coord) const{
	if((coord.getRow() >=0 && coord.getRow()<=rows)&&
	  (coord.getColumn() >=0 && coord.getColumn()<=columns)){
		return true;
	}
	else{
		return false;
	}
}
	
	
void Map::putJunk(const Junk &junk, const Coordinate &cor){
	junks[cor.getRow()][cor.getColumn()] = junk;
	
	}
	
	
	
	
Junk Map :: getJunk(const Coordinate &coord) const{
	Junk junco;
	junco = junks[coord.getRow()][coord.getColumn()];
	return junco;
	
	}
Junk Map::collectJunk(const Coordinate &coord){

	junks[coord.getRow()][coord.getColumn()] = Junk();
	return Junk();
	}
	
ostream &operator << (ostream &os, const Map &map){
		Junk contenido;
		
		for(int i = -1; i<map.rows; i++){
			for(int j = -1; j<map.columns; i++){
					contenido = map.junks[i][j];
					if( i == -1 && j == -1){
						os << "   ";
					}
					else if (i == -1){
						if(i<10){
							os << " 0";
							}
						os << i+1 ;	
					}
					else if (j == -1){
						if(j<10){
							os << "0";
							}
						os << j+1;	
					}
					else{
							os << contenido.getTypeChar() << "  ";
					}
				}
			}
		return os;
}
