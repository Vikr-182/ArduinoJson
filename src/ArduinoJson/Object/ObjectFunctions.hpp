// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Memory/MemoryPool.hpp"
#include "../Variant/SlotFunctions.hpp"
#include "../Variant/VariantData.hpp"

namespace ARDUINOJSON_NAMESPACE {

bool variantCopy(VariantData*, const VariantData*, MemoryPool*);

bool variantEquals(const VariantData*, const VariantData*);

inline bool objectEquals(const ObjectData* o1, const ObjectData* o2) {
  if (o1 == o2) return true;
  if (!o1 || !o2) return false;

  for (VariantSlot* s = o1->head; s; s = s->getNext()) {
    VariantData* v1 = s->getData();
    VariantData* v2 = o2->get(makeString(slotGetKey(s)));
    if (!variantEquals(v1, v2)) return false;
  }
  return true;
}
}  // namespace ARDUINOJSON_NAMESPACE
