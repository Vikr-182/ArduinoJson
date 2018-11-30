// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

namespace ARDUINOJSON_NAMESPACE {
class Array;
class Object;
class JsonVariant;

// A metafunction that returns the type of the value returned by
// JsonVariant::to<T>()
template <typename T>
struct JsonVariantTo {};

template <>
struct JsonVariantTo<Array> {
  typedef Array type;
};
template <>
struct JsonVariantTo<Object> {
  typedef Object type;
};
template <>
struct JsonVariantTo<JsonVariant> {
  typedef JsonVariant type;
};

}  // namespace ARDUINOJSON_NAMESPACE
