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
	for(int i = 0; i<int(traps.size());i++)
		for(int j = 0; j<int(betonskis.size()); j++){
			if(traps[i].getRow() == betonskis[j]->getPosition().getRow() && 
				traps[i].getColumn() == betonskis[j]->getPosition().getColumn() && 
				betonskis[j]->isCaptured() == false){
					
					betonskis[j]->capture();
					this->subdued.push_back(betonskis[j]);
		}
	}
}

bool Jankali::setTrap(const Coordinate &coord){
	for(int i = 0; i<coord.getRow();i++){
		if(coord.getRow() != traps[i].getRow() &&
			coord.getColumn() != traps[i].getColumn() &&
			this->power > (coord.getRow()+2)*(coord.getColumn()+2)){
			
			traps.push_back(this->traps[i]);
			return true;
		}
	}
	return false;
}

void Jankali::spoil(){
	for(int i = 0; i<int(subdued.size());i++){
		try{
			this->power += subdued[i]->spoliation();
		}
		catch (Exception EXCEPTION_REBELION){
			*subdued.erase(subdued.begin()+i);
		}
	}
}

void Jankali::spoil(JunkType type){
	
	for(int i = 0; i<int(this->subdued.size());i++){
			try{
				power += subdued[i]->spoliation(type);
			}
			catch(Exception EXCEPTION_REBELION ){
				*subdued.erase(subdued.begin()+i);
			}
	}
}

void Jankali::spoil(int pos){
	for(int i = 0; i<int(this->subdued.size());i++){
		try{
			if(pos == i){
				this->power += subdued[pos]->spoliation();
			}
		}
		catch(Exception EXCEPTION_REBELION){
			*subdued.erase(subdued.begin()+i);
		}
	}
}


ostream& operator<<(ostream &os,const Jankali &jankali){
	os << "Jankali " << '"' << jankali.name << '"' << ' ' << jankali.power<<endl;
	for(int i = 0; i<int(jankali.subdued.size()); i++){
		
		os << "Betonski " << '"' << jankali.subdued[i]->getName() 
		   << '"' << ' ' << jankali.subdued[i]->isCaptured() << ' '
		   << jankali.subdued[i]->getAnger() << ' ' << '[' 
		   << jankali.subdued[i]->getPosition().getRow() << ',' 
		   << jankali.subdued[i]->getPosition().getColumn() << ']'<<endl;


		for(int j = 0; j<int(jankali.subdued.size()); i++){
			os << Betonski(*jankali.subdued[i]); 
		}

	}

	os << "Traps "; 


	for(int z = 0; z<int(jankali.traps.size());z++){
		os << "[" << jankali.traps[z].getRow() << ","
		   << jankali.traps[z].getColumn() << "]";
	} 
	
	return os;
}
