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

  SECTION("Comparison") {
    REQUIRE((string_A < string_B) == (str_string_A < str_string_B));
    REQUIRE((string_A > string_B) == (str_string_A > str_string_B));
  }

  SECTION( "Constructors" ) {
    {
      kwValString copy = string_A;
      REQUIRE( str_string_A == copy.str());
    }

    kwValString ptr = kwValString(str_string_A);
    REQUIRE( ptr.str() == str_string_A); // This assumes that
                                         // comparison == is working

    kwValString fromkwPtr = kwValString(ptr);
    std::shared_ptr<kwValString> shared = std::make_shared<kwValString>("TestA");
    kwValString fromShared = kwValString(shared);
    REQUIRE( ptr == fromkwPtr);
    REQUIRE( ptr.str() == fromkwPtr.str());
    REQUIRE( fromShared == *shared);
    REQUIRE( fromShared.str() == shared->str());

    kwValString muha = string("BUH");
    auto sharedPtr = make_shared<kwValString>("Test");
  }

  SECTION( "Operator+" ) {
    kwValString added = string_A + string_B;
    string str_add = str_string_A + str_string_B;
    REQUIRE( str_add == added.str());
    kwValString emptykw = kwValString();
    kwValString emptykw2 = kwValString("Buh");
    kwValString res = emptykw + emptykw2;
    REQUIRE(res == emptykw2);
  }

  SECTION( "Pushback" ) {
    string_A.push_back('B');
    REQUIRE( string_A.str() == string("TestAB"));
  }

  SECTION( "Clear" ) {
    kwValString clear = kwValString("Buh");
    string clearstr = string("Buh");
    REQUIRE( clear.str() == clearstr);
    clear.clear();
    clearstr.clear();
    REQUIRE(clear.size() == clearstr.size());
  }

  SECTION( "O Stream") {
    std::ostringstream os;
    os << string_A;
    string fromOS = os.str();
    REQUIRE(fromOS == string_A.str());
  }

  SECTION("Assign string") {
    const kwValString constkwVal = kwValString("Const");
    const string conststr = string("Conststr");
    kwValString assigned = constkwVal;
    REQUIRE(assigned == constkwVal);

    assigned = conststr;
    REQUIRE(assigned == conststr);
  }

  SECTION("Erase") {
    kwValString acopy = kwValString(str_string_A);
    acopy.erase(0, 4);
    str_string_A.erase(0, 4);
    REQUIRE(acopy.str() == str_string_A);
  }

  SECTION("Return plain chars") {
    const char* chars = string_A.data();
    REQUIRE(strcmp(chars, "TestA") == 0);
  }
}
