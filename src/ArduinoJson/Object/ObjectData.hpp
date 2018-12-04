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

  template <typename TKey>
  VariantSlot *findSlot(TKey key) const;
};
}  // namespace ARDUINOJSON_NAMESPACE
