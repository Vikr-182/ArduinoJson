// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "ArrayRef.hpp"
#include "ObjectRef.hpp"

namespace ARDUINOJSON_NAMESPACE {

inline ArrayRef ArrayRef::createNestedArray() const {
  return add().to<ArrayRef>();
}

inline ObjectRef ArrayRef::createNestedObject() const {
  return add().to<ObjectRef>();
}
}  // namespace ARDUINOJSON_NAMESPACE
