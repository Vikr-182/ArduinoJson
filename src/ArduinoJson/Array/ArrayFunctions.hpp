// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Variant/SlotFunctions.hpp"
#include "../Variant/VariantData.hpp"

namespace ARDUINOJSON_NAMESPACE {

bool variantEquals(const VariantData*, const VariantData*);

inline bool arrayEquals(const ArrayData* a1, const ArrayData* a2) {
  if (a1 == a2) return true;
  if (!a1 || !a2) return false;
  VariantSlot* s1 = a1->head;
  VariantSlot* s2 = a2->head;
  for (;;) {
    if (s1 == s2) return true;
    if (!s1 || !s2) return false;
    if (!variantEquals(s1->getData(), s2->getData())) return false;
    s1 = s1->getNext();
    s2 = s2->getNext();
  }
}

inline size_t arraySize(const ArrayData* arr) {
  if (!arr) return 0;
  return slotSize(arr->head);
}
}  // namespace ARDUINOJSON_NAMESPACE
