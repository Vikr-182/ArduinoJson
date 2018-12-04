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

inline ArrayRef ArrayRef::createNestedArray() const {
  return add().to<ArrayRef>();
}

inline ObjectRef ArrayRef::createNestedObject() const {
  return add().to<ObjectRef>();
}
}  // namespace ARDUINOJSON_NAMESPACE
