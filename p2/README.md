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

void showCatalog(const BookStore &bookStore, Book & libros, int &pos) {
	unsigned int i;

	
	for(i = 0; i<bookStore.books.size(); i++){
		int ident = i+1;
		cout << ident << ". " << bookStore.books[i].title << ", " << bookStore.books[i].authors <<
		" (" << bookStore.books[i].year << "), " << bookStore.books[i].price <<endl; 
	}
	
}


void addBook(BookStore &bookStore, int &pos) {
	Book libros;
	int longitud, i;
	bool fail;
	string s;
	longitud = 0;
	string yearstr, pricestr;
	
	
	do{ //Falla con los caracteres especiales
		fail = false;
		cout << "Enter book tittle: ";
		getline(cin,libros.title);
		longitud = libros.title.length();
    if(libros.title.empty()){
      fail = true;
      error(ERR_BOOK_TITLE);
    }
    if(!fail){
      for(i = 0; i < longitud; i++){
      
         
          if(isalnum(libros.title[i]) == 8 || isblank(libros.title[i]) == 1){
            fail = false;
            }
          else if (libros.title[i] == ';' || libros.title[i] == ':' || libros.title[i] == '-' ){
            fail = false;
            }
          else{
            fail = true;
            error(ERR_BOOK_TITLE);
          }
			
		}
  }  
	}while(fail == true);
	
	
	do{
		fail = false;
		cout << "Enter author(s): ";
		getline(cin,libros.authors);
		longitud = libros.authors.length();
    if(libros.authors.empty()){
      fail = true;
      error(ERR_BOOK_AUTHORS);
    }
    if(!fail){
      for(i = 0; i < longitud; i++){
        if(!fail){
          if(isalpha(libros.authors[i]) != 0 || isblank(libros.authors[i]) != 0){
            fail = false;
            }
         else if (libros.authors[i] != ';' && libros.authors[i] != ':' && libros.authors[i] != '-' ){
            fail = true;
            error(ERR_BOOK_TITLE);
            }
			}
		}
    }
	}while(fail == true);	
	
	
	do{
		fail = false;
		cout << "Enter publication year: ";
		getline(cin, yearstr);
		if(yearstr.length() > 0){
			libros.year = stoi(yearstr);
			
			if(libros.year < 1945 || libros.year > 2022){
				fail = true;
				error(ERR_BOOK_DATE);
				}
		}
		else{
			error(ERR_BOOK_DATE);
			fail = true;
			}

			
		
	}while(fail == true);
	
	do{
		fail = false;
		cout << "Enter price: ";
		getline(cin,pricestr);

		if(pricestr.length() > 0){
			libros.price = stof(pricestr);

			if(libros.price < 0){
				fail = true;
				error(ERR_BOOK_PRICE);
				}
    }
    else{
        error(ERR_BOOK_PRICE);
        fail = true;
    }
		
	}while(fail == true);
		
 for(i = 0 ; i < longitud; i++){
   if(isalpha(libros.title[i])){
      libros.slug += tolower(libros.title[i]);
   }
    if(isblank(libros.title[i]) != 0 || libros.title[i] == ';' || libros.title[i] == ':' || libros.title[i] == '-' ){
      libros.slug[i] = '-';
    }
    else{
      libros.slug += libros.title[i];
    } 
 }
 
libros.id =  bookStore.nextId;
bookStore.nextId++;
 
bookStore.books.push_back(libros);


}

/*
void showExtendedCatalog(const BookStore &bookStore) {
}


*/
void deleteBook(BookStore &bookStore) { //No funciona el dete BOOK MIralo ---------------------
  int unsigned deleteid;
  int unsigned longitud, i;
  bool encontrado = false;
  longitud = bookStore.books.size();
  i = 0;
  cout << "Enter book id: ";
  cin >> deleteid;
  
      for(i = 0; i < longitud && !encontrado; i++){
		  if(bookStore.books[i].id == deleteid){
		   bookStore.books.erase(bookStore.books.begin()+deleteid);
		   encontrado = true;
		  }
	  }
  
	  if(encontrado == false){
		 error(ERR_ID);
	  }
}


void importFromCsv(BookStore &bookStore){
		string filename, t, authors;
		int unsigned i;
		Book books;
		string line;
		
		
		
		cout << "Enter filename: ";
		getline(cin, filename);
		
		
		ifstream f1(filename);
			if(f1.is_open()){
				
				while(getline(f1,line)){
					i = 0;
					string titulo, autor, fecha, slug, price;
					while(i<line.length() && line[i] != '"'){
						i++;
					}
					i++;
					
					while(line[i] != '"' && i<line.length() ){
						titulo += line[i];		//Leemos titulo
						i++;
					}
					i++;
					books.title = titulo;		//Agregamos el titulo
					
					while(line[i] != ',' && i<line.length() ){
						i++;
					}
					i++;
					while(line[i] != '"' && i<line.length() ){
						i++;
					}
					i++;
					while(i<line.length() && line[i] != '"'){
						autor += line[i];		//Leemos autor
						i++;
					}
					i++;
					books.authors = autor;
					
					while(line[i] != ',' && i<line.length() ){
						i++;
					}
					i++;
					
					while(line[i] != ',' && i<line.length() ){
						fecha += line[i];
						i++;
					}
					i++;
					
					if(fecha.length() > 0){
						books.year = stoi(fecha);
					}
					while(line[i] != '"' && i<line.length()){
						i++;
					}
					i++;
					while(line[i] != '"' && i<line.length()){
						slug += line[i];
						i++;
					}
					i++;
					books.slug = slug;
					
					while(line[i] != ',' && i<line.length() ){
						i++;
					}
					i++;
					while(i<line.length()){
						price += line[i];
						i++;
					}
					if(price.length() > 0){
						books.price = stof(price);
					}
					
					bookStore.books.push_back(books);
				}
					f1.close();
				
			}
			
				else{
				error(ERR_FILE);
				}
}
	
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
					fe << '"' << bookStore.books[i].title << '"' 
					   << ',' << '"'
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



void importExportMenu(BookStore &bookStore) {
	bool fail;
	char option;
	
	do{
		cout<<"[Import/export options]"<<endl
		<<"1- Import from CSV"<<endl
		<<"2- Export from CSV"<<endl
		<<"3- Load data"<<endl
		<<"4- Save data"<<endl
		<<"b- Back to main menu"<<endl
		<<"Option: ";
		cin >> option;
		cin.get();
		switch (option) {
		  case '1':
			importFromCsv(bookStore);
			fail = true;
			break;
		  case '2':
			exportToCsv(bookStore);
			fail = true;
			break;
		  case '3':
			//Load
			fail = true;
			break;
		  case '4':
			//Save
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


/*
void loadData(BookStore &bookStore){
}

void saveData(const BookStore &bookStore){
}
*/


int main(int argc, char *argv[]) {
  BookStore bookStore;
  bookStore.name = "My Book Store";
  bookStore.nextId = 1;
  Book libros;
  int i = 0;
  
  char option;
  do {
    showMainMenu();
    cin >> option;
    cin.get();

    switch (option) {
      case '1':
        showCatalog(bookStore, libros, i);
        break;
      case '2':
        //showExtendedCatalog(bookStore);
        break;
      case '3':
        addBook(bookStore, i);
        break;
      case '4':
        deleteBook(bookStore);
        break;
      case '5':
        importExportMenu(bookStore);
        break;
      case 'q':
        break;
      default:
        error(ERR_OPTION);
    }
  } while (option != 'q');

  return 0;
}

```