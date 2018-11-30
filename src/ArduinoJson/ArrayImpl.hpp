// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Array.hpp"
#include "Object.hpp"

namespace ARDUINOJSON_NAMESPACE {

inline Array Array::createNestedArray() const {
  return add().to<Array>();
}

inline Object Array::createNestedObject() const {
  return add().to<Object>();
}
}  // namespace ARDUINOJSON_NAMESPACE
