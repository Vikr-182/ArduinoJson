// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Data/SlotFunctions.hpp"
#include "JsonPair.hpp"

namespace ARDUINOJSON_NAMESPACE {

class JsonPairPtr {
 public:
  JsonPairPtr(MemoryPool *memoryPool, VariantSlot *slot)
      : _pair(memoryPool, slot) {}

  const JsonPair *operator->() const {
    return &_pair;
  }

  const JsonPair &operator*() const {
    return _pair;
  }

 private:
  JsonPair _pair;
};

class ObjectIterator {
 public:
  ObjectIterator() : _slot(0) {}

  explicit ObjectIterator(MemoryPool *memoryPool, VariantSlot *slot)
      : _memoryPool(memoryPool), _slot(slot) {}

  JsonPair operator*() const {
    return JsonPair(_memoryPool, _slot);
  }
  JsonPairPtr operator->() {
    return JsonPairPtr(_memoryPool, _slot);
  }

  bool operator==(const ObjectIterator &other) const {
    return _slot == other._slot;
  }

  bool operator!=(const ObjectIterator &other) const {
    return _slot != other._slot;
  }

  ObjectIterator &operator++() {
    _slot = _slot->getNext();
    return *this;
  }

  ObjectIterator &operator+=(size_t distance) {
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

class JsonPairConstPtr {
 public:
  JsonPairConstPtr(const VariantSlot *slot) : _pair(slot) {}

  const JsonPairConst *operator->() const {
    return &_pair;
  }

  const JsonPairConst &operator*() const {
    return _pair;
  }

 private:
  JsonPairConst _pair;
};

class ObjectConstIterator {
 public:
  ObjectConstIterator() : _slot(0) {}

  explicit ObjectConstIterator(const VariantSlot *slot) : _slot(slot) {}

  JsonPairConst operator*() const {
    return JsonPairConst(_slot);
  }
  JsonPairConstPtr operator->() {
    return JsonPairConstPtr(_slot);
  }

  bool operator==(const ObjectConstIterator &other) const {
    return _slot == other._slot;
  }

  bool operator!=(const ObjectConstIterator &other) const {
    return _slot != other._slot;
  }

  ObjectConstIterator &operator++() {
    _slot = _slot->getNext();
    return *this;
  }

  ObjectConstIterator &operator+=(size_t distance) {
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
