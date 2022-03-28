``` cc
/*
* Eric Mas Belén
* 20930249L
* Grupo 1
*/

#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <cstring>
#include <stdio.h>
#include <vector>
#include <fstream>


using namespace std;

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



void importExportMenu(BookStore &bookStore, string data, string bindata, bool &unocheck, bool &doscheck);

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
  cout << "[Options]" << endl
       << "1- Show catalog" << endl
       << "2- Show extended catalog" << endl
       << "3- Add book" << endl
       << "4- Delete book" << endl
       << "5- Import/export" << endl
       << "q- Quit" << endl
       << "Option: ";
}

//Catalogo simplificado 
void showCatalog(const BookStore &bookStore, Book & libros) {
	

	//Recorremos el vector hasta su ultima posición con "vector".size()
	//Imprimimos los datos simplificados de cada libro
	for(int unsigned i = 0; i<bookStore.books.size(); i++){
		cout << bookStore.books[i].id << ". " << bookStore.books[i].title <<
		" (" << bookStore.books[i].year << "), " << bookStore.books[i].price <<endl; 
	}
	
}

//Catálogo con todos los datos
void showExtendedCatalog(const BookStore &bookStore) {
	
	//Recorremos el vector hasta su ultima posición con "vector".size()
	//Imprimimos todos los datos de cada libro
	for(int unsigned i = 0; i<bookStore.books.size(); i++){
		cout <<'"' << bookStore.books[i].title <<'"' <<","<<'"'<<bookStore.books[i].authors<<
		'"'<<','<<bookStore.books[i].year<<","<<'"'<<bookStore.books[i].slug
		<<'"'<<','<<bookStore.books[i].price <<endl;
	}
}

//Submódulo de addBook para el título
void titulo(BookStore &bookStore, Book &libros, bool import, string &titulo){
	string data = "";
	string bindata = "";
	bool unocheck = false;
	bool doscheck = false;
	int longitud, i;
	bool fail;
	string s;
	longitud = 0;
	string yearstr, pricestr;	
	
	
	do{ 
		fail = false;
		if(import == false){
			cout << "Enter book title: ";				
			getline(cin,libros.title);
		}
		else{
			libros.title = titulo;
		}
		longitud = libros.title.length();		
		if(libros.title.empty() && !import){		//Si el nombre introducido es nulo dará error
		  fail = true;
		  error(ERR_BOOK_TITLE);					//Muestra mensaje de error
		}
		else if (libros.title.empty() && import){
			importExportMenu(bookStore, data, bindata, unocheck, doscheck);
			}
		if(!fail){									//Si no hay error empezamos a recorrer el título
			
			for(i = 0; i < longitud; i++){
		  
				if(!fail){							
					  
					  //Si son caracteres alphanumericos o espacio no dará error
					  if(isalnum(libros.title[i]) == 8 || isblank(libros.title[i]) == 1){
						fail = false;
						}
					  //En caso de no serlo se comprobará si está dentro de los carácteres permitidos
					  else if(libros.title[i] != ',' && libros.title[i] != ':' && libros.title[i] != '-'){
						
						error(ERR_BOOK_TITLE); 
						fail = true;
							if(import == true){
								importExportMenu(bookStore, data, bindata, unocheck, doscheck);
							}
					 }
				} 	
			}
		}	  
	}while(fail == true);
		
}

//Submódulo de addBook para los autores
void authors(BookStore &bookStore, Book &libros, bool import, string &autores){
	string data = "";
	string bindata = "";
	bool unocheck = false;
	bool doscheck = false;
	int longitud, i;
	bool fail;
	string s;
	longitud = 0;
	string yearstr, pricestr;
	
	do{
		fail = false;
		
		if(import == false){
			cout << "Enter author(s): ";			
			getline(cin,libros.authors);
		}
		else if(import == true){
			libros.authors = autores;
		}
		longitud = libros.authors.length();
		//Si el nombre introducido es nulo dará error
		if(libros.authors.empty()){					
		  fail = true;
		  error(ERR_BOOK_AUTHORS);					
		}
		else if(libros.authors.empty() && import){		
			importExportMenu(bookStore, data, bindata, unocheck, doscheck);
		}
		if(!fail){									
			for(i = 0; i < longitud; i++){
				if(!fail){							
				 
					
					if(isalnum(libros.authors[i]) != 0 || isblank(libros.authors[i]) != 0){			
						fail = false;
					}
					
					else if (libros.authors[i] != ',' && libros.authors[i] != ':' && libros.authors[i] != '-' ){
						
						fail = true;
						error(ERR_BOOK_TITLE);
						
						if(import == true){
							importExportMenu(bookStore, data, bindata, unocheck, doscheck);
						}
					}
				}
			}
		}
	}while(fail == true);	 
}

//Submódulo de addBook para la fecha de publicación
void anos(BookStore &bookStore, Book &libros, bool import, string &fecha){

	string data = "";
	string bindata = "";
	bool fail;
	bool unocheck = false;
	bool doscheck = false;
	string s;
	string yearstr, pricestr;

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
			libros.year = stoi(yearstr);			//Transformamos la cadena a un int
			
			if(libros.year <= 1440 || libros.year >= 2022){
				fail = true;
				error(ERR_BOOK_DATE);
				
				if(import == true){
							importExportMenu(bookStore, data, bindata, unocheck, doscheck);
						}
				}
		}
		else{
			
			error(ERR_BOOK_DATE);
			fail = true;
			}
	}while(fail == true);
}

//Submódulo de addBook para el precio
void precio(BookStore &bookStore, Book &libros, bool import, string &price){

	string data = "";
	string bindata = "";
	bool fail;
	bool unocheck = false;
	bool doscheck = false;
	string s;
	string yearstr, pricestr;
	
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
			libros.price = stof(pricestr);	//Transformamos la cadena a un float

			if(libros.price < 0){			
				fail = true;				
				error(ERR_BOOK_PRICE);
				if(import == true){
							importExportMenu(bookStore, data, bindata, unocheck, doscheck);
				}
			}
		}
		
		else{

			error(ERR_BOOK_PRICE);
			fail = true;
		}
		
	}while(fail == true);	
	
}

//Submódulo de addBook para un título modificado
void slug(BookStore &bookStore, Book &libros){
	
	
	string s;
	string yearstr, pricestr;
	
	for(int unsigned j = 0 ; j < libros.title.length(); j++){
		
		libros.slug += tolower(libros.title[j]);
		
		if(isblank(libros.title[j]) != 0 || libros.title[j] == ',' || libros.title[j] == ':' || libros.title[j] == '-' ){
		  libros.slug[j] = '-';
		}
	}
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
	string titulolibro = "";
	string autores = "";	
	string fecha = "";
	string price = "";
	Book libros;
	string s;
	string yearstr, pricestr;

	
	titulo(bookStore, libros, import, titulolibro);
	authors(bookStore, libros, import, autores);
	anos(bookStore, libros,import, fecha);
	precio(bookStore, libros, import, price);
	slug(bookStore, libros);
			
	//Agregamos e incrementamos la Id para el siguiente libro
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
 
	//Comenzamos a leer el vector
    for(i = 0; i < longitud && !encontrado; i++){
		//En el momento que se encuentra la ID
		if(bookStore.books[i].id == deleteid){
			 //Se borra utilizando la posición inicial del vector + la posición actual y se cambia el valor de encontrado para que pare
			 bookStore.books.erase(bookStore.books.begin()+i);
			 encontrado = true;
		}
	}
	
	//En caso de no haberlo encontrado
	if(encontrado == false){
		//Se emite error
		error(ERR_ID);
	}
}

//Guardar los datos en binario
void saveData(const BookStore &bookStore){
	
	//Declaramos las variables que utilizaremos	
	Book books;
	BinBook binbooks;
	BinBookStore binstore;
	string filename;
	int unsigned i;
	i = 0;
	
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
				
			
				for (i = 0; i<bookStore.books.size(); i++){
				
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

//Cargar los datos en binario
void loadData(BookStore &bookStore, string bindata, bool &doscheck){ //NO SE POR DONDE EMPEZAR DIRECTAMENTE.
	
	Book books;
	BinBook binbooks;
	BinBookStore binstore;
	char opcion;
	string filename, line;
	bookStore.books.clear();
			
			if(doscheck == false && bindata.size() >0){
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
			}
			else{
				error(ERR_FILE);			
			}
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
					fe << '"' << bookStore.books[i].title
					   << '"' << ',' << '"'
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

//Importar los datos de un txt normal
void importFromCsv(BookStore &bookStore, string data, bool &unocheck){
		bool import = true;
		string filename, t;
		int unsigned i;
		Book books;
		string line;
		
		if(unocheck == false && data.size() > 0){
			filename = data;
			unocheck = true;	
		}
		
		else{
			cout << "Enter filename: ";
			getline(cin, filename);
		}	
			
			ifstream fl(filename);
				if(fl.is_open()){
					import = true;
					while(getline(fl,line)){
						
						i = 0;
						string titulolibro, autor, fecha, slug, price;
						titulolibro = "";
						autor = "";
						while(i<line.length() && line[i] != '"' && import){
							i++;
						}
						i++;
						
						while(line[i] != '"' && i<line.length()  && import){
							titulolibro += line[i];	
							i++;
						}
						i++;
						titulo(bookStore, books, import, titulolibro);		//Llamamos al módulo del título
						
						while(line[i] != ',' && i<line.length()  && import){
							i++;
						}
						i++;
						while(line[i] != '"' && i<line.length()  && import){
							i++;
						}
						i++;
						while(i<line.length() && line[i] != '"' && import){
							autor += line[i];
							i++;
						}
						i++;
						authors(bookStore, books, import, autor);			//Lamamos al módulo del autor
						
						while(line[i] != ',' && i<line.length() && import){
							i++;
						}
						i++;
						
						while(line[i] != ',' && i<line.length()  && import){
							fecha += line[i];
							i++;
						}
						i++;
						anos(bookStore, books, import, fecha);

						while(line[i] != '"' && i<line.length() && import){
							i++;
						}
						i++;
						while(line[i] != '"' && i<line.length() && import){
							slug += line[i];
							i++;
						}
						i++;
						books.slug = slug;
						
						while(line[i] != ',' && i<line.length() && import){
							i++;
						}
						i++;
						while(i<line.length()){
							price += line[i];
							i++;
						}
						precio(bookStore, books, import, price);
						books.id = bookStore.nextId;
						bookStore.nextId++;
						
						bookStore.books.push_back(books);
					}
						fl.close();
				}	
			
				else{
				error(ERR_FILE);
				}
}

//Submenú para importar/Exportar datos en el programa
void importExportMenu(BookStore &bookStore, string data, string bindata, bool &unocheck, bool &doscheck) {
	bool fail;
	char option;
	
	do{
		cout<<"[Import/export options]"<<endl
		<<"1- Import from CSV"<<endl
		<<"2- Export to CSV"<<endl
		<<"3- Load data"<<endl
		<<"4- Save data"<<endl
		<<"b- Back to main menu"<<endl
		<<"Option: ";
		cin >> option;
		cin.get();
		switch (option) {
		  case '1':
			importFromCsv(bookStore, data, unocheck);
			fail = true;
			break;
		  case '2':
			exportToCsv(bookStore);
			fail = true;
			break;
		  case '3':
			loadData(bookStore, bindata, doscheck);
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


//Módulo principal
int main(int argc, char *argv[]) {

  BookStore bookStore;
  bookStore.name = "My Book Store";
  bookStore.nextId = 1;
  int i = 0;
  Book libros;
  char option;
  string bindata, data;
  bool unocheck, doscheck;
  unocheck= false;
  doscheck = false;
  bool argumenterror = false;

    if(argc > 5) { 
		error(ERR_ARGS);
	}
	else{
	
		for(i = 1; i<argc; i++){
			
			if(strcmp(argv[i],"-i") == 0 && doscheck == false){
				
				
				if(argc > i+1){
					data = argv[i+1];
					importFromCsv(bookStore, data, doscheck);
					//Si falla el import acaba
				}
				else{
					error(ERR_ARGS);
					argumenterror = true;
				}
				
			}
		}
			for(i = 1; i<argc; i++){
				if(strcmp(argv[i],"-l") == 0 && unocheck == false){
				
				if(argc > i+1){
					bindata = argv[i+1];
					loadData(bookStore, bindata, unocheck);
					//Si falla el load acaba
				}
				else{
					error(ERR_ARGS);
					argumenterror = true;
				}
			}
		}
	}
	
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
  return 0;
}
```
