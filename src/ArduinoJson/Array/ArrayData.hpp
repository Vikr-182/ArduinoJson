// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

namespace ARDUINOJSON_NAMESPACE {

class VariantSlot;
class MemoryPool;

struct VariantData;

struct ArrayData {
  VariantSlot *head;
  VariantSlot *tail;

 public:
  // Must be a POD!
  // - no constructor
  // - no destructor
  // - no virtual
  // - no inheritance

  VariantData *add(MemoryPool *pool);
  VariantData *get(size_t index) const;
  void remove(size_t index);
  void remove(VariantSlot *slot);

 private:
  VariantSlot *getSlot(size_t index) const;
};
}  // namespace ARDUINOJSON_NAMESPACE
