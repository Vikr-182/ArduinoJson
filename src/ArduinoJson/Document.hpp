// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Data/VariantTo.hpp"
#include "Memory/MemoryPool.hpp"
#include "Variant.hpp"

namespace ARDUINOJSON_NAMESPACE {

class Document : public Visitable {
 public:
  uint8_t nestingLimit;

  template <typename Visitor>
  void accept(Visitor& visitor) const {
    return getVariant().accept(visitor);
  }

  template <typename T>
  typename VariantAs<T>::type as() {
    return getVariant().template as<T>();
  }

  template <typename T>
  typename VariantConstAs<T>::type as() const {
    return getVariant().template as<T>();
  }

  void clear() {
    _memoryPool.clear();
    _rootData.type = JSON_NULL;
  }

  template <typename T>
  bool is() const {
    return getVariant().template is<T>();
  }

  size_t memoryUsage() const {
    return _memoryPool.size();
  }

  size_t capacity() const {
    return _memoryPool.capacity();
  }

  // for internal use only
  MemoryPool& memoryPool() {
    return _memoryPool;
  }

  template <typename T>
  typename VariantTo<T>::type to() {
    clear();
    return getVariant().template to<T>();
  }

 protected:
  Document(char* buf, size_t capa)
      : nestingLimit(ARDUINOJSON_DEFAULT_NESTING_LIMIT),
        _memoryPool(buf, capa) {}

  void copy(const Document& src) {
    nestingLimit = src.nestingLimit;
    to<Variant>().set(src.as<Variant>());
  }

 private:
  Variant getVariant() {
    return Variant(&_memoryPool, &_rootData);
  }

  VariantConst getVariant() const {
    return VariantConst(&_rootData);
  }

  MemoryPool _memoryPool;
  VariantData _rootData;
};

}  // namespace ARDUINOJSON_NAMESPACE
