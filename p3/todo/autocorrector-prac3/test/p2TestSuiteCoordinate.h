#include <cxxtest/TestSuite.h>

#include <iostream>
using namespace std;

#include "Coordinate.h"
#include "Util.h"

#include "Auxiliar.h"

#include <iostream>


using namespace std;


class TestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

 public:

  // Tests for Coordinate ----------------------------------------------------
  //  (mismos tests que en el autocorrector)
  void testCoordinate() {
  
    // constructor por defecto, pone a [-1,-1]
    Coordinate c; 
    TS_ASSERT_EQUALS(c.getRow(),-1);
    TS_ASSERT_EQUALS(c.getColumn(),-1);
    
    // constructor con valores, pone a [-7,767]
    Coordinate cc(-7,767);
    TS_ASSERT_EQUALS(cc.getRow(),-7);
    TS_ASSERT_EQUALS(cc.getColumn(),767);

    // setters y compare
    c.setRow(-7);
    TS_ASSERT_EQUALS(c.compare(cc), false);
    c.setColumn(767);
    TS_ASSERT_EQUALS(c.compare(cc), true);
    
    // operator<<
    stringstream ss;
    ss << c;
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("[-7,767]"));
  }
};

