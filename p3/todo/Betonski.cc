#include "Betonski.h"

Betonski::Betonski(string name){
	if(name.empty()){
		throw EXCEPTION_NAME;
	}
	this->name = name;
	captured = false;
	anger = 0;

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
	this->captured = true;
}
	
void Betonski::setPosition(const Coordinate &coord){
	this->position = coord;
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
		int otra = 0;
		if(!captured){
			throw BETONSKI_NOT_CAPTURED;
		}
	
		if(anger+calculateValue(type)>5000){
			this->captured = false;
			this->anger = 0;
			throw EXCEPTION_REBELION;
		}
		
		int masanger = calculateValue(type);
		otra += masanger;
		this->anger += masanger;
		
		for(int i = 0; i < int(bag.size()) ; i++){
			if(bag[i].getType() == type){
				bag.erase(bag.begin()+i);
				i--;
			}
		}
	return otra;
}

	
int Betonski::extract(Map &map){
	char pick;
	Junk temporal;
	int atemporal = 0;
		
		temporal = map.collectJunk(position);
		pick = temporal.getTypeChar();
			if(pick != 'W'){
				bag.push_back(temporal);
				atemporal = temporal.getValue();
			}
	
	return atemporal;
}
	
bool Betonski::move(const Map &map){
	Coordinate prueba;
	prueba.setColumn(-1);
	prueba.setRow(-1);

	if(position.getColumn() < 0 && position.getRow() < 0){
		throw EXCEPTION_OUTSIDE;
	}
	
	else{
		prueba = position;
		int movement = Util::getRandomNumber(8);
		switch(movement){
			case (0):
				prueba.setRow(prueba.getRow()-1);
				break;
			case (1):
				prueba.setRow(prueba.getRow()-1);
				prueba.setColumn(prueba.getColumn()+1);
				break;
			case(2):
				prueba.setColumn(prueba.getColumn()+1);
				break;
			case(3):
				prueba.setColumn(prueba.getColumn()+1);
				prueba.setRow(prueba.getRow()+1);
				break;
			case(4):
				prueba.setRow(prueba.getRow()+1);
				break;
			case(5):
				prueba.setRow(prueba.getRow()+1);
				prueba.setColumn(prueba.getColumn()-1);
				break;
			case(6):
				prueba.setColumn(prueba.getColumn()-1);
				break;
			case(7):
				prueba.setRow(prueba.getRow()-1);
				prueba.setColumn(prueba.getColumn()-1);
				break;
		}
	}

	if(map.isInside(prueba) == true){
		position = prueba;
		return true; 
	}

	else{
		return false;
	}
}

ostream& operator<<(ostream &os,const Betonski &betonski){
	os << "Betonski "<< '"' << betonski.name << '"';
	if(betonski.isCaptured() == true){
		os << " Captured ";
	}
	else{
		os << " Free ";
	}
	os << betonski.anger<<" ["<<betonski.position.getRow()<< ','<< betonski.position.getColumn()<< ']'<<'\n';
	
	for(int i = 0; i<int(betonski.bag.size()); i++){
		os << Junk(betonski.bag[i]);
	}

	return os;
}
	
