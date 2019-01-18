#include "catch.hpp"
#include <kw/kwValUnsignedInteger.h>
#include "string.h"
#include <sstream>
#include <memory>

using namespace std;

TEST_CASE( "kwValUnsignedInteger Method tests - should behave the same like string", "[kwValString]" ) {

    int i = 1;
    kwValUnsignedInteger val1 = 1;
    kwValUnsignedInteger val2 = 1000;

    SECTION("Constructor") {
        kwValUnsignedInteger val;
        REQUIRE(val.getValue() == 0);
    }

    SECTION( "O Stream") {
        std::ostringstream os;
        os << val2;
        string fromOS = os.str();
        REQUIRE(fromOS == string("1000"));
    }

    SECTION("Comparisons") {
        REQUIRE( (val1 > val2) == false);
        REQUIRE( (val1 < val2) == true);
        kwValUnsignedInteger clone = val1;
        REQUIRE( (clone >= val1) == true);
        REQUIRE( (clone <= val1) == true);
        REQUIRE( (val1 >= val2) == false);
        REQUIRE( (val1 <= val2) == true);
        REQUIRE( (val1 == clone) == true);
        REQUIRE( (val1 != val2) == true);
    }

    SECTION("Assignments") {
        int iVal = 50;
        kwValUnsignedInteger integerassign = iVal;
        REQUIRE(integerassign.getValue() == 50);
        integerassign = val2;
        REQUIRE( (integerassign == val2) == true);
    }

    SECTION("asString") {
        // This only tests the standard behaviour, to create custom
        // formatting you need to use stringstream instead.
        REQUIRE( kwValString("1") == val1.asString());
        REQUIRE( kwValString("1000") == val2.asString());
    }

    SECTION("Calculations") {
        // Assume the same behaviour like integers
        kwValUnsignedInteger sum = val1 + val2;
        REQUIRE(sum.getValue() == 1001);

        kwValUnsignedInteger sum2 = kwValUnsignedInteger(500);
        sum2 += val1;
        REQUIRE(sum2.getValue() == 501);

        kwValUnsignedInteger difference1 = val2 - val1;
        REQUIRE(difference1.getValue() == 999);

        kwValUnsignedInteger product = val1 * kwValUnsignedInteger(5);
        REQUIRE(product.getValue() == 5);

        kwValUnsignedInteger quotient = val2 / kwValUnsignedInteger(5);
        REQUIRE(quotient.getValue() == 200);
    }

    SECTION("Assignment") {
        std::shared_ptr<kwValUnsignedInteger> val5 = std::make_shared<kwValUnsignedInteger>(50);
        REQUIRE(val5->getValue() == 50);
        kwValUnsignedInteger val6 = 60;
        REQUIRE(val6.getValue() == 60);
    }

    SECTION("Pointer type destructor branch") {
        kwValUnsignedInteger* rawptr = new kwValUnsignedInteger(5);
        kwValUnsignedInteger rawptrres = kwValUnsignedInteger(3) + *rawptr;
        delete rawptr;
        REQUIRE(rawptrres.getValue() == 8);
    }

    SECTION("json serialization") {
        json expected = { {"uint", 1}};
        json generated;
        generated["int"] = val1.toJson();
        REQUIRE(expected == generated);
    }
}
