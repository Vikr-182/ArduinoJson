// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include <stddef.h>  // ptrdiff_t, size_t

#include "../Array/ArrayData.hpp"
#include "../Numbers/Float.hpp"
#include "../Numbers/Integer.hpp"
#include "../Object/ObjectData.hpp"

namespace ARDUINOJSON_NAMESPACE {

class VariantSlot;

enum VariantType {
  JSON_NULL,
  JSON_LINKED_RAW,
  JSON_OWNED_RAW,
  JSON_LINKED_STRING,
  JSON_OWNED_STRING,
  JSON_BOOLEAN,
  JSON_POSITIVE_INTEGER,
  JSON_NEGATIVE_INTEGER,
  JSON_ARRAY,
  JSON_OBJECT,
  JSON_FLOAT
};

struct RawData {
  const char *data;
  size_t size;
};

// A union that defines the actual content of a VariantData.
// The enum VariantType determines which member is in use.
union VariantContent {
  Float asFloat;
  UInt asInteger;
  ArrayData asArray;
  ObjectData asObject;
  const char *asString;
  struct {
    const char *data;
    size_t size;
  } asRaw;
};

// this struct must be a POD type to prevent error calling offsetof on clang
struct VariantData {
  VariantContent content;
  bool keyIsOwned : 1;
  VariantType type : 7;
};

inline VariantData *getVariantData(ArrayData *arr) {
  const ptrdiff_t offset =
      offsetof(VariantData, content) - offsetof(VariantContent, asArray);
  if (!arr) return 0;
  return reinterpret_cast<VariantData *>(reinterpret_cast<char *>(arr) -
                                         offset);
}

inline VariantData *getVariantData(ObjectData *obj) {
  const ptrdiff_t offset =
      offsetof(VariantData, content) - offsetof(VariantContent, asObject);
  if (!obj) return 0;
  return reinterpret_cast<VariantData *>(reinterpret_cast<char *>(obj) -
                                         offset);
}
}  // namespace ARDUINOJSON_NAMESPACE
