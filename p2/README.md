``` cc
/*
* Eric Mas Belén
* 20930249L
* Grupo 1
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <fstream>
using namespace std;

//Definicion de estrucutras y constantes
const int KMAXSTRING = 50;

enum Error {
  ERR_OPTION,
  ERR_BOOK_TITLE,
  ERR_BOOK_AUTHORS,
  ERR_BOOK_DATE,
  ERR_BOOK_PRICE,
  ERR_ID,
  ERR_FILE,
  ERR_ARGS
};

struct Book {
  unsigned int id;
  string title;
  string authors;
  int year;
  string slug;
  float price;
};

struct BinBook {
  unsigned int id;
  char title[KMAXSTRING];
  char authors[KMAXSTRING];
  int year;
  char slug[KMAXSTRING];
  float price;
};

struct BookStore {
  string name;
  vector<Book> books;
  unsigned int nextId;
};

struct BinBookStore {
  char name[KMAXSTRING];
  unsigned int nextId;
};

//Lista de errores que se producen a la hora de parametros invalidos
void error(Error e) {
  switch (e) { 
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_BOOK_TITLE:
      cout << "ERROR: wrong book title" << endl;
      break;
    case ERR_BOOK_AUTHORS:
      cout << "ERROR: wrong author(s)" << endl;
      break;
    case ERR_BOOK_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_BOOK_PRICE:
      cout << "ERROR: wrong price" << endl;
      break;
    case ERR_ID:
      cout << "ERROR: wrong book id" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
      break;
  }
}

//Menú principal
void showMainMenu() {
  cout << "[Options]" << endl << "1- Show catalog" << endl
       << "2- Show extended catalog" << endl << "3- Add book" << endl
       << "4- Delete book" << endl << "5- Import/export" << endl
       << "q- Quit" << endl << "Option: ";
}

//Catalogo simplificado donde recorremos el vector
void showCatalog(const BookStore &bookStore, Book & libros) {

	for(int unsigned i = 0; i<bookStore.books.size(); i++){
		cout << bookStore.books[i].id << ". " << bookStore.books[i].title <<
		" (" << bookStore.books[i].year << "), " << bookStore.books[i].price <<endl; 
	}
	
}

//Catálogo con todos los datos donde recorremos el vector
void showExtendedCatalog(const BookStore &bookStore) {

	for(int unsigned i = 0; i<bookStore.books.size(); i++){
		cout <<'"' << bookStore.books[i].title <<'"' <<","<<'"'<<bookStore.books[i].authors<<
		'"'<<','<<bookStore.books[i].year<<","<<'"'<<bookStore.books[i].slug
		<<'"'<<','<<bookStore.books[i].price <<endl;
	}
}

//Submódulo de titulo para introducir el título sin comprobar caracteres
void titulotitulo(BookStore &bookStore, Book &libros, bool &import, string &titulo, bool &fail, bool &pass){
	
		fail = false;
		if(import == false){
			cout << "Enter book title: ";				
			getline(cin,titulo);
		}
		else{
			libros.title = titulo;
		}			
		if(titulo.empty()){	
		  fail = true;
		  titulo = " ";
		  error(ERR_BOOK_TITLE);					
		}
		else{		
			fail = false;
			libros.title = titulo;	
		}	
}
//Submódulo para el título de addbook para título	
void titulo(BookStore &bookStore, Book &libros, bool &import, string &titulo){

	bool fail = false;
	string yearstr, pricestr, s;	
	bool pass = false;
	
	do{
		titulotitulo(bookStore, libros, import, titulo, fail, pass);
		if(!fail){
			for(int unsigned i = 0; i < titulo.length(); i++){
				if(!fail){//Comprobamos los caracteres del string y si no cumplen el formato se dara error
					  if(isalnum(libros.title[i]) == 8 || isblank(libros.title[i]) == 1){
						fail = false;
						}
					  else if((libros.title[i] != ',' && libros.title[i] != ':' && libros.title[i] != '-')){
						error(ERR_BOOK_TITLE); 
						fail = true;
						if(import == true){		//Si es desde import, se dejará de importar
							import = false;
							pass = true;	
						}
					} 
				}
			}
		}
	}while(fail == true && !pass);	
}

//Submódulo para pedir el nombre del autor sin verificarlo
void authorname(BookStore &bookStore, Book &libros, bool &import, string &autores, bool &fail, bool &pass){
	
		fail = false;
		if(import == false){
			cout << "Enter author(s): ";			
			getline(cin,libros.authors);
		}
		else if(import == true){
			libros.authors = autores;
		}
		if(libros.authors.empty()){					
		  libros.authors = " ";
		  fail = true;
		  error(ERR_BOOK_AUTHORS);					
		}
		if(fail == true && import == true){		//Si es desde import, se dejará de importar
			import = false;
			pass = true;
		}
}
//Submódulo de addBook para los autores
void authors(BookStore &bookStore, Book &libros, bool &import, string &autores){
	bool fail;
	string yearstr, pricestr, s;
	bool pass = false;
	authorname(bookStore, libros, import, autores, fail, pass);
	
	do{
		if(!fail){//Comprobamos si los caracteres cumplen el formato, sino, se dará error									
			for(int unsigned i = 0; i < libros.authors.length(); i++){
				if(!fail){							
					if(isalnum(libros.authors[i]) != 0 || isblank(libros.authors[i]) != 0){			
						fail = false;
					}
					else if (libros.authors[i] != ',' && libros.authors[i] != ':' && libros.authors[i] != '-' ){
						fail = true;
						error(ERR_BOOK_AUTHORS);
						if(import == true){		//Si es desde import, se dejará de importar
							import = false;
							pass = true;
						}
					}
				}
			}
		}
	}while(fail == true && !pass); 
}

//Submódulo de addBook para la fecha de publicación
void anos(BookStore &bookStore, Book &libros, bool &import, string &fecha){
	string yearstr, pricestr, s;
	bool pass = false, fail = false;
	
	do{
		fail = false;
		if(import == false){
			cout << "Enter publication year: ";			
			getline(cin, yearstr);
		}
		else if(import == true){
			yearstr = fecha;
		}
		if(yearstr.length() > 0){					
			libros.year = stoi(yearstr);	
			if(libros.year <= 1440 || libros.year >= 2022){
				fail = true;
				error(ERR_BOOK_DATE);
				if(import == true){		//Si es desde import, se dejará de importar
					import = false;
					pass = true;
					break;
				}
			}
		}
		else{
			error(ERR_BOOK_DATE);
			fail = true;
			if(import == true){			//Si es desde import, se dejará de importar
				import = false;
				pass = true;
				break;
			}
		}
	}while(fail == true && !pass);
}

//Submódulo de addBook para el precio
void precio(BookStore &bookStore, Book &libros, bool &import, string &price){
	string yearstr, pricestr, s;
	bool pass = false, fail = false;
	
	do{
		fail = false;
		if(import == false){
			cout << "Enter price: ";			
			getline(cin,pricestr);	
		}
		else if (import == true){
			pricestr = price;
		}
		if(pricestr.length() > 0){			
			libros.price = stof(pricestr);
			if(libros.price <= 0){			
				fail = true;				
				error(ERR_BOOK_PRICE);
				if(import == true){			//Si es desde import, se dejará de importar
					import = false;
					pass = true;
				}
			}
		}
		else{
			error(ERR_BOOK_PRICE);
			fail = true;
			if(import == true){				//Si es desde import, se dejará de importar
				import = false;
				pass = true;
			}
		}
	}while(fail == true && !pass);	
}

//Submódulo de addBook para un título modificado
void slug(BookStore &bookStore, Book &libros){
	//Transformamos todos los caracteres no alphanumericos a guiones
	for(int unsigned j = 0 ; j < libros.title.length(); j++){
		libros.slug += tolower(libros.title[j]);
		if(isblank(libros.title[j]) != 0 || libros.title[j] == ',' || libros.title[j] == ':' || libros.title[j] == '-' ){
		  libros.slug[j] = '-';
		}
	}//Si lleva comillas al inicio o al final se deben borrar
	if(libros.slug[0] == '-'){
		libros.slug.erase(libros.slug.begin());
	}
	if(libros.slug[libros.slug.length()-1] == '-'){
		libros.slug.erase(libros.slug.begin()+libros.slug.length()-1);
	}
	for(unsigned j = 0; j<libros.slug.size(); j++){
		if(libros.slug[j] == '-' && libros.slug[j+1] == '-'){
			libros.slug.erase(libros.slug.begin()+j);
			j--;
		}
	}
}

//Módulo para agregar libros
void addBook(BookStore &bookStore) {
	bool import = false;
	string titulolibro, autores, fecha, price, s, yearstr, pricestr;
	Book libros;
	
	titulo(bookStore, libros, import, titulolibro);
	authors(bookStore, libros, import, autores);
	anos(bookStore, libros,import, fecha);
	precio(bookStore, libros, import, price);
	slug(bookStore, libros);
	libros.id =  bookStore.nextId;
	bookStore.nextId++;
	//Devolvemos al vector los datos introducidos
	bookStore.books.push_back(libros);
}

//Módulo para borrar libros
void deleteBook(BookStore &bookStore) { 
	
	int unsigned deleteid;
	int unsigned longitud, i;
	bool encontrado = false;
	longitud = bookStore.books.size();
	
	cout << "Enter book id: ";
	cin >> deleteid;
    for(i = 0; i < longitud && !encontrado; i++){
		if(bookStore.books[i].id == deleteid){
			 //Se borra utilizando la posición inicial del vector + la posición actual y se cambia el valor de encontrado para que pare
			 bookStore.books.erase(bookStore.books.begin()+i);
			 encontrado = true;
		}
	}
	if(encontrado == false){
		error(ERR_ID);
	}
}

//Guardar los datos en binario
void saveData(const BookStore &bookStore){
	Book books;
	BinBook binbooks;
	BinBookStore binstore;
	string filename;
	
	cout << "Enter filename: ";
	getline(cin,filename);
	//Si el string no es nulo creamos/abrimos el fichero binario
	if(filename.size()>0){
		ofstream fe(filename, ios::binary);
			if(fe.is_open()){
				//Copiamos en el binario todos los datos del vector de bookStore dejando siempre el caracter nulo
				strncpy(binstore.name, bookStore.name.c_str(),KMAXSTRING-1);
				binstore.nextId = bookStore.nextId;
				binstore.name[KMAXSTRING] = '\0';
				//Empezamos con la escritura en el archivo binario dejando siempre espacio para el caracter nulo		
				fe.write((const char *) &binstore, sizeof(BinBookStore)); 
				for (int unsigned i = 0; i<bookStore.books.size(); i++){
					binbooks.id = bookStore.books[i].id;
					strncpy(binbooks.title, bookStore.books[i].title.c_str(),KMAXSTRING-1);
					binbooks.title[KMAXSTRING-1] = '\0';
 					strncpy(binbooks.authors, bookStore.books[i].authors.c_str(),KMAXSTRING-1);
					binbooks.authors[KMAXSTRING-1] = '\0';
 					binbooks.year = bookStore.books[i].year;
 					strncpy(binbooks.slug, bookStore.books[i].slug.c_str(),KMAXSTRING-1);
					binbooks.slug[KMAXSTRING-1] = '\0';
 					binbooks.price = bookStore.books[i].price;
 					fe.write((const char * ) &binbooks, sizeof(BinBook));
				}
 				fe.close();
			}
			else{
 				error(ERR_FILE);
			}	
		}
}

//Submodulo de loadData para cargar los datos en binario
void loadData2(BookStore &bookStore, string bindata, string filename,BinBook &binbooks, BinBookStore &binstore, bool &argumenterror, bool &intento){
	Book books;
	
	ifstream fl(filename, ios::binary);			
				if(fl.is_open()){
					fl.read((char * )&binstore, sizeof(BinBookStore));
					bookStore.name = binstore.name;
					bookStore.nextId = binstore.nextId;
					
					while(fl.read((char * ) &binbooks, sizeof(BinBook))){
						books.id = binbooks.id;
						books.title = binbooks.title;
						books.authors = binbooks.authors;
						books.year = binbooks.year;
						books.slug = binbooks.slug;
						books.price = binbooks.price;
						bookStore.books.push_back(books);
					}
				
				fl.close();
			}else{
				error(ERR_FILE);
				if(intento == true){
					argumenterror = true;
					intento = false;
				}		
			}
	}
//Advertencia sobre los datos y pide el nombre del fichero binario
void loadData(BookStore &bookStore, string bindata, bool &doscheck, bool &intento, bool &argumenterror){
	
	Book books;
	BinBook binbooks;
	BinBookStore binstore;
	char opcion;
	string filename;
	
	bookStore.books.clear();		
		if(!bindata.empty()){//Si no esta vacio es que ha se ha pasado algun argumento con nombre de archivo
			filename = bindata;
			doscheck = true;
		}
		else{	
			do{
				cout << "All data will be erased, do you want to continue (Y/N)?: ";
				cin >> opcion;
			}while(opcion != 'Y' && opcion != 'N' && opcion != 'y' && opcion != 'n' );
				if (opcion == 'Y' || opcion == 'y'){
					cin.get();
					cout << "Enter filename: ";
					getline(cin, filename);
				}
		}
		loadData2(bookStore, bindata, filename, binbooks, binstore, intento, argumenterror);
}

//Exportar los datos a un txt normal
void exportToCsv(const BookStore &bookStore){
	string filename;
	int unsigned i;
	i = 0;
	
	cout << "Enter filename: ";
	getline(cin,filename);
	
	if(filename.size()>0){
		ofstream fe(filename);
		if(fe.is_open()){
			for(i = 0; i<bookStore.books.size(); i++){
				fe << '"' << bookStore.books[i].title<< '"' << ',' << '"'
				   <<bookStore.books[i].authors << '"' << ','
				   <<bookStore.books[i].year <<',' << '"'
				   <<bookStore.books[i].slug <<'"' << ','
				   <<bookStore.books[i].price<<endl;
			}
			fe.close();
		}
		else{
			error(ERR_FILE);
		}	
	}
}

//Parte de leer el título y el autor de importFromCSV
void tituloautor(BookStore &bookStore, string data, bool &unocheck, string &titulolibro, string &autor, bool &import, int unsigned &i, string &line, Book &books){			
		if(import){
			while(i<line.length() && line[i] != '"' && import){
				i++;
			}i++;
		}
		if(import){	
			while(line[i] != '"' && i<line.length()  && import){
				titulolibro += line[i];	
				i++;
			}i++;
			titulo(bookStore, books, import, titulolibro);
		}
		if(import){	
			while(line[i] != ',' && i<line.length()  && import){
				i++;
			}i++;
		}
		if(import){	
			while(line[i] != '"' && i<line.length()  && import){
				i++;
			}i++;
		}
		if(import){		
			while(i<line.length() && line[i] != '"' && import){
				autor += line[i];
				i++;
			}i++;
			authors(bookStore, books, import, autor);
		}
		if(import){		
			while(line[i] != ',' && i<line.length() && import){
				i++;
			}i++;
		}
}
//Parte de leer los años, el slug, y el precio de importFromCSV
void anosslugprecio(BookStore &bookStore, string data, bool &unocheck, string &fecha, string &slug, string &price, bool &import, int unsigned &i, string &line, Book &books) {
		if(import){		
			while(line[i] != ',' && i<line.length()  && import){
				fecha += line[i];
				i++;
			}i++;
			anos(bookStore, books, import, fecha);
		}
		if(import){	
			while(line[i] != '"' && i<line.length() && import){
				i++;
			}i++;
		}
		if(import){	
			while(line[i] != '"' && i<line.length() && import){
				slug += line[i];
				i++;
			}i++;
			books.slug = slug;
		}
		if(import){	
			while(line[i] != ',' && i<line.length() && import){
				i++;
			}i++;
		}
		if(import){
			while(i<line.length()){
				price += line[i];
				i++;
			}
		precio(bookStore, books, import, price);
	}
}

//Importar los datos de un txt normal
void importFromCsv(BookStore &bookStore, string data, bool &unocheck, bool &intento, bool &argumenterror){
		bool import = true;
		string filename, line;
		Book books;
		
		if(data.size() > 0){
			filename = data;
		}
		else{
			cout << "Enter filename: ";
			getline(cin, filename);
		}	
			ifstream fl(filename);
				if(fl.is_open()){
					while(getline(fl,line)){
						import = true;
						int unsigned i = 0;
						string titulolibro, autor, fecha, slug, price;
						
						tituloautor(bookStore, data, unocheck, titulolibro, autor, import, i, line, books);
						anosslugprecio(bookStore, data, unocheck, fecha, slug, price, import, i, line, books);
						if(import){		//Si se llega al final sin ningún fallo entonces se hará pushback
							books.id = bookStore.nextId;
							bookStore.nextId++;
							bookStore.books.push_back(books);
						}
					}
						fl.close();
				}	
				else{
					error(ERR_FILE);
					if(intento == true){
						argumenterror = true;
						intento = false;
					}
				}
}

//Submenú para importar/Exportar datos en el programa
void importExportMenu(BookStore &bookStore, string data, string bindata, bool &unocheck, bool &doscheck) {
	bool fail = true, intento = false, argumenterror = false;
	char option;
	
	do{
		cout<<"[Import/export options]"<<endl<<"1- Import from CSV"<<endl
		<<"2- Export to CSV"<<endl<<"3- Load data"<<endl<<"4- Save data"<<endl
		<<"b- Back to main menu"<<endl<<"Option: ";
		cin >> option;
		cin.get();
		switch (option) {
		  case '1':
			importFromCsv(bookStore, data, unocheck, intento, argumenterror);
			fail = true;
			break;
		  case '2':
			exportToCsv(bookStore);
			fail = true;
			break;
		  case '3':
			loadData(bookStore, bindata, doscheck, intento, argumenterror);
			fail = true;
			break;
		  case '4':
			saveData(bookStore);
			fail = true;
			break;
		  case 'b': //BACK
			fail = false;
			break;
		  default:
			error(ERR_OPTION);
			fail = true;
		}
	}while(fail);
}

//Módulo de comprobación de los argumentos
void argcheck(int argc, char *argv[], bool &argumenterror, BookStore &bookStore){
	bool unocheck= false, doscheck = false, intento = true;
	argumenterror = false;
	int countload = 0, countimport = 0;
	string data, bindata;
	
	if(argc <= 5) {
		for( int i = 0; i<argc; i++){
			if(i%2 != 0 && i != 0){		//Las posiciones imparse son las posiciones donde esta el argumento, las pares el nombre
				if(countimport == 0 && strcmp(argv[i],"-i") == 0){		//No puede aparecer el mismo argumento 2 veces, por lo que aumentamos contador
					if(i+1 < argc){
						countimport++;
						data = argv[i+1];
					}
					else if (!argumenterror){
						argumenterror = true;
						error(ERR_ARGS);
					}
				}
				else if (countload == 0 && strcmp(argv[i],"-l") == 0){	//No puede aparecer el mismo argumento 2 veces, por lo que aumentamos contador
					if(i+1 < argc){
						countload++;
						bindata = argv[i+1];
					}
					else if (!argumenterror){
						argumenterror = true;
						error(ERR_ARGS);
					}
				}
				else if (!argumenterror){ 								//Si el argumento es distinto de -l o -i dará error porque no se deben usar otros
					argumenterror = true;
					error(ERR_ARGS);
				}
			}
		}
		if(!argumenterror){
			intento = true;
			if(countload == 1)											// Si ha llegado bien al final, entonces realizamos la funcion de los argumentos en orden
				loadData(bookStore, bindata, unocheck, intento, argumenterror);
			if(countimport == 1)
				importFromCsv(bookStore, data, doscheck, intento, argumenterror);
			intento = false;
		}
	}
}

//Menu de selección de la opción escogida
void menuoptions(BookStore &bookStore, char &option, Book libros, string data, string bindata, bool &unocheck, bool &doscheck, bool &argumenterror){	
		if(argumenterror == false){  
		do {
			showMainMenu();
			cin >> option;
			cin.get();

			switch (option) {
			  case '1':
				showCatalog(bookStore, libros);
				break;
			  case '2':
				showExtendedCatalog(bookStore);
				break;
			  case '3':
				addBook(bookStore);
				break;
			  case '4':
				deleteBook(bookStore);
				break;
			  case '5':
				importExportMenu(bookStore, data, bindata, unocheck, doscheck);
				break;
			  case 'q':
				break;
			  default:
				error(ERR_OPTION);
			}
		} while (option != 'q');
	}
}

//Módulo principal
int main(int argc, char *argv[]) {
  BookStore bookStore;
  bookStore.name = "My Book Store";
  bookStore.nextId = 1;
  Book libros;
  char option;
  string bindata, data;
  bool unocheck= false, doscheck = false, argumenterror = false;    
 
  argcheck(argc, argv, argumenterror, bookStore);
  menuoptions(bookStore, option, libros, data, bindata, unocheck, doscheck, argumenterror);  
  return 0;
}
```
