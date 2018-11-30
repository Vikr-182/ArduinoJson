// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("JsonArray::get()") {
  DynamicJsonDocument doc;
  deserializeJson(doc, "[1,2,3]");
  JsonArray array = doc.as<JsonArray>();

  SECTION("Underflow") {
    REQUIRE(array.get(-1).isNull());
  }

  SECTION("Overflow") {
    REQUIRE(array.get(3).isNull());
  }
}
