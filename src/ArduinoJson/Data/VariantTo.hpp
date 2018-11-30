// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

namespace ARDUINOJSON_NAMESPACE {
class ArrayRef;
class Object;
class Variant;

// A metafunction that returns the type of the value returned by
// Variant::to<T>()
template <typename T>
struct VariantTo {};

template <>
struct VariantTo<ArrayRef> {
  typedef ArrayRef type;
};
template <>
struct VariantTo<Object> {
  typedef Object type;
};
template <>
struct VariantTo<Variant> {
  typedef Variant type;
};

}  // namespace ARDUINOJSON_NAMESPACE
