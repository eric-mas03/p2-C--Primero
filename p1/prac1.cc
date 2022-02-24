/* Programación 2 - Práctica 1
 DNI: 20930249L
 Nombre: Eric Mas Belen
*/

#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <cstring>
#include <stdio.h>

using namespace std;

const int KNAME = 32; // Longitud del nombre del personaje
const int KENEMIES = 5; // Razas de enemigos
const int KPOINTS = 200; // Puntos a distribuir
const int KDICE = 20; // Número de caras del dado

//Definición de estrucuturas para los personajes, generación etc.
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

Hero createHero(Heroe &player, int & longitud);
Enemy createEnemy(Enemy & enemigo, int genera);
void fight(Hero & hero, Enemy & enemy, int &super, int genera, int &huida, int &longitud);
void ataqueheroe(Hero & hero, Enemy & enemy, int &super, int genera, int &huida);
void ataquenemy(Hero & hero, Enemy & enemy, int &super, int genera, int &huida, int & longitud);
void report(const Hero & hero, int longitud);

Hero createHero(Heroe &player, int & longitud) {		//Módulo de creación del personaje
	
  int i, ataque, defensa;
  char barra;
  bool error;
  
	do {
	error = 0;
	cout << "Enter hero name: ";
    //Insertamos el nombre que ocupará KNAME -1 ya que la última posición esta reservada para caracter nulo
    cin.getline(player.name, KNAME - 1);	
	longitud = strlen(player.name);
	
	//Leemos los caracteres insertados para verificar que no se incumplan condiciones
    for (i = 0; i < longitud; i++) {		
	  if (error == 0) { 
         if (isalnum(player.name[i]) != 0 || isblank(player.name[i]) != 0){
          error = 0;
		 }
		 if (isalnum(player.name[i]) == 0 && isblank(player.name[i]) == 0){
		  error = 1;
		 }       
		 if (isdigit(player.name[0]) == 1) {
          error = 1;
         } 
       }
     }

    if (error == 1) {
      //Si se ha incumplido alguna condición mostraremos el mensaje y pediremos el nombre de nuevo
      cout << "ERROR: wrong name" << endl;	
    }
	}while (error == 1);
  
	//Leemos los parametros de ataque y defensa y en caso de ser no validos volveremos a pedirlos mostrando un error
	do{										
		error = 0;							
		cout << "Enter attack/defense: ";
		cin>>ataque>>barra>>defensa;
		
		if(barra != '/'){
			error = 1;
		}
		
		if(error == 1|| (ataque+defensa != 100) || ataque == 0 || defensa == 0){
			cout <<"ERROR: wrong distribution"<<endl<<endl;
		}
	}while((error == 1) || (ataque+defensa != 100) || (ataque == 0 || defensa == 0));
		
		//Inicializamos sus parámetros
		player.features.attack = KPOINTS*ataque/100;
		player.features.defense = KPOINTS*defensa/100;
		player.features.hp = player.features.defense*2;
		player.special = true;
		player.runaways = 3;
		player.exp = 0;
			
  		for(i = 0; i<KENEMIES; i++){
  			player.kills[i] = 0;
  		}
  		
  	return player;
}

Enemy createEnemy(Enemy & enemigo, int genera) {		//Módulo de creación del enemigo

	//En función del valor obtenido por el dado en el dado generaremos el enemigo con sus caracterísiticas	
	if (genera <= 6 && genera <= 6) { //Ajolote
		enemigo.features.attack = 40;
		enemigo.features.defense = 40;
		enemigo.name = AXOLOTL;
	}
	if (genera >= 7 && genera <= 11) { //Troll
		enemigo.features.attack = 60;
		enemigo.features.defense = 80;
		enemigo.name = TROLL;
	}
	if (genera >= 12 && genera <= 15) { //Orc
		enemigo.features.attack = 80;
		enemigo.features.defense = 120;
		enemigo.name = ORC;  
		}
	if (genera >= 16 && genera <= 18) { //Hell Hound
		enemigo.features.attack = 120;
		enemigo.features.defense = 100;
		enemigo.name = HELLHOUND;
	}
	if (genera >= 19 && genera <= 20) { //Dragon
		enemigo.features.attack = 160;
		enemigo.features.defense = 140;
		enemigo.name = DRAGON;
	}
	enemigo.features.hp = enemigo.features.defense * 2;

	//Mostramos el texto que identifiacará al enemigo y lo mostrará por pantalla
	cout << "[Enemy]" << endl << "Breed: ";
	switch(enemigo.name){
			case 0:
				cout << "Axolotl"<<endl;
				break;
			
			case 1:
				cout << "Troll"<<endl;
				break;
			
			case 2:
				cout << "Orc"<<endl;
				break;
			
			case 3:
				cout << "Hellhound"<<endl;
				break;
			
			case 4:
				cout << "Dragon"<<endl;
				break;
			
			default:
			break;

		}
	cout << "Attack: " << enemigo.features.attack << endl;
	cout << "Defense: " << enemigo.features.defense << endl;
	cout << "Health points: " << enemigo.features.hp <<endl;
  
	return enemigo;

}

void ataqueheroe(Hero & hero, Enemy & enemy, int &super, int genera, int &huida){		//Subdivisión del módulo fight en el que es el turno del héroe
		
	int dado, damage, newattack, newdefense, hp;
	huida = 0;									//Ponemos a huidas a 0 para que pueda volver a hacer runaway ya que ha atacado
	hp = enemy.features.hp;
		
	//Calculamos el ataque del héroe
	cout << "[Hero -> Enemy]"<<endl;		
	dado = rollDice()*5;						
		
	//En caso de haber actvidado el special desde el menú se efectuará el ataque con dado *3
	if(super == 1 && hero.special == true){			
		hero.special = false;
		newattack = hero.features.attack + dado*3;
		cout << "Attack: " << hero.features.attack << " + " << dado*3<<endl;	
	}
	//En caso de no haber activado el special desde el menú se efectuará el ataque con dado normal 
	else {											
		newattack = hero.features.attack + dado;
		cout << "Attack: " << hero.features.attack << " + " << dado<<endl;
	}
	
	//Calculamos la defensa del héroe
	dado = rollDice()*5;
	newdefense = enemy.features.defense + dado;
	damage = newattack - newdefense;
	cout << "Defense: " << enemy.features.defense << " + " << dado<<endl;
	
	//Si los hitpoints son negativos los pondremos a 0
	if(newattack < newdefense){
		damage = 0;		
	}	
	cout << "Hit points: " << damage << endl;
	
	//Calculamos la vida en función del ataque y la defensa
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
	cout << "Enemy health points: " << enemy.features.hp << endl;
	
}	

void ataquenemy(Hero & hero, Enemy & enemy, int &super, int genera, int &huida, int & longitud){		//Subdivisión del modulo fight para el turno enemigo
		
		int dado, damage, newattack, newdefense, hp;
		hp = hero.features.hp;
		cout << "[Enemy -> Hero]"<<endl;		
		
		//Calculamos el ataque del enemigo
		dado = rollDice()*5;
		newattack = enemy.features.attack + dado;
		cout << "Attack: " << enemy.features.attack << " + " << dado<<endl;
		
		//Calculamos la defensa del enemigo
		dado = rollDice()*5;
		newdefense = hero.features.defense + dado;
		cout << "Defense: " << hero.features.defense << " + " << dado <<endl;
		
		damage = newattack - newdefense;
		
		//En caso de ser daño negativo lo pondremos a 0
		if(newattack < newdefense){
			damage = 0;	
		}
		cout << "Hit points: " << damage << endl;
		
		//En función del daño calculamos la vida del heroe
		if(newattack >= newdefense){
			hp = hero.features.hp - damage;
			hero.features.hp = hp;
		}
		if(newattack < newdefense){
			hero.features.hp = hp;
		}
		if(hero.features.hp <= 0){
			hero.features.hp = 0;
		}
		cout << "Hero health points: " << hero.features.hp<<"\n";
	
		//En caso de tener vida 0 o negativa, el heroe habrá muerto y se llamará a report
		if(hero.features.hp <= 0){
			cout << "You are dead" <<endl;
			report(hero, longitud);
		}
	}

void fight(Hero & hero, Enemy & enemy, int &super, int genera, int &huida, int &longitud) {			// Pelea con turnos
	
	//Llamamos a el ataque del héroe
	ataqueheroe(hero, enemy, super, genera, huida);
	
	//Calculamos la exp obtenida y aumentamos el contador de kills
	if(enemy.features.hp <= 0){
		cout << "Enemy killed"<<endl;
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
		//Llamamos a el ataque del enemigo si este sigue vivo
		ataquenemy(hero, enemy, super, genera, huida, longitud);
	}
}

void report(const Hero & hero, int longitud) {		//Módulo que muestra las estadísitcas del héroe
	
	int i, total_kills;
	total_kills = 0;
	
	cout << "[Report]"<<endl<<"Name: ";
	
	//Mostramos el nombre del héroe sin espacios basura utilizando el longitud obtenido del createhero
	for(i = 0; i<longitud; i++){
		cout << hero.name[i];
	}
	cout << endl;
	
	//Mostramos estadísticas
	cout <<"Attack: " << hero.features.attack<<endl
	<<"Defense: " << hero.features.defense<<endl
	<<"Health points: " << hero.features.hp<<endl
	<<"Special: ";
	if(hero.special){
		cout << "yes"<<endl;
	}
	else{
		cout << "no" << endl;
	}
	cout << "Runaways: " << hero.runaways<<endl
	<<"Exp: " << hero.exp<<endl
	<<"Enemies killed: "<<endl
	<<"- Axolotl: "	<< hero.kills[0]<<endl
	<<"- Troll: " << hero.kills[1]<<endl
	<<"- Orc: "	<< hero.kills[2]<<endl
	<<"- Hellhound: "<< hero.kills[3]<<endl
	<<"- Dragon: "<< hero.kills[4]<<endl
	<<"- Total: "; 
	for(i = 0; i<KENEMIES; i++){
		total_kills = total_kills + hero.kills[i];
	}
	cout << total_kills<<endl;
}

void showMenu() {		//Módulo que muestra el menu de opciones
	  
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
	int genera, error, super, huida, longitud;
	char opcion;

	if (argc != 2) { // Si los parámetros no son correctos, el programa termina inmediatamente
		cout << "Usage: " << argv[0] << " <seed>" << endl;
	}
	
	else {
		srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
	}
	
	//Creamos al héroe y a su primer enemigo
	createHero(player, longitud);
	genera = rollDice();
	createEnemy(enemigo, genera);
	super = 0;
	huida = 0;
	
	//Comenzamos el bucle que mostrará el menú y realizará la opción seleccionada en función de este
		do{
			if(player.features.hp > 0){
				showMenu(); 		//Mostramos el menú   
				cin >> opcion;		//Pedimos opción
				error = 0;
							
				switch (opcion) {	//En fución de la opción se elige una acción
					case '1':		//Entra en batalla
						fight(player, enemigo, super, genera, huida, longitud);
						break;

					case '2':		//Utiliza runaway una vez y cambia huida para que no pueda huir de nuevo
						if(player.runaways > 0 && huida == 0){
							player.runaways--;
							cout << "You run away" << endl;
							genera = rollDice();
							createEnemy(enemigo, genera);
							huida = 1;	
						}
						else{		//Si no puede porque tiene que atacar o no le quedan muestra el mensaje
							cout << "ERROR: cannot run away" <<endl;
						}
						break;
					
					case '3':		//Utiliza el ataque especial y cambia a super para que no pueda volver a entrar
						if(player.special == true && super == 0){
							super++;
							fight(player, enemigo, super, genera, huida, longitud);
						}
						else{		//Si no puede usarlo porque lo ha gastado muestra el mensaje
							cout << "ERROR: special not available" << endl;
						}
						break;
					
					case '4':		//Muestra por pantalla las estadísticas del héroe
						report(player, longitud);
						break;
					
					case 'q':		//Acaba el programa 
						player.features.hp = 0;
						break;

					default: 		//Si no existe la opción da error y vuelve a pedirla
						error = 1;
						cout << "ERROR: wrong option" << endl;
						break;
				}
				if (player.features.hp <= 0){	//Si el jugador tiene vida negativa acaba el programa (Ya muestra las estadísitcas en el submodulo de fight)
					return 0;
				}
				if(enemigo.features.hp <= 0){	//Si el enemigo ha muerto se vuelve a generar otro
					genera = rollDice();
					createEnemy(enemigo, genera);				
				}
			
			
			}
				
		} while (error == 1 || opcion != 'q' || player.features.hp != 0);	//Estará en bucle hasta que muera 

}

