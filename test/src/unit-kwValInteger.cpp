#include "catch.hpp"
#include "kw/kwValInteger.h"
#include "string.h"
#include <sstream>
#include <memory>

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

    SECTION("Assignments") {
        kwValInteger integerassign = 50;
        REQUIRE(integerassign.getValue() == 50);
    }

    SECTION("asString") {
        // This only tests the standard behaviour, to create custom
        // formatting you need to use stringstream instead.
        REQUIRE( kwValString("-1000") == val1.asString());
        REQUIRE( kwValString("1000") == val4.asString());
    }

    SECTION("Calculations") {
        // Assume the same behaviour like integers
        kwValInteger sum = val1 + val4;
        REQUIRE(sum.getValue() == 0);

        kwValInteger sum2 = kwValInteger(500);
        sum2 += val1;
        REQUIRE(sum2.getValue() == -500);

        kwValInteger difference1 = val4 - val3;
        REQUIRE(difference1.getValue() == 999);

        kwValInteger difference2 = kwValInteger(500);
        difference2 -= val4;
        REQUIRE(difference2.getValue() == -500);

        kwValInteger product = val1 * kwValInteger(5);
        REQUIRE(product.getValue() == -5000);

        kwValInteger quotient = val4 / kwValInteger(5);
        REQUIRE(quotient.getValue() == 200);
    }

    SECTION("Assignment") {
        std::shared_ptr<kwValInteger> val5 = std::make_shared<kwValInteger>(50);
        REQUIRE(val5->getValue() == 50);
        kwValInteger val6 = 60;
        REQUIRE(val6.getValue() == 60);
    }

    SECTION("Pointer type destructor branch") {
        kwValInteger* rawptr = new kwValInteger(5);
        kwValInteger rawptrres = kwValInteger(3) + *rawptr;
        delete rawptr;
        REQUIRE(rawptrres.getValue() == 8);
    }

    SECTION("json serialization") {
        json expected = { {"int", -1000}};
        json generated;
        generated["int"] = val1.toJson();
        REQUIRE(expected == generated);
    }
}
