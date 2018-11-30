// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

namespace ARDUINOJSON_NAMESPACE {

class Array;
class ArrayConst;
class Object;
class ObjectConst;
class JsonVariant;
class JsonVariantConst;

// A metafunction that returns the type of the value returned by
// JsonVariant::as<T>()
template <typename T>
struct JsonVariantAs {
  typedef T type;
};

template <>
struct JsonVariantAs<char*> {
  typedef const char* type;
};

// A metafunction that returns the type of the value returned by
// JsonVariant::as<T>()
template <typename T>
struct JsonVariantConstAs {
  typedef typename JsonVariantAs<T>::type type;
};

template <>
struct JsonVariantConstAs<JsonVariant> {
  typedef JsonVariantConst type;
};

template <>
struct JsonVariantConstAs<Object> {
  typedef ObjectConst type;
};

template <>
struct JsonVariantConstAs<Array> {
  typedef ArrayConst type;
};
}  // namespace ARDUINOJSON_NAMESPACE
