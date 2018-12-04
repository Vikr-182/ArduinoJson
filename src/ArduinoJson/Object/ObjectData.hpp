// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

namespace ARDUINOJSON_NAMESPACE {

class VariantSlot;
class MemoryPool;

struct VariantData;

struct ObjectData {
  VariantSlot *head;
  VariantSlot *tail;

 public:
  // Must be a POD!
  // - no constructor
  // - no destructor
  // - no virtual
  // - no inheritance

  void clear();

  template <typename TKey>
  bool containsKey(const TKey &key) const;

  bool copyFrom(const ObjectData &src, MemoryPool *pool);

  bool equals(const ObjectData &other) const;

  template <typename TKey>
  VariantData *get(TKey key) const;

  template <typename TKey>
  VariantData *set(TKey key, MemoryPool *pool);

  template <typename TKey>
  void remove(TKey key) {
    remove(findSlot(key));
  }

  void remove(VariantSlot *slot);

  size_t size() const;

 private:
  template <typename TKey>
  VariantData *add(TKey key, MemoryPool *pool);

  template <typename TKey>
  VariantSlot *findSlot(TKey key) const;
};
}  // namespace ARDUINOJSON_NAMESPACE
