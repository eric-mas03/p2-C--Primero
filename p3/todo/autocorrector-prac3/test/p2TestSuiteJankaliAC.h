#include <cxxtest/TestSuite.h>

#include <iostream>
using namespace std;

#include "Coordinate.h"
#include "Junk.h"
#include "Map.h"
#include "Betonski.h"
#include "Jankali.h"
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

class BetonskiCo: public Betonski {  // subclass for accessing Betonsi's protected attributes

  public:
  
     BetonskiCo(string name):Betonski(name) { }
     
     vector<Junk> gtBag()   const { return bag; }
     
     void setAnger(int anger)        { this->anger = anger; }  // cabrear artificialmente al Betonski
     void setCaptured(bool captured) { this->captured = captured; }  // capturar/liberar artificialmente al Betonski
     void addJunk(const Junk &junk)  { bag.push_back(junk); }  // añadir artificialmente 'junk' a la bolsa
     void clearBag()                 { bag.clear(); }          // borrar la bolsa
};


class JankaliCo: public Jankali {  // subclass for accessing Jankali's protected attributes

  public:
  
    JankaliCo(string name):Jankali(name) { }

    vector<Betonski *> gtSubdued()  { return subdued; }
    vector<Coordinate> gtTraps()    { return traps; }
    void stPower(int power)         { this->power = power; }
    
    void stTrap(const Coordinate &coord) { traps.push_back(coord); }  // añadir trampa sin coste

};

class TestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

 public:

  // Tests for Jankaki -------------------------------------------------------
  void testJankali() {

    JankaliCo jan("Darth Vader");
    
    TS_ASSERT_EQUALS(jan.getName(),"Darth Vader");
    TS_ASSERT_EQUALS(jan.getPower(),300);
    TS_ASSERT_EQUALS(jan.gtSubdued().size(),0);
    TS_ASSERT_EQUALS(jan.gtTraps().size(),0);
    
    // check EXCEPTION_NAME
    TS_ASSERT_THROWS_ASSERT(new Jankali(""), const Exception &e, TS_ASSERT_EQUALS(e, EXCEPTION_NAME));
    
    
    // añadir artificialmente trampas
    Coordinate c11(1,1), c33(3,3), c53(5,3);
    jan.stTrap(c11);
    jan.stTrap(c33);
    TS_ASSERT_EQUALS(jan.gtTraps().size(),2);
    
    // crear Betonskis para que los cace el Jankali, ponerles Junks, y ponerlos en las trampas
    vector<Betonski *> betonskis;
    
    BetonskiCo *pBetOne = new BetonskiCo("BetOne");
    BetonskiCo *pBetTwo = new BetonskiCo("BetTwo");
    BetonskiCo *pBetThree = new BetonskiCo("BetThree");
    BetonskiCo *pBetFour = new BetonskiCo("BetFour");
    
    betonskis.push_back(pBetOne);
    betonskis.push_back(pBetTwo);
    betonskis.push_back(pBetFour);
    betonskis.push_back(pBetThree);
    
    pBetFour->setCaptured(true);  // marcar como capturado, para que no lo capture 
    
    JunkCo jcg(GOLD,1), jcm(METAL,1), jcf(FOOD,1), jcs(STONE,1);
    
    pBetOne->addJunk(jcg);
    pBetOne->addJunk(jcm);
    pBetOne->addJunk(jcg);
    pBetOne->addJunk(jcg);
    
    pBetTwo->addJunk(jcm);
    pBetTwo->addJunk(jcm);
    pBetTwo->addJunk(jcf);
    pBetTwo->addJunk(jcm);

    pBetThree->addJunk(jcf);
    pBetThree->addJunk(jcf);
    pBetThree->addJunk(jcf);
    pBetThree->addJunk(jcs);
    
    pBetOne->setPosition(c11);
    pBetTwo->setPosition(c33);
    pBetThree->setPosition(c33);
    pBetFour->setPosition(c11);
    
    // hunt
    jan.hunt(betonskis);
    TS_ASSERT_EQUALS(jan.gtSubdued().size(),3);   // no debe capturar a pBetFour
    TS_ASSERT_EQUALS(jan.gtSubdued()[0]->getName(),pBetOne->getName());
    TS_ASSERT_EQUALS(jan.gtSubdued()[1]->getName(),pBetTwo->getName());
    TS_ASSERT_EQUALS(jan.gtSubdued()[2]->getName(),pBetThree->getName());
    
    TS_ASSERT_EQUALS(pBetOne->isCaptured(),true);    
    TS_ASSERT_EQUALS(pBetTwo->isCaptured(),true);    
    TS_ASSERT_EQUALS(pBetThree->isCaptured(),true);    

    // operator<<
    stringstream ss;
    ss << jan;
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Jankali \"Darth Vader\" 300\nBetonski \"BetOne\" Captured 0 [1,1]\n[GOLD:1][METAL:1][GOLD:1][GOLD:1]\nBetonski \"BetTwo\" Captured 0 [3,3]\n[METAL:1][METAL:1][FOOD:1][METAL:1]\nBetonski \"BetThree\" Captured 0 [3,3]\n[FOOD:1][FOOD:1][FOOD:1][STONE:1]\nTraps [1,1][3,3]\n"));

    
    // setTrap
    TS_ASSERT_EQUALS(jan.setTrap(c53),true);  // coste = (5+2)*(3+2) = 7*5 = 35
    TS_ASSERT_EQUALS(jan.getPower(),265);
    

    // spoil(pos)
    jan.spoil(2);  // spoil a BetThree (3 FOOD + 1 STONE = 170)
    TS_ASSERT_EQUALS(pBetThree->gtBag().size(),0);
    TS_ASSERT_EQUALS(pBetThree->getAnger(),170);
    TS_ASSERT_EQUALS(jan.getPower(),435);
    
    
    // añadimos junks a BetThree
    pBetThree->addJunk(jcg);
    pBetThree->addJunk(jcm);
    pBetThree->addJunk(jcf);
    pBetThree->addJunk(jcs);
    
    // spoil(METAL)   (1 + 3 + 1 = 500)
    jan.spoil(METAL);
    TS_ASSERT_EQUALS(jan.getPower(),935);
    TS_ASSERT_EQUALS(pBetOne->getAnger(),100);
    TS_ASSERT_EQUALS(pBetOne->gtBag().size(),3);
    TS_ASSERT_EQUALS(pBetTwo->getAnger(),300);
    TS_ASSERT_EQUALS(pBetTwo->gtBag().size(),1);
    TS_ASSERT_EQUALS(pBetThree->getAnger(),270);
    TS_ASSERT_EQUALS(pBetThree->gtBag().size(),3);
    
    // spoil + rebelión de BetThree
    pBetThree->setAnger(4999);   // 'cabreamos' a BetThree para que se rebele
    jan.spoil();  // BetOne 3g = 1500, BetTwo 1f = 50 , BetThree se rebela
    TS_ASSERT_EQUALS(jan.gtSubdued().size(),2);   // solo quedan 2
    TS_ASSERT_EQUALS(jan.getPower(),2485);  // 935 + 1550
    TS_ASSERT_EQUALS(pBetOne->getAnger(),1600);
    TS_ASSERT_EQUALS(pBetOne->gtBag().size(),0);
    TS_ASSERT_EQUALS(pBetTwo->getAnger(),350);
    TS_ASSERT_EQUALS(pBetTwo->gtBag().size(),0);
    TS_ASSERT_EQUALS(pBetThree->isCaptured(),false);
    TS_ASSERT_EQUALS(pBetThree->getAnger(),0);
    TS_ASSERT_EQUALS(pBetThree->gtBag().size(),3);
  }
};

