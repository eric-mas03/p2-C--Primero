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
		cout << ident << ". " << bookStore.books[i].title <<
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
		
 for(i = 0 ; i< libros.title.length(); i++){
   if(isalpha(libros.title[i])){
      libros.slug[i] = tolower(libros.title[i]);
   }
    if(isblank(libros.title[i]) != 0 || libros.title[i] == ';' || libros.title[i] == ':' || libros.title[i] == '-' ){
      libros.slug[i] = '-';
    }
    else{
      libros.slug[i] = libros.title[i];
    } 
 }
bookStore.books.push_back(libros);

}

/*
void showExtendedCatalog(const BookStore &bookStore) {
}


*/
void deleteBook(BookStore &bookStore) {
  string deleteid;
  int buscado, i;

  cout << "Enter book id: ";
  getline(cin, deleteid);
  if(deleteid.length() > 0){
    buscado = stoi(deleteid);
      for(i = 0; i<bookStore.books.size(); i++){
      if(bookStore.books[i].id == buscado){
       cout << "Falta borrar"<<endl;
      }
    }
  
  else{
     error(ERR_ID);
  }
  }
}

/*
void importExportMenu(BookStore &bookStore) {
}

void importFromCsv(BookStore &bookStore){
}

void exportToCsv(const BookStore &bookStore){
}

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
        deleteBook(bookStore, i);
        break;
      case '5':
        //importExportMenu(bookStore);
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
