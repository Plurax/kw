#include "catch.hpp"
#include "kw/kwValString.h"
#include "string.h"

using namespace std;

TEST_CASE( "kwValString Method tests - should behave the same like string", "[kwValString]" ) {

  kwValString string_A = kwValString("TestA");
  kwValString string_B = kwValString("TestB");

  string str_string_A = string("TestA");
  string str_string_B = string("TestA");

  REQUIRE( str_string_A == string_A.str());

  // SECTION( "resizing bigger changes size and capacity" ) {
  // }
  // SECTION( "resizing smaller changes size but not capacity" ) {
  // }
  // SECTION( "reserving bigger changes capacity but not size" ) {
  // }
  // SECTION( "reserving smaller does not change size or capacity" ) {
  // }
}
