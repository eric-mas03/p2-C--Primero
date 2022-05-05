#include <cxxtest/TestSuite.h>

#include <iostream>
using namespace std;

#include "Coordinate.h"
#include "Junk.h"
#include "Map.h"
#include "Betonski.h"
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

class BetonskiCo: public Betonski {  // subclass for accessing Betonski's protected attributes

  public:
  
     BetonskiCo(string name):Betonski(name) { }
     
     vector<Junk> gtBag()   const { return bag; }
     
     void setAnger(int anger)        { this->anger = anger; }  // cabrear artificialmente al Betonski
     void setCaptured(bool captured) { this->captured = captured; }  // capturar/liberar artificialmente al Betonski
     void addJunk(const Junk &junk)  { bag.push_back(junk); }  // añadir artificialmente 'junk' a la bolsa
     void clearBag()                 { bag.clear(); }          // borrar la bolsa
};


class TestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

 public:

  // Tests for Betonski ------------------------------------------------------
  void testBetonski() {

    Junk jmetal(METAL,5);
    Coordinate c12(1,2);
    Coordinate c23(2,3);
    Coordinate c00(0,0);  ///co
    MapCo map(6,12);
    

    // constructor
    BetonskiCo beti("Tiste Foo");
    
    TS_ASSERT_EQUALS(beti.getName(),"Tiste Foo");
    TS_ASSERT_EQUALS(beti.gtBag().size(),0);
    TS_ASSERT_EQUALS(beti.getAnger(),0);
    TS_ASSERT_EQUALS(beti.isCaptured(),false);
    TS_ASSERT_EQUALS(beti.getPosition().getRow(),-1);
    TS_ASSERT_EQUALS(beti.getPosition().getColumn(),-1);
    
    // check EXCEPTION_NAME
    TS_ASSERT_THROWS_ASSERT(new Betonski(""), const Exception &e, TS_ASSERT_EQUALS(e, EXCEPTION_NAME));

    // check EXCEPTION_OUTSIDE  (position is [-1,-1])
    TS_ASSERT_THROWS_ASSERT(beti.move(map), const Exception &e, TS_ASSERT_EQUALS(e, EXCEPTION_OUTSIDE));

    // captured
    beti.capture();
    TS_ASSERT_EQUALS(beti.isCaptured(),true);
    
    // setPosition
    beti.setPosition(c23);
    TS_ASSERT_EQUALS(beti.getPosition().getRow(),2);
    TS_ASSERT_EQUALS(beti.getPosition().getColumn(),3);
    
    // move
    TS_ASSERT_EQUALS(beti.move(map),true);     // dirección = 7  [2,3] --> [1,2]
    TS_ASSERT_EQUALS(beti.getPosition().getRow(),1);
    TS_ASSERT_EQUALS(beti.getPosition().getColumn(),2);
    
    // extract
    beti.setPosition(c12);  // por si acaso
    map.putJunk(jmetal,c12);
    TS_ASSERT_EQUALS(beti.extract(map),500);
    TS_ASSERT_EQUALS(beti.gtBag().size(),1);
    TS_ASSERT_EQUALS(beti.gtBag()[0].getType(),METAL);
    TS_ASSERT_EQUALS(beti.gtBag()[0].getQuantity(),5);
    TS_ASSERT_EQUALS(map.gtJunks()[1][2].getType(),WASTELAND);
    TS_ASSERT_EQUALS(map.gtJunks()[1][2].getQuantity(),0);
    
    // llenar la bolsa (artificialmente, sin usar el mapa)
    JunkCo jcg(GOLD,5), jcm(METAL,6), jcf(FOOD,7), jcs(STONE,8);
    
    beti.addJunk(jcg);
    beti.addJunk(jcm);
    beti.addJunk(jcf);
    beti.addJunk(jcs);
    jcg.stQuantity(10);
    jcm.stQuantity(11);
    jcf.stQuantity(12);
    jcs.stQuantity(13);
    beti.addJunk(jcs);
    beti.addJunk(jcf);
    beti.addJunk(jcm);
    beti.addJunk(jcg);
 
    // operator<<   
    stringstream ss;
    ss << beti;
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Betonski \"TisteFoo\" Captured 0 [1,2]\n[METAL:5][GOLD:5][METAL:6][FOOD:7][STONE:8][STONE:13][FOOD:12][METAL:11][GOLD:10]\n"));
    
    // calculateValue
    TS_ASSERT_EQUALS(beti.calculateValue(),11070);
    TS_ASSERT_EQUALS(beti.calculateValue(GOLD),7500);
    TS_ASSERT_EQUALS(beti.calculateValue(METAL),2200);
    TS_ASSERT_EQUALS(beti.calculateValue(FOOD),950);
    TS_ASSERT_EQUALS(beti.calculateValue(STONE),420);
    
    // spoliation
    beti.setCaptured(false);
    TS_ASSERT_THROWS_ASSERT(beti.spoliation(), const InternalException &e, TS_ASSERT_EQUALS(e, BETONSKI_NOT_CAPTURED));
    
    beti.setCaptured(true);
    TS_ASSERT_EQUALS(beti.spoliation(FOOD),950);
    ss << beti;
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Betonski \"TisteFoo\" Captured 950 [1,2]\n[METAL:5][GOLD:5][METAL:6][STONE:8][STONE:13][METAL:11][GOLD:10]\n"));

    TS_ASSERT_THROWS_ASSERT(beti.spoliation(GOLD), const Exception &e, TS_ASSERT_EQUALS(e, EXCEPTION_REBELION));
    TS_ASSERT_EQUALS(beti.getAnger(),0);
    TS_ASSERT_EQUALS(beti.isCaptured(),false);
    TS_ASSERT_EQUALS(beti.gtBag().size(),7);
    TS_ASSERT_EQUALS(beti.gtBag()[0].getType(),METAL);
    TS_ASSERT_EQUALS(beti.gtBag()[0].getQuantity(),5);

    ss << beti;
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Betonski \"TisteFoo\" Free 0 [1,2]\n[METAL:5][GOLD:5][METAL:6][STONE:8][STONE:13][METAL:11][GOLD:10]\n"));
    
  }  
};

