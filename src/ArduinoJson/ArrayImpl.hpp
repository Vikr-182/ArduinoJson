// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Array.hpp"
#include "JsonObject.hpp"

namespace ARDUINOJSON_NAMESPACE {

inline Array Array::createNestedArray() const {
  return add().to<Array>();
}

inline JsonObject Array::createNestedObject() const {
  return add().to<JsonObject>();
}
}  // namespace ARDUINOJSON_NAMESPACE
