// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Serialization/DynamicStringWriter.hpp"
#include "VariantFunctions.hpp"

namespace ARDUINOJSON_NAMESPACE {

class ArrayRef;
class ArrayConstRef;
class Object;
class ObjectConst;
class Variant;
class VariantConst;

// A metafunction that returns the type of the value returned by
// Variant::as<T>()
template <typename T>
struct VariantAs {
  typedef T type;
};

template <>
struct VariantAs<char*> {
  typedef const char* type;
};

// A metafunction that returns the type of the value returned by
// Variant::as<T>()
template <typename T>
struct VariantConstAs {
  typedef typename VariantAs<T>::type type;
};

template <>
struct VariantConstAs<Variant> {
  typedef VariantConst type;
};

template <>
struct VariantConstAs<Object> {
  typedef ObjectConst type;
};

template <>
struct VariantConstAs<ArrayRef> {
  typedef ArrayConstRef type;
};

// ---

template <typename T>
inline typename enable_if<is_integral<T>::value, T>::type variantAs(
    const VariantData* _data) {
  return variantAsIntegral<T>(_data);
}

template <typename T>
inline typename enable_if<is_same<T, bool>::value, T>::type variantAs(
    const VariantData* _data) {
  return variantAsBoolean(_data);
}

template <typename T>
inline typename enable_if<is_floating_point<T>::value, T>::type variantAs(
    const VariantData* _data) {
  return variantAsFloat<T>(_data);
}

template <typename T>
inline typename enable_if<is_same<T, const char*>::value ||
                              is_same<T, char*>::value,
                          const char*>::type
variantAs(const VariantData* _data) {
  return variantAsString(_data);
}

template <typename T>
inline typename enable_if<is_same<VariantConst, T>::value, T>::type variantAs(
    const VariantData* _data);

template <typename T>
inline typename enable_if<IsWriteableString<T>::value, T>::type variantAs(
    const VariantData* _data);

}  // namespace ARDUINOJSON_NAMESPACE
