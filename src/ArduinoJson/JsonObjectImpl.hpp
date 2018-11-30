// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Array.hpp"
#include "JsonObject.hpp"

namespace ARDUINOJSON_NAMESPACE {

template <typename TString>
inline Array JsonObject::createNestedArray(const TString& key) const {
  return set(key).template to<Array>();
}

template <typename TString>
inline Array JsonObject::createNestedArray(TString* key) const {
  return set(key).template to<Array>();
}
}  // namespace ARDUINOJSON_NAMESPACE
