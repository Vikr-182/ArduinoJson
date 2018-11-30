// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Document.hpp"

namespace ARDUINOJSON_NAMESPACE {

template <size_t CAPACITY>
class StaticDocument : public Document {
  static const size_t ACTUAL_CAPACITY =
      AddPadding<Max<1, CAPACITY>::value>::value;

 public:
  StaticDocument() : Document(_buffer, ACTUAL_CAPACITY) {}

  StaticDocument(const Document& src) : Document(_buffer, ACTUAL_CAPACITY) {
    copy(src);
  }

  StaticDocument operator=(const Document& src) {
    copy(src);
    return *this;
  }

 private:
  char _buffer[ACTUAL_CAPACITY];
};

}  // namespace ARDUINOJSON_NAMESPACE
