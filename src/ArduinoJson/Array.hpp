// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "ArrayIterator.hpp"
#include "Data/ArrayFunctions.hpp"
#include "Data/VariantData.hpp"

// Returns the size (in bytes) of an array with n elements.
// Can be very handy to determine the size of a StaticMemoryPool.
#define JSON_ARRAY_SIZE(NUMBER_OF_ELEMENTS) \
  ((NUMBER_OF_ELEMENTS) * sizeof(ARDUINOJSON_NAMESPACE::VariantSlot))

namespace ARDUINOJSON_NAMESPACE {

class Object;
class ArraySubscript;

template <typename TData>
class ArrayProxy {
 public:
  FORCE_INLINE bool isNull() const {
    return _data == 0;
  }

  FORCE_INLINE VariantConst operator[](size_t index) const {
    return VariantConst(arrayGet(_data, index));
  }

  FORCE_INLINE size_t size() const {
    return arraySize(_data);
  }

 protected:
  ArrayProxy(TData* data) : _data(data) {}
  TData* _data;
};

class ArrayConst : public ArrayProxy<const ArrayData>, public Visitable {
  friend class Array;
  typedef ArrayProxy<const ArrayData> proxy_type;

 public:
  typedef ArrayConstIterator iterator;

  template <typename Visitor>
  FORCE_INLINE void accept(Visitor& visitor) const {
    if (_data)
      visitor.visitArray(*this);
    else
      visitor.visitNull();
  }

  FORCE_INLINE iterator begin() const {
    if (!_data) return iterator();
    return iterator(_data->head);
  }

  FORCE_INLINE iterator end() const {
    return iterator();
  }

  FORCE_INLINE ArrayConst() : proxy_type(0) {}
  FORCE_INLINE ArrayConst(const ArrayData* data) : proxy_type(data) {}

  FORCE_INLINE bool operator==(ArrayConst rhs) const {
    return arrayEquals(_data, rhs._data);
  }
};

class Array : public ArrayProxy<ArrayData>, public Visitable {
  typedef ArrayProxy<ArrayData> proxy_type;

 public:
  typedef ArrayIterator iterator;

  FORCE_INLINE Array() : proxy_type(0), _memoryPool(0) {}
  FORCE_INLINE Array(MemoryPool* pool, ArrayData* data)
      : proxy_type(data), _memoryPool(pool) {}

  operator Variant() {
    return Variant(_memoryPool, getVariantData(_data));
  }

  operator ArrayConst() const {
    return ArrayConst(_data);
  }

  // Adds the specified value at the end of the array.
  //
  // bool add(TValue);
  // TValue = bool, long, int, short, float, double, serialized, Variant,
  //          std::string, String, Object
  template <typename T>
  FORCE_INLINE bool add(const T& value) const {
    return add().set(value);
  }
  // Adds the specified value at the end of the array.
  FORCE_INLINE bool add(Array value) const {
    return add().set(value);
  }
  //
  // bool add(TValue);
  // TValue = char*, const char*, const FlashStringHelper*
  template <typename T>
  FORCE_INLINE bool add(T* value) const {
    return add().set(value);
  }

  Variant add() const {
    return Variant(_memoryPool, arrayAdd(_data, _memoryPool));
  }

  FORCE_INLINE iterator begin() const {
    if (!_data) return iterator();
    return iterator(_memoryPool, _data->head);
  }

  FORCE_INLINE iterator end() const {
    return iterator();
  }

  // Imports a 1D array
  template <typename T, size_t N>
  FORCE_INLINE bool copyFrom(T (&array)[N]) const {
    return copyFrom(array, N);
  }

  // Imports a 1D array
  template <typename T>
  bool copyFrom(T* array, size_t len) const {
    bool ok = true;
    for (size_t i = 0; i < len; i++) {
      ok &= add(array[i]);
    }
    return ok;
  }

  // Imports a 2D array
  template <typename T, size_t N1, size_t N2>
  bool copyFrom(T (&array)[N1][N2]) const {
    bool ok = true;
    for (size_t i = 0; i < N1; i++) {
      Array nestedArray = createNestedArray();
      for (size_t j = 0; j < N2; j++) {
        ok &= nestedArray.add(array[i][j]);
      }
    }
    return ok;
  }

  // Copy a Array
  FORCE_INLINE bool copyFrom(Array src) const {
    return arrayCopy(_data, src._data, _memoryPool);
  }

  // Exports a 1D array
  template <typename T, size_t N>
  FORCE_INLINE size_t copyTo(T (&array)[N]) const {
    return copyTo(array, N);
  }

  // Exports a 1D array
  template <typename T>
  size_t copyTo(T* array, size_t len) const {
    size_t i = 0;
    for (iterator it = begin(); it != end() && i < len; ++it) array[i++] = *it;
    return i;
  }

  // Exports a 2D array
  template <typename T, size_t N1, size_t N2>
  void copyTo(T (&array)[N1][N2]) const {
    if (!_data) return;
    size_t i = 0;
    for (iterator it = begin(); it != end() && i < N1; ++it) {
      it->as<Array>().copyTo(array[i++]);
    }
  }

  FORCE_INLINE Array createNestedArray() const;
  FORCE_INLINE Object createNestedObject() const;

  FORCE_INLINE ArraySubscript operator[](size_t index) const;

  FORCE_INLINE bool operator==(Array rhs) const {
    return arrayEquals(_data, rhs._data);
  }

  // Gets the value at the specified index.
  FORCE_INLINE Variant get(size_t index) const {
    return Variant(_memoryPool, arrayGet(_data, index));
  }

  // Removes element at specified position.
  FORCE_INLINE void remove(iterator it) const {
    arrayRemove(_data, it.internal());
  }

  // Removes element at specified index.
  FORCE_INLINE void remove(size_t index) const {
    arrayRemove(_data, index);
  }

  template <typename Visitor>
  FORCE_INLINE void accept(Visitor& visitor) const {
    ArrayConst(_data).accept(visitor);
  }

 private:
  template <typename TValueRef>
  FORCE_INLINE bool add_impl(TValueRef value) const {
    return add().set(value);
  }

  MemoryPool* _memoryPool;
};
}  // namespace ARDUINOJSON_NAMESPACE
