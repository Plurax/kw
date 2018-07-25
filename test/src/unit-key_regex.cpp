
#include "catch.hpp"
#include <regex>
#include <string>
#include <iostream>

using namespace std;

string extractKey( string str ) {
  // find ${KEY} as match on KEY
  regex re("\\$\\{(.*)\\}");
  smatch mat;
  if (regex_search(str, mat, re))
  {
    cout << "Matched: " << mat.str(1) << endl;
    return mat.str(1);
  }
  else
  {
    cout << "No match..." << endl;
    return string("");
  }
}

TEST_CASE( "Regex NO Match", "[extractKey]" ) {
  REQUIRE( extractKey(string("das ist ein TEST")) == string(""));
}

TEST_CASE( "Regex Match END", "[extractKey]" ) {
  REQUIRE( extractKey(string("das ist ein ${TEST}")) == string("TEST"));
}

TEST_CASE( "Regex Match START", "[extractKey]" ) {
  REQUIRE( extractKey(string("${TEST}sdfsdf")) == string("TEST"));
}

TEST_CASE( "Regex Match WITHIN", "[extractKey]" ) {
  REQUIRE( extractKey(string("buh hab ${TEST}sdfsdf")) == string("TEST"));
}

TEST_CASE( "Regex Match extWITHIN", "[extractKey]" ) {
  REQUIRE( extractKey(string("buh hab ${TEST:Temperature}sdfsdf")) == string("TEST:Temperature"));
}
