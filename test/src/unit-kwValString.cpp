#include "catch.hpp"
#include "kw/kwValString.h"
#include "string.h"

using namespace std;

TEST_CASE( "kwValString Method tests - should behave the same like string", "[kwValString]" ) {

  kwValString string_A = kwValString("TestA");
  kwValString string_B = kwValString("TestB");

  string str_string_A = string("TestA");
  string str_string_B = string("TestB");

  REQUIRE( str_string_A == string_A.str());
  REQUIRE( str_string_B == string_B.str());

  char* nonConstCStr = "NonConstcstr";
  string nonConstStr = string("NonConstcstr");

  SECTION( "Calling base constructor will cause empty true" ) {
    REQUIRE( string_A.empty() == false);
    kwValString emptyString = kwValString();
    REQUIRE( emptyString.empty() == true);
  }

  SECTION( "Non const C String construtors" ) {
    kwValString nonConstkwStr = kwValString(nonConstCStr);
    REQUIRE( nonConstkwStr.str() == nonConstStr);
    REQUIRE( nonConstkwStr.empty() == false);
  }

  SECTION( "Copy constructor" ) {
    kwValString copy = string_A;
    REQUIRE( str_string_A == copy.str());
  }

  SECTION( "Operator+" ) {
    kwValString added = string_A + string_B;
    string str_add = str_string_A + str_string_B;
    REQUIRE( str_add == added.str());
  }
}
