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

template <typename TKey>
inline bool ObjectData::containsKey(const TKey& key) const {
  return findSlot(key);
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

template <typename TString>
inline ArrayRef ObjectRef::createNestedArray(const TString& key) const {
  return set(key).template to<ArrayRef>();
}

template <typename TString>
inline ArrayRef ObjectRef::createNestedArray(TString* key) const {
  return set(key).template to<ArrayRef>();
}
}  // namespace ARDUINOJSON_NAMESPACE
