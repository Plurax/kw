#include "catch.hpp"
#include "kw/kwValFixedPoint.h"
#include "string.h"
#include <sstream>
#include <memory>

using namespace std;

TEST_CASE( "kwValFixedPoint Method tests", "[kwValFixedPoint]" ) {

    int i = 1;
    kwValFixedPoint val_default = kwValFixedPoint("1234.56");
    kwValFixedPoint val13N4_1 = kwValFixedPoint("12.3456 prec13N4");
    kwValFixedPoint val13N4_2 = kwValFixedPoint("-12.3456 prec13N4");

    SECTION("Constructor") {
        kwValFixedPoint val;
        REQUIRE(val.getValue() == 0);
        REQUIRE(val.getPrecision() == enumValFixedPointPrec::prec13N4);

        auto precConst = kwValFixedPoint(12908, enumValFixedPointPrec::prec13N4);
    }

    SECTION( "O Stream") {
        std::ostringstream os;
        os << val_default;
        string fromOS = os.str();
        REQUIRE(fromOS == string("12.3456"));
    }

    SECTION("Comparisons") {
        REQUIRE( (val13N4_1 > val13N4_2) == true);
        REQUIRE( (val13N4_1 < val13N4_2) == false);
        kwValFixedPoint clone = val13N4_1;
        REQUIRE( (clone >= val13N4_1) == true);
        REQUIRE( (clone <= val13N4_1) == true);
        REQUIRE( (val13N4_1 >= val13N4_2) == true);
        REQUIRE( (val13N4_1 <= val13N4_2) == false);
        REQUIRE( (val13N4_1 == clone) == true);
        REQUIRE( (val13N4_1 != val13N4_2) == true);
    }

    SECTION("Assignments") {
        kwValFixedPoint assign = val13N4_2;
        REQUIRE( (assign == val13N4_2) == true);
    }

    SECTION("String creation") {
        // This only tests the standard behaviour, to create custom
        // formatting you need to use stringstream instead.
        REQUIRE( kwValString("12.3456") == val13N4_1.asString());
        REQUIRE( kwValString("-12.3456") == val13N4_2.asString());
    }

    SECTION("Calculations") {
        // Assume the same behaviour like integers
        // kwValFixedPoint sum = val13N4_1 + val4;
        // REQUIRE(sum.getValue() == 0);

        // kwValFixedPoint sum2 = kwValFixedPoint(500);
        // sum2 += val13N4_1;
        // REQUIRE(sum2.getValue() == -500);

        // kwValFixedPoint difference1 = val4 - val3;
        // REQUIRE(difference1.getValue() == 999);

        // kwValFixedPoint difference2 = kwValFixedPoint(500);
        // difference2 -= val4;
        // REQUIRE(difference2.getValue() == -500);

        // kwValFixedPoint product = val13N4_1 * kwValFixedPoint(5);
        // REQUIRE(product.getValue() == -5000);

        // kwValFixedPoint quotient = val4 / kwValFixedPoint(5);
        // REQUIRE(quotient.getValue() == 200);
    }

    SECTION("Assignment") {
        // std::shared_ptr<kwValFixedPoint> val5 = std::make_shared<kwValFixedPoint>(50);
        // REQUIRE(val5->getValue() == 50);
        // kwValFixedPoint val6 = 60;
        // REQUIRE(val6.getValue() == 60);
    }

    SECTION("Pointer type destructor branch") {
        // kwValFixedPoint* rawptr = new kwValFixedPoint(5);
        // kwValFixedPoint rawptrres = kwValFixedPoint(3) + *rawptr;
        // delete rawptr;
        // REQUIRE(rawptrres.getValue() == 8);
    }

    SECTION("json serialization") {
        // json expected = { {"int", -1000}};
        // json generated;
        // generated["int"] = val13N4_1.toJson();
        // REQUIRE(expected == generated);
    }
}
