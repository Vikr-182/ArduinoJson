// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Serialization/DynamicStringWriter.hpp"
#include "../Variant.hpp"
#include "VariantFunctions.hpp"

namespace ARDUINOJSON_NAMESPACE {

template <typename T>
inline typename enable_if<is_same<VariantConst, T>::value, T>::type variantAs(
    const VariantData* _data) {
  return VariantConst(_data);
}

template <typename T>
inline typename enable_if<IsWriteableString<T>::value, T>::type variantAs(
    const VariantData* _data) {
  const char* cstr = variantAsString(_data);
  if (cstr) return T(cstr);
  T s;
  serializeJson(VariantConst(_data), s);
  return s;
}

}  // namespace ARDUINOJSON_NAMESPACE
