#include "catch.hpp"
#include "kw/kwValFloat.h"
#include "kw/kwValString.h"
#include "string.h"
#include <sstream>
#include <memory>
#include <limits>

using namespace std;

TEST_CASE( "kwValFloat Method tests - should behave the same like float", "[kwValFloat]" ) {

    float fl = 1.5;
    kwValFloat val1 = -1000.5f;
    kwValFloat val2 = -1.5f;
    kwValFloat val3 = 1.5f;
    kwValFloat val4 = 1000.2f;

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

    SECTION("asString") {
        // This only tests the standard behaviour, to create custom
        // formatting you need to use stringstream instead.
        REQUIRE( kwValString("-1.500000") == val2.asString());
        REQUIRE( kwValString("1.500000") == val3.asString());
    }

    SECTION("Calculations") {
        kwValFloat sum1 = val1 + val2;
        REQUIRE( sum1 == kwValFloat(-1002));

        kwValFloat sum2 = val1 + val4;
        REQUIRE( sum2.getValue() == Approx(-0.3f).epsilon(0.0001));

        // shortened calculations
        kwValFloat res3 = kwValFloat(500.5);
        res3 += val1;
        REQUIRE( res3 == kwValFloat(-500));

        kwValFloat difference1 = res3 - val4;
        REQUIRE( difference1 == kwValFloat(-1500.2));

        kwValFloat difference2 = kwValFloat(1000);
        kwValFloat subtrahend = kwValFloat(1000);
        difference2 -= subtrahend;
        REQUIRE(difference2  == kwValFloat(0));

        kwValFloat factor1 = kwValFloat(10.1);
        kwValFloat factor2 = kwValFloat(6);
        kwValFloat product = factor1 * factor2;
        REQUIRE(product.getValue()  == Approx(kwValFloat(60.6).getValue()));

        kwValFloat divident = kwValFloat(10.2);
        kwValFloat divisor = kwValFloat(2);
        kwValFloat quotient = divident / divisor;
        REQUIRE(quotient  == kwValFloat(5.1));
    }

    SECTION("Pointer type destructor branch") {
        kwValFloat* rawptr = new kwValFloat(0.5);
        kwValFloat rawptrres = kwValFloat(0.3) + *rawptr;
        delete rawptr;
        REQUIRE(rawptrres.getValue() == Approx(0.8));
    }

    SECTION("json serialization") {
        json expected = { {"float", -1000.5}};
        json generated;
        generated["float"] = val1.toJson();
        REQUIRE(expected == generated);
    }
}
