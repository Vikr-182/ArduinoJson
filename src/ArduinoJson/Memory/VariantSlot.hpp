// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Data/JsonVariantData.hpp"
#include "../Polyfills/type_traits.hpp"

namespace ARDUINOJSON_NAMESPACE {

typedef conditional<sizeof(void*) <= 2, int8_t, int16_t>::type VariantSlotDiff;

struct VariantSlot {
  JsonVariantData value;
  VariantSlotDiff next;
  VariantSlotDiff prev;
  const char* key;

  VariantSlot* getNext() {
    return next ? this + next : 0;
  }

  const VariantSlot* getNext() const {
    return next ? this + next : 0;
  }

  VariantSlot* getPrev() {
    return prev ? this + prev : 0;
  }

  void setNext(VariantSlot* slot) {
    next = VariantSlotDiff(slot ? slot - this : 0);
  }

  void setPrev(VariantSlot* slot) {
    prev = VariantSlotDiff(slot ? slot - this : 0);
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
