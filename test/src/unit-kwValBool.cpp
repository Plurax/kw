#include "catch.hpp"
#include "kw/kwValBool.h"
#include "kw/kwValString.h"
#include "string.h"
#include <limits>
#include <memory>
#include <sstream>

using namespace std;

TEST_CASE("kwValBool Method tests - should behave the same like float",
          "[kwValBool]") {

  kwValBool false_val1 = false;
  kwValBool true_val1 = true;
  kwValBool false_val2 = false;
  kwValBool true_val2 = true;

  SECTION("Constructor") {
    kwValBool emptyConstr;
    REQUIRE(emptyConstr.getValue() == false);

    kwValBool val(true);
    REQUIRE(val.getValue() == true);
    kwValBool val2(true);
    REQUIRE(val == val2);
  }

  SECTION("O Stream") {
    std::ostringstream os;
    os << false_val1;
    string fromOS = os.str();
    REQUIRE(fromOS == string("0"));
  }

  SECTION("Comparisons") {}

  SECTION("asString") {
    // This only tests the standard behaviour, to create custom
    // formatting you need to use stringstream instead.
    REQUIRE(kwValString("false") == false_val2.asString());
    REQUIRE(kwValString("true") == true_val2.asString());
  }

  SECTION("Pointer type destructor branch") {
    kwValBool *rawptr = new kwValBool(true);
    kwValBool rawptrres = kwValBool(true);
    delete rawptr;
    REQUIRE(rawptrres == *rawptr);
  }

  SECTION("json serialization") {
    json expected = {{"bool", true}};
    json generated;
    generated["bool"] = true_val1.toJson();
    REQUIRE(expected == generated);
  }
}
