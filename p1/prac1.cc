/* Programación 2 - Práctica 1
 DNI: 20930249L
 Nombre: Eric Mas Belen
*/

#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
using std::string;

const int KNAME = 32; // Longitud del nombre del personaje
const int KENEMIES = 5; // Razas de enemigos
const int KPOINTS = 200; // Puntos a distribuir
const int KDICE = 20; // Número de caras del dado

struct Core {
  int attack;
  int defense;
  int hp;
};

enum Breed {
  AXOLOTL,
  TROLL,
  ORC,
  HELLHOUND,
  DRAGON
};

struct Enemy {
  Breed name;
  Core features;
};

struct Hero {
  char name[KNAME];
  Core features;
  bool special;
  int runaways;
  int exp;
  int kills[KENEMIES];
};

int rollDice() {
  return rand() % KDICE + 1;
}

typedef Hero Heroe;
typedef Enemy Enemigo;

Hero createHero(Heroe & player) {
 
  int i, error, longitud, ataque, defensa;
  char barra;
  
  //Verificar nombre de Héroe ---> Comprobado
  do {
    error = 0;
    cout << "Enter hero name : " << endl;
    cin.getline(player.name, KNAME - 1);
	longitud = strlen(player.name);
	
    for (i = 0; i < longitud; i++) {
      if (error == 0) {

        if (isalnum(player.name[i]) == 0) {
          error = 1;
        }
      }
    }

    if (error == 1) {
      cout << "ERROR: wrong name" << endl << endl;
    }

  } while (error == 1);

  

  do{
	error = 0;
	cout << "Enter attack/defense:" << endl;
	cin>>ataque>>barra>>defensa;
	cout << endl;
	
	if(barra != '/'){
		error = 1;
	}
	
	if(error == 1|| (ataque+defensa != 100)){
		cout <<"ERROR: wrong distribution"<<endl<<endl;
	}
	
	}while((error == 1) || (ataque+defensa != 100) || (ataque == 0 || defensa == 0));

		player.features.attack = KPOINTS*ataque/100;
		player.features.defense = KPOINTS*defensa/100;
		player.features.hp = player.features.defense*2;
		player.special = true;
		player.runaways = 3;
		player.exp = 0;
			
  		for(i = 0; i<KENEMIES; i++){
  			player.kills[i] = 0;
  		}
  	
}

Enemy createEnemy(Enemy & enemigo, int genera) { //No funciona decir el nombre del enemigo <-------------------
  char breed[100];
  
	enemigo.features.attack = 0;
	enemigo.features.defense = 0;
	enemigo.features.hp = 0;
	
  if (genera <= 6 && genera <= 6) { //Ajolote
    enemigo.features.attack = 40;
    enemigo.features.defense = 40;
    enemigo.features.hp = enemigo.features.defense * 2;
    strcpy(breed, "AXOLOTL");
  }
  if (genera >= 7 && genera <= 11) { //Troll
    enemigo.features.attack = 60;
    enemigo.features.defense = 80;
    enemigo.features.hp = enemigo.features.defense * 2;
    strcpy(breed, "TROLL");
  }
  if (genera >= 12 && genera <= 15) { //Orc
    enemigo.features.attack = 80;
    enemigo.features.defense = 120;
    enemigo.features.hp = enemigo.features.defense * 2;
    strcpy(breed, "ORC");
  }
  if (genera >= 16 && genera <= 18) { //Hell Hound
    enemigo.features.attack = 120;
    enemigo.features.defense = 100;
    enemigo.features.hp = enemigo.features.defense * 2;
    strcpy(breed, "HELLHOUND");
  }
  if (genera >= 19 && genera <= 20) { //Dragon
    enemigo.features.attack = 160;
    enemigo.features.defense = 140;
    enemigo.features.hp = enemigo.features.defense * 2;
    strcpy(breed, "DRAGON");
  }

  cout << "[Enemy]" << endl;
  cout << "Breed: " << breed << endl;
  cout << "Attack: " << enemigo.features.attack << endl;
  cout << "Defense: " << enemigo.features.defense << endl;
  cout << "Healt points: " << enemigo.features.hp << endl << endl;
  
}

void fight(Hero & hero, Enemy & enemy, int super, int genera) {
	int dado, damage, newattack, newdefense, hp;
	hp = enemy.features.hp;
	newattack = 0;
	newdefense = 0;
	
	cout << "[Hero -> Enemy]"<<endl;		
	
		dado = rollDice()*5;
		if(super == 1 && hero.special == true){
			hero.special = false;
			newattack = hero.features.attack + dado*3;
			cout << "Attack : " << hero.features.attack << " + " << dado*3<<endl;
		}
		
		else {
			newattack = hero.features.attack + dado;
			cout << "Attack : " << hero.features.attack << " + " << dado<<endl;
		}


	dado = rollDice()*5;
	newdefense = enemy.features.defense + dado;
		
	cout << "Defense : " << enemy.features.defense << " + " << dado<<endl;
		
	damage = newattack - newdefense;
		
	if(newattack < newdefense){
		damage = 0;		
	}
		
	cout << "Hit points : " << damage << endl;
	if(newattack >= newdefense){
		hp = enemy.features.hp - damage;
		enemy.features.hp = hp;
	}
	if(newattack < newdefense){
		enemy.features.hp = hp;
	}
	if(enemy.features.hp < 0){
		enemy.features.hp = 0;
	}
	
	cout << "Enemy healt points : " << enemy.features.hp << endl << endl;
	
	if(enemy.features.hp <= 0){
		cout << "Enemy killed"<<endl<<endl;
		if (genera <= 6 && genera <= 6) { //Ajolote
			hero.kills[0]++;
			hero.exp = hero.exp+100;
		}
		if (genera >= 7 && genera <= 11) { //Troll
			hero.kills[1]++;
			hero.exp = hero.exp+150;
		}	
		if (genera >= 12 && genera <= 15) { //Orc
			hero.kills[2]++;
			hero.exp = hero.exp+200;
		}
		if (genera >= 16 && genera <= 18) { //Hell Hound
			hero.kills[3]++;
			hero.exp = hero.exp+300;
		}
		if (genera >= 19 && genera <= 20) { //Dragon
			hero.kills[4]++;
			hero.exp = hero.exp+400;
		}
	}
	else{
		hp = hero.features.hp;
		
		cout << "[Enemy -> Hero]"<<endl;		
	
		dado = rollDice()*5;
		newattack = enemy.features.attack + dado;
	
		cout << "Attack : " << enemy.features.attack << " + " << dado<<endl;
	
	
		dado = rollDice()*5;
		newdefense = hero.features.defense + dado;
		
		cout << "Defense : " << hero.features.defense << " + " << dado <<endl;
		
		damage = newattack - newdefense;
		
		if(newattack < newdefense){
			damage = 0;
			
		}
		
		cout << "Hit points : " << damage << endl;
		
		if(newattack >= newdefense){
			hp = hero.features.hp - damage;
			hero.features.hp = hp;
		}
		if(newattack < newdefense){
			hero.features.hp = hp;
		}
		if(hero.features.hp < 0){
			hero.features.hp = 0;
		}
		
		cout << "Hero healt points : " << hero.features.hp << endl << endl;
	
		if(hero.features.hp <= 0){
			cout << "You are dead" <<endl;
		}
	}
}

void report(const Hero & hero) {
	
	int i, total_kills;
	
	total_kills = 0;
	
	cout << "[Report]"<<endl
	<<"Name: ";
	
	for(i = 0; i<KNAME; i++){
		cout << hero.name[i];
	}
	
	cout << endl;
	cout <<"Attack: " << hero.features.attack<<endl
	<<"Defense: " << hero.features.defense<<endl
	<<"Health Points: " << hero.features.hp<<endl
	<<"Special: ";
	
	if(hero.special){
		cout << "yes"<<endl;
	}
	else{
		cout << "no" << endl;
	}
	
	cout << "Runaways: " << hero.runaways<<endl
	<<"Exp: " << hero.exp <<endl
	<<"Enemies killed: "<<endl
	<<"- Axolotl: " << hero.kills[0]<<endl
	<<"- Troll: " << hero.kills[1]<<endl
	<<"- Orc: " << hero.kills[2]<<endl
	<<"- Hellhound: " << hero.kills[3]<<endl
	<<"- Dragon: " << hero.kills[4]<<endl
	<<"- Total: "; 
	
	for(i = 0; i<KENEMIES; i++){
		total_kills = total_kills + hero.kills[i];
	}
	
	cout << total_kills<<endl<<endl;
}

void showMenu() { 
	  
	cout << "[Options]" << endl <<
			"1- Fight" << endl <<
			"2- Run away" << endl <<
			"3- Special" << endl <<
			"4- Report" << endl <<
			"q- Quit" << endl <<
			"Option: ";
}

int main(int argc, char * argv[]) {

	Heroe player;
	Enemigo enemigo;
	int genera, error, super;
	char opcion;
	
	
	
	if (argc != 2) { // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
	}
  
	else {
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
	}


	createHero(player);
	super = 0;
	genera = rollDice();
	createEnemy(enemigo, genera);
	
	
		
		do{
			if(player.features.hp > 0){
				showMenu();   
				cin >> opcion;
				cout << endl;
				error = 0;
							
				switch (opcion) {
		   
					case '1':
						fight(player, enemigo, super, genera);
						break;

					case '2':
						if(player.runaways > 0){
							
							player.runaways--;
							cout << "You run away" << endl;
							genera = rollDice();
							createEnemy(enemigo, genera);
							
						
						}
						
						else{
							cout << "ERROR: cannot run away" <<endl;
						}
						
						break;
					
					case '3':
						if(player.special == true && super == 0){
							super++;
						}
						else{
							cout << "ERROR: special not available" << endl;
						}
						
						break;
					
					case '4':
						report(player);
						break;
					
					case 'q':
						cout << "Caso quit" << endl;
						player.features.hp = 0;
						cout << player.features.hp << endl;
						break;

					default: 
						error = 1;
						cout << "ERROR: wrong option" << endl;
						break;
				}
			
				if(enemigo.features.hp <= 0){
						genera = rollDice();
						createEnemy(enemigo, genera);				
				}
					
			}
			
			if(opcion == 'q' || player.features.hp	== 0){
				return 0;
			}

		} while (error == 1 || opcion != 'q' || player.features.hp == 0);	
}

