// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "JsonKey.hpp"
#include "Variant.hpp"

namespace ARDUINOJSON_NAMESPACE {
// A key value pair for ObjectData.
class JsonPair {
 public:
  JsonPair(MemoryPool* memoryPool, VariantSlot* slot) : _key(slot) {
    if (slot) {
      _value = Variant(memoryPool, &slot->value);
    }
  }

  JsonKey key() const {
    return _key;
  }

  Variant value() const {
    return _value;
  }

 private:
  JsonKey _key;
  Variant _value;
};

class JsonPairConst {
 public:
  JsonPairConst(const VariantSlot* slot) : _key(slot) {
    if (slot) {
      _value = VariantConst(&slot->value);
    }
  }

  JsonKey key() const {
    return _key;
  }

  VariantConst value() const {
    return _value;
  }

 private:
  JsonKey _key;
  VariantConst _value;
};
}  // namespace ARDUINOJSON_NAMESPACE
