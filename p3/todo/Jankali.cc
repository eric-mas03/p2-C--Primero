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

//ARREGLAR LA FORMA DE RECORRER EL TRAP YA QUE LA J PUEDE SER DISITNTA DE I Y POR ESO DA ERROR
bool Jankali::setTrap(const Coordinate &coord){	
	bool existe = false;
	
	for (int i = 0; i<int(traps.size());i++){
		
		bool esta = coord.compare(this->traps[i]);
		if(esta == true)
			existe = true;
	}

	if(this->power > int((coord.getRow()+2)*(coord.getColumn()+2)) && existe == false){
				
				this->power = this->power - int((coord.getRow()+2)*(coord.getColumn()+2));
				this->traps.push_back(coord);

				return true;
	}
	return false;
	}

/*
	
	for(int i = 0; i < int(coord.getRow());i++){
		if(int(coord.getRow()) != int(this->traps[i].getRow())){
			
			for(int j = 0; j<int(coord.getColumn());j++){
			
				if(int(coord.getColumn()) != int(this->traps[j].getColumn()) &&
				   int(coord.getRow()) != int(this->traps[j].getRow()) &&
				   this->power >= (coord.getRow()+2)*(coord.getColumn()+2)){
					
					this->power = this->power - int((coord.getRow()+2)*(coord.getColumn()+2));
					traps.push_back(this->traps[j]);
					return true;
				   }
				}
			}
		}
	return false;
	}
	*/


void Jankali::spoil(){
	for(int i = 0; i<int(subdued.size());i++){
		try{
			this->power += subdued[i]->spoliation();
		}
		catch (Exception e){
			*subdued.erase(subdued.begin()+i);
			i--;
		}
	}
}

void Jankali::spoil(JunkType type){
	
	for(int i = 0; i<int(this->subdued.size());i++){
			try{
				power += subdued[i]->spoliation(type);
			}
			catch(Exception e){
				*subdued.erase(subdued.begin()+i);
				i--;
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
		catch(Exception e){
			*subdued.erase(subdued.begin()+i);
			i--;
		}
	}
}


ostream& operator<<(ostream &os,const Jankali &jankali){
	os << "Jankali " << '"' << jankali.getName() << '"' << ' ' << jankali.getPower()<<endl;
	
		for(int j = 0; j<int(jankali.subdued.size()); j++){
			os << (*jankali.subdued[j]); 
		}



	os << "Traps "<<endl; 

	for(int i = 0; i<int(jankali.traps.size());i++){
		os << "[" << jankali.traps[i].getRow() << ","
		   << jankali.traps[i].getColumn() << "]";
	} 
	
	return os;
}
