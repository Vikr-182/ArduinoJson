// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Object/ObjectRef.hpp"
#include "ArrayData.hpp"
#include "ArrayRef.hpp"

namespace ARDUINOJSON_NAMESPACE {

inline VariantData *ArrayData::add(MemoryPool *pool) {
  VariantSlot *slot = pool->allocVariant();
  if (!slot) return 0;

  slot->init();

  if (this->tail) {
    slot->attachTo(this->tail);
    this->tail = slot;
  } else {
    this->head = slot;
    this->tail = slot;
  }

  return slot->getData();
}

inline void ArrayData::clear() {
  this->head = 0;
  this->tail = 0;
}

inline bool ArrayData::copyFrom(const ArrayData *src, MemoryPool *pool) {
  if (!src) return false;
  clear();
  for (VariantSlot *s = src->head; s; s = s->getNext()) {
    if (!variantCopy(add(pool), s->getData(), pool)) return false;
  }
  return true;
}

inline bool ArrayData::equals(const ArrayData &other) const {
  VariantSlot *s1 = this->head;
  VariantSlot *s2 = other.head;
  for (;;) {
    if (s1 == s2) return true;
    if (!s1 || !s2) return false;
    if (!variantEquals(s1->getData(), s2->getData())) return false;
    s1 = s1->getNext();
    s2 = s2->getNext();
  }
}

inline VariantData *ArrayData::get(size_t index) const {
  VariantSlot *slot = getSlot(index);
  return slot ? slot->getData() : 0;
}

inline VariantSlot *ArrayData::getSlot(size_t index) const {
  return this->head->getNext(index);
}

inline void ArrayData::remove(VariantSlot *slot) {
  if (!slot) return;

  VariantSlot *prev = slot->getPrev(this->head);
  VariantSlot *next = slot->getNext();

  if (prev)
    prev->setNext(next);
  else
    this->head = next;
  if (!next) this->tail = prev;
}

inline void ArrayData::remove(size_t index) {
  remove(getSlot(index));
}

inline size_t ArrayData::size() const {
  return slotSize(this->head);
}

inline ArrayRef ArrayRef::createNestedArray() const {
  return add().to<ArrayRef>();
}

inline ObjectRef ArrayRef::createNestedObject() const {
  return add().to<ObjectRef>();
}
}  // namespace ARDUINOJSON_NAMESPACE
