/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "autocorrector-prac3/test/p2TestSuiteCoordinate.h"

static TestSuiteAC suite_TestSuiteAC;

static CxxTest::List Tests_TestSuiteAC = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestSuiteAC( "autocorrector-prac3/test/p2TestSuiteCoordinate.h", 17, "TestSuiteAC", suite_TestSuiteAC, Tests_TestSuiteAC );

static class TestDescription_TestSuiteAC_testCoordinate : public CxxTest::RealTestDescription {
public:
 TestDescription_TestSuiteAC_testCoordinate() : CxxTest::RealTestDescription( Tests_TestSuiteAC, suiteDescription_TestSuiteAC, 23, "testCoordinate" ) {}
 void runTest() { suite_TestSuiteAC.testCoordinate(); }
} testDescription_TestSuiteAC_testCoordinate;

#include <cxxtest/Root.cpp>
