// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "ArrayRef.hpp"
#include "Object.hpp"

namespace ARDUINOJSON_NAMESPACE {

inline ArrayRef ArrayRef::createNestedArray() const {
  return add().to<ArrayRef>();
}

inline Object ArrayRef::createNestedObject() const {
  return add().to<Object>();
}
}  // namespace ARDUINOJSON_NAMESPACE
