#include "catch.hpp"
#include "kw/kwValBool.h"
#include "kw/kwValFloat.h"
#include "kw/kwSystem.h"
#include "kw/kwValString.h"
#include "kw/kwDataContainer.h"
#include "string.h"
#include <sstream>
#include <memory>
#include <limits>

using namespace std;

TEST_CASE("kwDataContainer Method tests", "[kwDataContainer]") {

  json config =
      "{\"DataLayer\" : {\"DataSource\": { \"config\": { \"Temperature\": 1002.4 }, \"name\": \"valuemap\", \"classname\": \"kwDataContainer\", \"libname\": \"kw\" }}}"_json;

  kwSystem &sys = kwSystem::Inst();
  sys.configure(config);

  SECTION("Retrieve valuemap") {
    std::shared_ptr<kwDataSource> mySource = sys.getDataSource(kwValString("valuemap"));

    std::shared_ptr<kwValue<kwValString>> fvalue = mySource->getValue(kwValString("Temperature"));

    kwValBool val(true);
    REQUIRE(val.getValue() == true);
    kwValBool val2(true);
    REQUIRE(val == val2);
  }
}
