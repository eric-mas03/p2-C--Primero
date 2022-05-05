/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "autocorrector-prac3/test/p2TestSuiteMapAC.h"

static TestSuiteAC suite_TestSuiteAC;

static CxxTest::List Tests_TestSuiteAC = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestSuiteAC( "autocorrector-prac3/test/p2TestSuiteMapAC.h", 55, "TestSuiteAC", suite_TestSuiteAC, Tests_TestSuiteAC );

static class TestDescription_TestSuiteAC_testMap : public CxxTest::RealTestDescription {
public:
 TestDescription_TestSuiteAC_testMap() : CxxTest::RealTestDescription( Tests_TestSuiteAC, suiteDescription_TestSuiteAC, 60, "testMap" ) {}
 void runTest() { suite_TestSuiteAC.testMap(); }
} testDescription_TestSuiteAC_testMap;

#include <cxxtest/Root.cpp>
