#include <cxxtest/TestSuite.h>

#include <iostream>
using namespace std;

#include "Coordinate.h"
#include "Junk.h"
#include "Map.h"
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


class MapCo: public Map {  // subclass for accessing Map's protected attributes

  public:
  
     MapCo(int rows,int columns):Map(rows,columns) { }
     
     int gtRows()    const { return rows; }
     int gtColumns() const { return columns; }
     vector<vector<Junk>> gtJunks() const { return junks; }
};


class TestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

 public:

  // Tests for Map -----------------------------------------------------------
  void testMap() {
  
    // constructor con valores mínimos
    MapCo m5x5(5,5);
    
    TS_ASSERT_EQUALS(m5x5.gtRows(),5);
    TS_ASSERT_EQUALS(m5x5.gtColumns(),5);

    // comprobar que se crea la matriz   
    for (unsigned i=0;i<5;i++)
      for (unsigned j=0;j<5;j++)
      {
        Junk junk = m5x5.gtJunks()[i][j];
        TS_ASSERT_EQUALS(junk.getType(),WASTELAND);
        TS_ASSERT_EQUALS(junk.getQuantity(),0);
      }
    
    // check EXCEPTION_SIZE exception
    TS_ASSERT_THROWS_ASSERT(new Map(4,5), const Exception &e, TS_ASSERT_EQUALS(e, EXCEPTION_SIZE));

    // isInside
    Coordinate c(3,4),cc;
    TS_ASSERT_EQUALS(m5x5.isInside(c),true);
    TS_ASSERT_EQUALS(m5x5.isInside(cc),false); // cc is [-1,-1]
    
    // putJunk / getJunk
    Junk jgold(GOLD,10);
    m5x5.putJunk(jgold,c);
    TS_ASSERT_EQUALS(m5x5.gtJunks()[3][4].getType(),GOLD);
    TS_ASSERT_EQUALS(m5x5.gtJunks()[3][4].getQuantity(),10);
    
    Junk jgg = m5x5.getJunk(c);
    TS_ASSERT_EQUALS(jgold.getType(),jgg.getType());
    TS_ASSERT_EQUALS(jgold.getQuantity(),jgg.getQuantity());

    // check EXCEPTION_OUTSIDE    
    TS_ASSERT_THROWS_ASSERT(m5x5.putJunk(jgold,cc), const Exception &e, TS_ASSERT_EQUALS(e, EXCEPTION_OUTSIDE));
    TS_ASSERT_THROWS_ASSERT(m5x5.getJunk(cc), const Exception &e, TS_ASSERT_EQUALS(e, EXCEPTION_OUTSIDE));
    TS_ASSERT_THROWS_ASSERT(m5x5.collectJunk(cc), const Exception &e, TS_ASSERT_EQUALS(e, EXCEPTION_OUTSIDE));
    
    // collectJunk
    Junk jgc = m5x5.collectJunk(c);
    TS_ASSERT_EQUALS(jgold.getType(),jgc.getType());
    TS_ASSERT_EQUALS(jgold.getQuantity(),jgc.getQuantity());
 
    TS_ASSERT_EQUALS(m5x5.gtJunks()[3][4].getType(),WASTELAND);
    TS_ASSERT_EQUALS(m5x5.gtJunks()[3][4].getQuantity(),0);

    // operator<<
    Junk jmetal(METAL,15),jfood(FOOD,20),jstone(STONE,25);
    Coordinate c11(1,1),c23(2,3),c34(3,4),c41(4,1);
    m5x5.putJunk(jgold,c11);
    m5x5.putJunk(jmetal,c23);
    m5x5.putJunk(jfood,c34);
    m5x5.putJunk(jstone,c41);
        
    stringstream ss;
    ss << m5x5;
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("00010203040001G02M03F04S"));  // rmb()  quita todos los blancos y \n
    /*
       00 01 02 03 04
    00               
    01    G          
    02          M    
    03             F 
    04    S          
    */
  }
  
  
};

