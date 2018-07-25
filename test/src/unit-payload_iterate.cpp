#include "catch.hpp"
#include <regex>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

float getValue(string path)
{
  if (path == string("${valuemap:Temperature<float>}"))
      return 14.5;
}

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


/* A recursion to iterate over all objects to replace magic strings
 * with the corresponding payload string or objects
 */
string iterate(json obj)
{
  for ( auto &item : obj.get<json::object_t>() )
  {
    if (item.second.is_string())
    {
      string searchstring = item.second.get<std::string>();
      cout << "Searched: " << searchstring << endl;
      if (extractKey(searchstring) != "")
      {
        return searchstring;
      }
    }
    else
      if (item.second.is_object())
        return iterate(item.second);
  }
  return "";
}

string replaceKeys( ) {

  json exampleObj =
      {
        {"Duration" , "00:00:5.000"},
        {"MessageId" , "1"},
        {"Payload", {
            {"type" , "Temperature"},
            {"0" , {
                {"unit" , "°C"},
                {"value" , "${valuemap:Temperature<float>}"}
              }
            }
          }
        }
      };
  return iterate(exampleObj);
}

TEST_CASE( "Iterate find searchstring", "[iterate]" ) {
  REQUIRE( replaceKeys() == "${valuemap:Temperature<float>}");
}
