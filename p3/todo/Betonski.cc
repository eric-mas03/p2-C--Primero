#include "Betonski.h"


Betonski::Betonski(string name){
	if(name.empty()){
		throw EXCEPTION_NAME;
	}
	
	this->name = name;
	captured = false;
	anger = 0;
	this->position = Coordinate();
	
}
	
string Betonski::getName() const{
	return name;
}
	
int Betonski::getAnger() const{
	return anger;
}
	
bool Betonski::isCaptured() const{
	return captured;
}
	
Coordinate Betonski::getPosition() const{
	return position;
}
	
void Betonski::capture(){
	captured = true;
}
	
void Betonski::setPosition(const Coordinate &coord){
	position = coord;
}
	
int Betonski::calculateValue() const{
	int total = 0;
	for(int  i = 0; i < int(bag.size()) ; i++){
		total += bag[i].getValue();
	} 
	return total;
}
	
int Betonski::calculateValue(JunkType type) const{
	int total = 0;
	for(int i = 0; i < int(bag.size()) ; i++){
		if(bag[i].getType() == type){
			total += bag[i].getValue();
		}
	} 
	return total;	
}

	
int Betonski::spoliation(){

		if(!captured){
			throw BETONSKI_NOT_CAPTURED;
		}
		if(anger+calculateValue()>5000){
			this->captured = false;
			this->anger = 0;
			throw EXCEPTION_REBELION;
		}
		int masanger = calculateValue();
		this->anger += masanger;
		bag.clear();
		return masanger;
}

	
int Betonski::spoliation(JunkType type) {
		int masanger = anger;
		if(!captured){
			throw BETONSKI_NOT_CAPTURED;
		}
	
		if(anger+calculateValue()>5000){
			this->captured = false;
			this->anger = 0;
			throw EXCEPTION_REBELION;
		}
		
		for(int i = 0; i < int(bag.size()) ; i++){
			if(bag[i].getType() == type){
				int masanger = calculateValue(type);
				this->anger += masanger;
				bag.erase(bag.begin()+i);
			}
		}
	return masanger;
}

	
int Betonski::extract(const Map &map){
	char pick;
	Junk temporal;
	int atemporal = 0;
		
		temporal = map.getJunk(this->position); 
		pick = temporal.getTypeChar();
			if(pick != 'W'){
				bag.push_back(temporal);
				atemporal = temporal.getValue();
			}
	
	return atemporal;
}
	
bool Betonski::move(const Map &map){
	if(position.getColumn() < 0 && position.getRow() < 0){
		throw EXCEPTION_OUTSIDE;
	}
	else{
		int movement = Util::getRandomNumber(8);
		switch(movement){
				case (0):
					position.SetRow(position.getRow()-1);
					break;
				case (1):
					position.SetRow(position.getRow()-1);
					position.SetColumn(position.getColumn()+1);
					break;
				case(2):
					position.SetColumn(position.getColumn()+1);
					break;
				case(3):
					position.SetColumn(position.getColumn()+1);
					position.SetRow(position.getRow()+1);
					break;
				case(4):
					position.SetRow(position.getRow()+1);
					break;
				case(5):
					position.SetRow(position.getRow()+1);
					position.SetColumn(position.getColumn()-1);
					break;
				case(6):
					position.SetColumn(position.getColumn()-1);
					break;
				case(7):
					position.SetRow(position.getRow()-1);
					position.SetColumn(position.getColumn()-1);
					break;
				default:
					break;
		}
	}
	return 0;
}

ostream& operator<<(ostream &os,const Betonski &betonski){

	os << "Betonski "<< '"' << betonski.name << '"';
	if(betonski.captured){
		os << " Captured ";
	}
	else{
		os << " Free ";
	}
	os << betonski.anger<<" ["<<betonski.position.getRow()<< ','<< betonski.position.getRow()<< ']'<<'\n';
	
	for(int i = 0; i<int(betonski.bag.size()); i++){
			os << "["<<betonski.bag[i].getType()<<betonski.bag[i].getQuantity()<<"]";
	}
	return os;
}
