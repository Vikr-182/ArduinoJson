// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Variant/VariantData.hpp"
#include "ArrayFunctions.hpp"
#include "ArrayIterator.hpp"

// Returns the size (in bytes) of an array with n elements.
// Can be very handy to determine the size of a StaticMemoryPool.
#define JSON_ARRAY_SIZE(NUMBER_OF_ELEMENTS) \
  ((NUMBER_OF_ELEMENTS) * sizeof(ARDUINOJSON_NAMESPACE::VariantSlot))

namespace ARDUINOJSON_NAMESPACE {

class ObjectRef;
class ArraySubscript;

template <typename TData>
class ArrayRefBase {
 public:
  FORCE_INLINE bool isNull() const {
    return _data == 0;
  }

  FORCE_INLINE VariantConstRef operator[](size_t index) const {
    return VariantConstRef(arrayGet(_data, index));
  }

  FORCE_INLINE size_t size() const {
    return arraySize(_data);
  }

 protected:
  ArrayRefBase(TData* data) : _data(data) {}
  TData* _data;
};

class ArrayConstRef : public ArrayRefBase<const ArrayData>, public Visitable {
  friend class ArrayRef;
  typedef ArrayRefBase<const ArrayData> base_type;

 public:
  typedef ArrayConstRefIterator iterator;

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

  FORCE_INLINE ArrayConstRef() : base_type(0) {}
  FORCE_INLINE ArrayConstRef(const ArrayData* data) : base_type(data) {}

  FORCE_INLINE bool operator==(ArrayConstRef rhs) const {
    return arrayEquals(_data, rhs._data);
  }
};

class ArrayRef : public ArrayRefBase<ArrayData>, public Visitable {
  typedef ArrayRefBase<ArrayData> base_type;

 public:
  typedef ArrayIterator iterator;

  FORCE_INLINE ArrayRef() : base_type(0), _memoryPool(0) {}
  FORCE_INLINE ArrayRef(MemoryPool* pool, ArrayData* data)
      : base_type(data), _memoryPool(pool) {}

  operator VariantRef() {
    return VariantRef(_memoryPool, getVariantData(_data));
  }

  operator ArrayConstRef() const {
    return ArrayConstRef(_data);
  }

  // Adds the specified value at the end of the array.
  //
  // bool add(TValue);
  // TValue = bool, long, int, short, float, double, serialized, VariantRef,
  //          std::string, String, ObjectRef
  template <typename T>
  FORCE_INLINE bool add(const T& value) const {
    return add().set(value);
  }
  // Adds the specified value at the end of the array.
  FORCE_INLINE bool add(ArrayRef value) const {
    return add().set(value);
  }
  //
  // bool add(TValue);
  // TValue = char*, const char*, const FlashStringHelper*
  template <typename T>
  FORCE_INLINE bool add(T* value) const {
    return add().set(value);
  }

  VariantRef add() const {
    if (!_data) return VariantRef();
    return VariantRef(_memoryPool, _data->add(_memoryPool));
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
      ArrayRef nestedArray = createNestedArray();
      for (size_t j = 0; j < N2; j++) {
        ok &= nestedArray.add(array[i][j]);
      }
    }
    return ok;
  }

  // Copy a ArrayRef
  FORCE_INLINE bool copyFrom(ArrayRef src) const {
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
      it->as<ArrayRef>().copyTo(array[i++]);
    }
  }

  FORCE_INLINE ArrayRef createNestedArray() const;
  FORCE_INLINE ObjectRef createNestedObject() const;

  FORCE_INLINE ArraySubscript operator[](size_t index) const;

  FORCE_INLINE bool operator==(ArrayRef rhs) const {
    return arrayEquals(_data, rhs._data);
  }

  // Gets the value at the specified index.
  FORCE_INLINE VariantRef get(size_t index) const {
    return VariantRef(_memoryPool, arrayGet(_data, index));
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
    ArrayConstRef(_data).accept(visitor);
  }

 private:
  template <typename TValueRef>
  FORCE_INLINE bool add_impl(TValueRef value) const {
    return add().set(value);
  }

  MemoryPool* _memoryPool;
};
}  // namespace ARDUINOJSON_NAMESPACE
