#include "catch.hpp"
#include "kw/kwValInteger.h"
#include "string.h"
#include <sstream>

using namespace std;

TEST_CASE( "kwValInteger Method tests - should behave the same like string", "[kwValString]" ) {

  int i = 1;
  kwValInteger val1 = -1000;
  kwValInteger val2 = -1;
  kwValInteger val3 = 1;
  kwValInteger val4 = 1000;

  SECTION("Constructor") {
    kwValInteger val;
    REQUIRE(val.getValue() == 0);
  }

  SECTION( "O Stream") {
    std::ostringstream os;
    os << val1;
    string fromOS = os.str();
    REQUIRE(fromOS == string("-1000"));
  }

  SECTION("Comparisons") {
    REQUIRE( (val1 > val2) == false);
    REQUIRE( (val1 < val2) == true);
    kwValInteger clone = val1;
    REQUIRE( (clone >= val1) == true);
    REQUIRE( (clone <= val1) == true);
    REQUIRE( (val1 >= val2) == false);
    REQUIRE( (val1 <= val2) == true);
  }
}
