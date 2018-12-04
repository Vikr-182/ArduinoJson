// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Array/ArrayRef.hpp"
#include "ObjectRef.hpp"

namespace ARDUINOJSON_NAMESPACE {

template <typename TKey>
inline VariantData* ObjectData::add(TKey key, MemoryPool* pool) {
  VariantSlot* slot = pool->allocVariant();
  if (!slot) return 0;

  slot->init();

  if (this->tail) {
    slot->attachTo(this->tail);
    this->tail = slot;
  } else {
    this->head = slot;
    this->tail = slot;
  }

  if (!slotSetKey(slot, key, pool)) return 0;
  return slot->getData();
}

inline void ObjectData::clear() {
  this->head = 0;
  this->tail = 0;
}

template <typename TKey>
inline bool ObjectData::containsKey(const TKey& key) const {
  return findSlot(key);
}

inline bool ObjectData::copyFrom(const ObjectData& src, MemoryPool* pool) {
  clear();
  for (VariantSlot* s = src.head; s; s = s->getNext()) {
    VariantData* var;
    if (s->ownsKey())
      var = add(ZeroTerminatedRamString(s->key()), pool);
    else
      var = add(ZeroTerminatedRamStringConst(s->key()), pool);
    if (!variantCopy(var, s->getData(), pool)) return false;
  }
  return true;
}

inline bool ObjectData::equals(const ObjectData& other) const {
  for (VariantSlot* s = this->head; s; s = s->getNext()) {
    VariantData* v1 = s->getData();
    VariantData* v2 = other.get(makeString(slotGetKey(s)));
    if (!variantEquals(v1, v2)) return false;
  }
  return true;
}

template <typename TKey>
inline VariantSlot* ObjectData::findSlot(TKey key) const {
  VariantSlot* slot = this->head;
  while (slot) {
    if (key.equals(slotGetKey(slot))) break;
    slot = slot->getNext();
  }
  return slot;
}

template <typename TKey>
inline VariantData* ObjectData::get(TKey key) const {
  VariantSlot* slot = findSlot(key);
  return slot ? slot->getData() : 0;
}

inline void ObjectData::remove(VariantSlot* slot) {
  if (!slot) return;
  VariantSlot* prev = slot->getPrev(this->head);
  VariantSlot* next = slot->getNext();
  if (prev)
    prev->setNext(next);
  else
    this->head = next;
  if (!next) this->tail = prev;
}

template <typename TKey>
inline VariantData* ObjectData::set(TKey key, MemoryPool* pool) {
  // ignore null key
  if (key.isNull()) return 0;

  // search a matching key
  VariantSlot* slot = findSlot(key);
  if (slot) return slot->getData();

  return add(key, pool);
}

inline size_t ObjectData::size() const {
  return slotSize(this->head);
}

template <typename TString>
inline ArrayRef ObjectRef::createNestedArray(const TString& key) const {
  return set(key).template to<ArrayRef>();
}

template <typename TString>
inline ArrayRef ObjectRef::createNestedArray(TString* key) const {
  return set(key).template to<ArrayRef>();
}
}  // namespace ARDUINOJSON_NAMESPACE
