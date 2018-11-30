// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Memory/MemoryPool.hpp"
#include "../Polyfills/assert.hpp"
#include "../Strings/StringTypes.hpp"
#include "VariantData.hpp"

namespace ARDUINOJSON_NAMESPACE {

template <typename TKey>
inline bool slotSetKey(VariantSlot* var, TKey key, MemoryPool* pool) {
  char* dup = key.save(pool);
  if (!dup) return false;
  var->key = dup;
  var->keyIsOwned = true;
  return true;
}

inline bool slotSetKey(VariantSlot* var, ZeroTerminatedRamStringConst key,
                       MemoryPool*) {
  var->key = key.c_str();
  var->keyIsOwned = false;
  return true;
}

inline bool slotSetKey(VariantSlot* var, StringInMemoryPool key, MemoryPool*) {
  var->key = key.c_str();
  var->keyIsOwned = true;
  return true;
}

inline const char* slotGetKey(const VariantSlot* var) {
  return var->key;
}

inline size_t slotSize(const VariantSlot* var) {
  size_t n = 0;
  while (var) {
    n++;
    var = var->getNext();
  }
  return n;
}
}  // namespace ARDUINOJSON_NAMESPACE
