// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Memory/MemoryPool.hpp"
#include "../Variant/SlotFunctions.hpp"
#include "../Variant/VariantData.hpp"

namespace ARDUINOJSON_NAMESPACE {

inline void objectRemove(ObjectData* obj, VariantSlot* slot) {
  if (!obj) return;
  if (!slot) return;
  VariantSlot* prev = slot->getPrev(obj->head);
  VariantSlot* next = slot->getNext();
  if (prev)
    prev->setNext(next);
  else
    obj->head = next;
  if (!next) obj->tail = prev;
}

inline size_t objectSize(const ObjectData* obj) {
  if (!obj) return 0;
  return slotSize(obj->head);
}

bool variantCopy(VariantData*, const VariantData*, MemoryPool*);

inline bool objectCopy(ObjectData* dst, const ObjectData* src,
                       MemoryPool* pool) {
  if (!dst || !src) return false;
  dst->clear();
  for (VariantSlot* s = src->head; s; s = s->getNext()) {
    VariantData* var;
    if (s->ownsKey())
      var = dst->add(ZeroTerminatedRamString(s->key()), pool);
    else
      var = dst->add(ZeroTerminatedRamStringConst(s->key()), pool);
    if (!variantCopy(var, s->getData(), pool)) return false;
  }
  return true;
}

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
