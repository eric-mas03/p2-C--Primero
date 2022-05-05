#include "Junk.h"


Junk::Junk(){
	type = WASTELAND;
	quantity = 0;
}

Junk::Junk(JunkType type, int quantity){
	this-> type = type;
	if(quantity < 0){
		throw EXCEPTION_QUANTITY;
	}
	else{
		this->quantity = quantity;
	}
}

JunkType Junk::getType() const{
	return type;
}
	
int Junk:: getQuantity() const{
	return quantity;
}
	
char Junk::getTypeChar() const{
	char capital;
	switch (type){
		case WASTELAND:
			capital = 'W';
			break;
		case GOLD:
			capital = 'G';
			break;
		case METAL:
			capital = 'M';
			break;
		case FOOD:
			capital = 'F';
			break;
		case STONE:
			capital = 'S';
			break;
	}	
	return capital;
	
	char capitals[] = "WGMFS";
	return capitals[type];
}


int Junk::getValue() const{
	int valor;
	switch (type){
		case WASTELAND:
			valor  = 0;
			break;
		case GOLD:
			valor = 500;
			break;
		case METAL:
			valor = 100;
			break;
		case FOOD:
			valor = 50;
			break;
		case STONE:
			valor = 20;
			break;
	}
	valor = valor*quantity;	
	return valor;
	int values[] = {0,500,100,50,20};
	return values[type]*quantity;
}

ostream &operator<<(ostream &os, const Junk &junk){
	os << "[";
	switch (junk.type){
		case WASTELAND:
			os<< "WASTELAND";
			break;
		case GOLD:
			os<< "GOLD";
			break;
		case METAL:
			os<<"METAL";
			break;
		case FOOD:
			os<< "FOOD";
			break;
		case STONE:
			os<< "STONE";
			break;
	}
	
	os << junk.quantity << "]";
	return os;
	string nombre[] = {"WASTELAND","GOLD","METAL","FOOD","STONE"};
	os << "[" << nombre[junk.type]<<":"<<junk.quantity<<"]";
	return os;

}


//int Junk::getRow() const {return row;}
//int Junk::getColumn() const {return column;}
//void Junk::SetRow(int row){}
//void Junk::SetColumn(int column){}
//bool Junk::compare(const Junk &coord) const{return true;}


