#include "Jankali.h"



Jankali::Jankali(string name){
	if(name.empty() == true){
		throw EXCEPTION_NAME;
	}
	this->name = name;
	this->power = 300;
}

string Jankali::getName() const{
	return name;
	
	}

int Jankali::getPower() const{
	return power;
	}

void Jankali::hunt(vector<Betonski *> betonskis){
	for(int i = 0; i<int(betonskis.size());i++)
		if(this->traps.getRow() == betonskis[i]->getPosition().getRow() && 
			this->traps.getColumn() == betonskis[i]->getPosition().getColumn() && 
			betonskis[i]->isCaptured() == false){
			
//			betonskis[i]->capture() = true;
//			subdued.push_back(this->betonskis);

	}
}

bool Jankali::setTrap(const Coordinate &coord){
	return false;
}
	
void spoil(){
	

}

void spoil(JunkType type){


}


void spoil(int pos){


}


ostream& operator<<(ostream &os,const Jankali &jankali){
	return os;
	}
