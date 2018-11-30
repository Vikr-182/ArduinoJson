// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Key.hpp"
#include "Variant.hpp"

namespace ARDUINOJSON_NAMESPACE {
// A key value pair for ObjectData.
class Pair {
 public:
  Pair(MemoryPool* memoryPool, VariantSlot* slot) : _key(slot) {
    if (slot) {
      _value = Variant(memoryPool, &slot->value);
    }
  }

  Key key() const {
    return _key;
  }

  Variant value() const {
    return _value;
  }

 private:
  Key _key;
  Variant _value;
};

class PairConst {
 public:
  PairConst(const VariantSlot* slot) : _key(slot) {
    if (slot) {
      _value = VariantConst(&slot->value);
    }
  }

  Key key() const {
    return _key;
  }

  VariantConst value() const {
    return _value;
  }

 private:
  Key _key;
  VariantConst _value;
};
}  // namespace ARDUINOJSON_NAMESPACE
