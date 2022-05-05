#include <cxxtest/TestSuite.h>

#include <iostream>
using namespace std;

#include "Coordinate.h"
#include "Junk.h"
#include "Util.h"

#include "Auxiliar.h"

#include <iostream>


using namespace std;


class JunkCo: public Junk {  // subclass for accessing Junk's protected attributes

  public:

    JunkCo():Junk() { }  
    JunkCo(JunkType type,int quantity):Junk(type,quantity)  { }
    
    JunkType gtType() const  { return type; }
    // si da error en este método en 'type' puede ser por dos razones:
    //   - no has puesto "protected" en vez de "private"
    //   - no has llamado 'type' a ese atributo. 
    //     IMPORTANTE: los atributos deben llamarse como aparecen en el diagrama
    
    int gtQuantity() const  { return quantity; }
    void stQuantity(int qty) { quantity = qty; } // cambiar quantity para las pruebas
    
  friend ostream& operator<< (ostream& os,const JunkCo &junk)
  {
    Junk j=junk;
    return os << j;
  }
};

class TestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

 public:

  // Tests for Junk ----------------------------------------------------------
  void testJunk() {

    // Constructor por defecto, pone a [WASTELAND:0]
    JunkCo junkDef;
    
    TS_ASSERT_EQUALS(junkDef.gtType(),WASTELAND);
    TS_ASSERT_EQUALS(junkDef.gtQuantity(),0);

    // Constructor con parámetros
    JunkCo junkPar(STONE,6);
    
    TS_ASSERT_EQUALS(junkPar.gtType(),STONE);
    TS_ASSERT_EQUALS(junkPar.gtQuantity(),6);
    
    // check EXCEPTION_QUANTITY exception
    TS_ASSERT_THROWS_ASSERT(new Junk(GOLD,-1), const Exception &e, TS_ASSERT_EQUALS(e, EXCEPTION_QUANTITY));

        
    // getTypeChar
    TS_ASSERT_EQUALS(junkDef.getTypeChar(),'W');
    TS_ASSERT_EQUALS(junkPar.getTypeChar(),'S');

    // getValue
    TS_ASSERT_EQUALS(junkPar.getValue(), 120);  // 6 * 20 = 120

    // operator<<
    stringstream ss;
    ss << junkPar;
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("[STONE:6]"));
    
  }
};

