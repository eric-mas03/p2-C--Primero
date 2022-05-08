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
	
	if((coord.getRow() >=0 && coord.getRow()<=this->rows)&&
	   (coord.getColumn() >=0 && coord.getColumn()<=this->columns)){
		return true;
	}

	else{
		return false;
	}
}
	
	
void Map::putJunk(const Junk &junk, const Coordinate &cor){
	if(isInside(cor) == true){
		junks[cor.getRow()][cor.getColumn()] = junk;
	}
	else{
		throw EXCEPTION_OUTSIDE;
	}
	
}
	

Junk Map::getJunk(const Coordinate &coord) const{
	Junk junco;
		if(isInside(coord)){
			junco = junks[coord.getRow()][coord.getColumn()];
			return junco;
		}
		else{
			throw EXCEPTION_OUTSIDE;
		}	
}

Junk Map::collectJunk(const Coordinate &coord){
	if(isInside(coord)){
		Junk contenido;
		/*
		junks[coord.getRow()][coord.getColumn()] = Junk();
		return Junk();
		*/
		contenido = junks[coord.getRow()][coord.getColumn()];
		junks[coord.getRow()][coord.getColumn()] = Junk();
		return contenido;
		
	}
	else{
		throw EXCEPTION_OUTSIDE;
	}
	
}

//Cambia los 0 por -1
ostream &operator << (ostream &os, const Map &map){
	Junk contenido;
	
	os << "    ";
	int i, j = 0;

	for(j = 0; j<int(map.columns);j++){
		if(j < 10){
			os << "0";
		}
		os<<j<<" ";
	}

	for(i = 0; i<int(map.rows);i++){
		
		if(i < 10){
			os << "0";
		}
		os<< i <<" ";

		for(j = 0; j<int(map.columns);j++){
			if(map.junks[i][j].getTypeChar() == 'W' ){
				os << "   ";
			}
			else{
				os << map.junks[i][j].getTypeChar();
			}
		}
	}

	return os;
}

	/*
	for(int i = -1; i<map.rows; i++){
		for(int j = -1; j<map.columns; j++){
				
				if( i == -1 && j == -1){
					os << "   ";
				}

				else if (i == -1){
					if(j<10 && j>=0){
						os << "0"<< j <<" ";
					}
					else{
						os << j << " ";
					}	
				}

				else if (j == -1){
					if(i<10 && i>=0){
						os << "0"<< i <<" ";
					}
					os << i << " ";	
				}

				else if(contenido.getTypeChar() == 'W'){
					
					contenido = map.junks[i][j];
					os << "   ";
				}

				else{
					contenido = map.junks[i][j];
					os << contenido.getTypeChar() << "  ";
				}
				
			}
			os<<"||||("<<i<<") fila completada||||"<<endl;
		}
		os<<"HASTAAQUI"<<endl;
	*/