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

  VariantData *add(MemoryPool *pool);
};
}  // namespace ARDUINOJSON_NAMESPACE
