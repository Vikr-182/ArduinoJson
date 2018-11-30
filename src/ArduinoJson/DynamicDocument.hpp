// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Document.hpp"

#include <stdlib.h>  // malloc, free

namespace ARDUINOJSON_NAMESPACE {

class DynamicDocument : public Document {
 public:
  DynamicDocument(size_t capa = ARDUINOJSON_DEFAULT_POOL_SIZE)
      : Document(alloc(capa), addPadding(capa)) {}

  DynamicDocument(const DynamicDocument& src)
      : Document(alloc(src.memoryUsage()), addPadding(src.memoryUsage())) {
    copy(src);
  }

  DynamicDocument(const Document& src)
      : Document(alloc(src.memoryUsage()), addPadding(src.memoryUsage())) {
    copy(src);
  }

  ~DynamicDocument() {
    free(memoryPool().buffer());
  }

  DynamicDocument& operator=(const DynamicDocument& src) {
    copy(src);
    return *this;
  }

  template <typename T>
  DynamicDocument& operator=(const Document& src) {
    copy(src);
    return *this;
  }

 private:
  static char* alloc(size_t capa) {
    return reinterpret_cast<char*>(malloc(addPadding(capa)));
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
