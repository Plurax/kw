#include "catch.hpp"
#include "kw/kwValFloat.h"
#include "string.h"
#include <sstream>

using namespace std;

TEST_CASE( "kwValFloat Method tests - should behave the same like float", "[kwValFloat]" ) {

    float fl = 1.5;
    kwValFloat val1 = -1000.5;
    kwValFloat val2 = -1.5;
    kwValFloat val3 = 1.5;
    kwValFloat val4 = 1000.2;

    SECTION("Constructor") {
        kwValFloat val;
        REQUIRE(val.getValue() == 0.0);
        kwValFloat val2(2.2);
        val = 2.2;
        REQUIRE(val == val2);
    }

    SECTION( "O Stream") {
        std::ostringstream os;
        os << val1;
        string fromOS = os.str();
        REQUIRE(fromOS == string("-1000.5"));
    }

    SECTION("Comparisons") {
        REQUIRE( (val1 > val2) == false);
        REQUIRE( (val1 < val2) == true);
        kwValFloat clone = val1;
        REQUIRE( (clone >= val1) == true);
        REQUIRE( (clone <= val1) == true);
        REQUIRE( (val1 >= val2) == false);
        REQUIRE( (val1 <= val2) == true);
    }

    SECTION("Calculations") {
        kwValFloat res = val1 + val2;
        REQUIRE( res == kwValFloat(-1002));

        kwValFloat res2 = val1 + val4;
    }
}
