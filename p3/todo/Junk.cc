#include "Junk.h"


Junk::Junk(){
	type = WASTELAND;
	quantity = 0;
}

Junk::Junk(JunkType type, int quantity){
	if(quantity < 0){
		throw EXCEPTION_QUANTITY;
	}
	else{
		this-> type = type;
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
		default:
			break;
	}	
	return capital;
	char capitals[] = "WGMFS";
	return capitals[type];
}


int Junk::getValue() const{
	int valor = 0;
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
}

ostream &operator<<(ostream &os, const Junk &junk){

	string nombre[] = {"WASTELAND","GOLD","METAL","FOOD","STONE"};
	os << "[" << nombre[junk.getType()]<< ':' <<junk.getQuantity()<<"]";
	return os;

}


//int Junk::getRow() const {return row;}
//int Junk::getColumn() const {return column;}
//void Junk::SetRow(int row){}
//void Junk::SetColumn(int column){}
//bool Junk::compare(const Junk &coord) const{return true;}


