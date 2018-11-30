// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Data/SlotFunctions.hpp"
#include "Variant.hpp"

namespace ARDUINOJSON_NAMESPACE {

class VariantPtr {
 public:
  VariantPtr(MemoryPool *memoryPool, VariantData *data)
      : _variant(memoryPool, data) {}

  Variant *operator->() {
    return &_variant;
  }

  Variant &operator*() {
    return _variant;
  }

 private:
  Variant _variant;
};

class ArrayIterator {
 public:
  ArrayIterator() : _slot(0) {}
  explicit ArrayIterator(MemoryPool *memoryPool, VariantSlot *slot)
      : _memoryPool(memoryPool), _slot(slot) {}

  Variant operator*() const {
    return Variant(_memoryPool, &_slot->value);
  }
  VariantPtr operator->() {
    return VariantPtr(_memoryPool, &_slot->value);
  }

  bool operator==(const ArrayIterator &other) const {
    return _slot == other._slot;
  }

  bool operator!=(const ArrayIterator &other) const {
    return _slot != other._slot;
  }

  ArrayIterator &operator++() {
    _slot = _slot->getNext();
    return *this;
  }

  ArrayIterator &operator+=(size_t distance) {
    _slot = _slot->getNext(distance);
    return *this;
  }

  VariantSlot *internal() {
    return _slot;
  }

 private:
  MemoryPool *_memoryPool;
  VariantSlot *_slot;
};

class VariantConstPtr {
 public:
  VariantConstPtr(const VariantData *data) : _variant(data) {}

  VariantConst *operator->() {
    return &_variant;
  }

  VariantConst &operator*() {
    return _variant;
  }

 private:
  VariantConst _variant;
};

class ArrayConstIterator {
 public:
  ArrayConstIterator() : _slot(0) {}
  explicit ArrayConstIterator(const VariantSlot *slot) : _slot(slot) {}

  VariantConst operator*() const {
    return VariantConst(&_slot->value);
  }
  VariantConstPtr operator->() {
    return VariantConstPtr(&_slot->value);
  }

  bool operator==(const ArrayConstIterator &other) const {
    return _slot == other._slot;
  }

  bool operator!=(const ArrayConstIterator &other) const {
    return _slot != other._slot;
  }

  ArrayConstIterator &operator++() {
    _slot = _slot->getNext();
    return *this;
  }

  ArrayConstIterator &operator+=(size_t distance) {
    _slot = _slot->getNext(distance);
    return *this;
  }

  const VariantSlot *internal() {
    return _slot;
  }

 private:
  const VariantSlot *_slot;
};
}  // namespace ARDUINOJSON_NAMESPACE
