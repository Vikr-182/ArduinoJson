// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include <stddef.h>
#include <stdint.h>  // for uint8_t

#include "Data/VariantAs.hpp"
#include "Data/VariantData.hpp"
#include "Data/VariantFunctions.hpp"
#include "Memory/MemoryPool.hpp"
#include "Numbers/parseFloat.hpp"
#include "Numbers/parseInteger.hpp"
#include "Polyfills/type_traits.hpp"
#include "Variant.hpp"
#include "VariantBase.hpp"
#include "Visitable.hpp"

namespace ARDUINOJSON_NAMESPACE {

// Forward declarations.
class ArrayRef;
class Object;

// Contains the methods shared by Variant and VariantConst
template <typename TData>
class VariantProxy {
 public:
  // Tells wether the variant has the specified type.
  // Returns true if the variant has type type T, false otherwise.
  //
  // bool is<char>() const;
  // bool is<signed char>() const;
  // bool is<signed short>() const;
  // bool is<signed int>() const;
  // bool is<signed long>() const;
  // bool is<unsigned char>() const;
  // bool is<unsigned short>() const;
  // bool is<unsigned int>() const;
  // bool is<unsigned long>() const;
  template <typename T>
  FORCE_INLINE typename enable_if<is_integral<T>::value, bool>::type is()
      const {
    return variantIsInteger(_data);
  }
  //
  // bool is<double>() const;
  // bool is<float>() const;
  template <typename T>
  FORCE_INLINE typename enable_if<is_floating_point<T>::value, bool>::type is()
      const {
    return variantIsFloat(_data);
  }
  //
  // bool is<bool>() const
  template <typename T>
  FORCE_INLINE typename enable_if<is_same<T, bool>::value, bool>::type is()
      const {
    return _data && _data->type == JSON_BOOLEAN;
  }
  //
  // bool is<const char*>() const;
  // bool is<char*>() const;
  // bool is<std::string>() const;
  // bool is<String>() const;
  template <typename T>
  FORCE_INLINE typename enable_if<is_same<T, const char *>::value ||
                                      is_same<T, char *>::value ||
                                      IsWriteableString<T>::value,
                                  bool>::type
  is() const {
    return variantIsString(_data);
  }
  //
  // bool is<ArrayRef> const;
  // bool is<const ArrayRef> const;
  template <typename T>
  FORCE_INLINE typename enable_if<
      is_same<typename remove_const<T>::type, ArrayRef>::value, bool>::type
  is() const {
    return variantIsArray(_data);
  }
  //
  // bool is<Object> const;
  // bool is<const Object> const;
  template <typename T>
  FORCE_INLINE
      typename enable_if<is_same<typename remove_const<T>::type, Object>::value,
                         bool>::type
      is() const {
    return variantIsObject(_data);
  }

  FORCE_INLINE bool isNull() const {
    return variantIsNull(_data);
  }

  FORCE_INLINE bool isInvalid() const {
    return _data == 0;
  }

  size_t size() const {
    return objectSize(variantAsObject(_data)) +
           arraySize(variantAsArray(_data));
  }

 protected:
  VariantProxy(TData *data) : _data(data) {}
  TData *_data;
};

// A variant that can be a any value serializable to a JSON value.
//
// It can be set to:
// - a boolean
// - a char, short, int or a long (signed or unsigned)
// - a string (const char*)
// - a reference to a ArrayRef or Object
class Variant : public VariantProxy<VariantData>,
                public VariantBase<Variant>,
                public Visitable {
  typedef VariantProxy<VariantData> proxy_type;
  friend class VariantConst;

 public:
  // Intenal use only
  FORCE_INLINE Variant(MemoryPool *memoryPool, VariantData *data)
      : proxy_type(data), _memoryPool(memoryPool) {}

  // Creates an uninitialized Variant
  FORCE_INLINE Variant() : proxy_type(0), _memoryPool(0) {}

  // set(bool value)
  FORCE_INLINE bool set(bool value) const {
    return variantSetBoolean(_data, value);
  }

  // set(double value);
  // set(float value);
  template <typename T>
  FORCE_INLINE bool set(
      T value,
      typename enable_if<is_floating_point<T>::value>::type * = 0) const {
    return variantSetFloat(_data, static_cast<Float>(value));
  }

  // set(char)
  // set(signed short)
  // set(signed int)
  // set(signed long)
  // set(signed char)
  template <typename T>
  FORCE_INLINE bool set(
      T value,
      typename enable_if<is_integral<T>::value && is_signed<T>::value>::type * =
          0) const {
    return variantSetSignedInteger(_data, value);
  }

  // set(unsigned short)
  // set(unsigned int)
  // set(unsigned long)
  template <typename T>
  FORCE_INLINE bool set(
      T value, typename enable_if<is_integral<T>::value &&
                                  is_unsigned<T>::value>::type * = 0) const {
    return variantSetUnsignedInteger(_data, static_cast<UInt>(value));
  }

  // set(SerializedValue<const char *>)
  FORCE_INLINE bool set(SerializedValue<const char *> value) const {
    return variantSetLinkedRaw(_data, value);
  }

  // set(SerializedValue<std::string>)
  // set(SerializedValue<String>)
  // set(SerializedValue<const __FlashStringHelper*>)
  template <typename T>
  FORCE_INLINE bool set(
      SerializedValue<T> value,
      typename enable_if<!is_same<const char *, T>::value>::type * = 0) const {
    return variantSetOwnedRaw(_data, value, _memoryPool);
  }

  // set(const std::string&)
  // set(const String&)
  template <typename T>
  FORCE_INLINE bool set(
      const T &value,
      typename enable_if<IsString<T>::value>::type * = 0) const {
    return variantSetString(_data, makeString(value), _memoryPool);
  }

  // set(char*)
  template <typename T>
  FORCE_INLINE bool set(
      T *value, typename enable_if<IsString<T *>::value>::type * = 0) const {
    return variantSetString(_data, makeString(value), _memoryPool);
  }

  // set(const char*);
  FORCE_INLINE bool set(const char *value) const {
    return variantSetString(_data, value);
  }

  // for internal use only
  FORCE_INLINE bool set(StringInMemoryPool value) const {
    return variantSetOwnedString(_data,
                                 value.save(_memoryPool));  // TODO: remove?
  }
  FORCE_INLINE bool set(ZeroTerminatedRamStringConst value) const {
    return variantSetString(_data, value.c_str());
  }

  bool set(VariantConst value) const;
  bool set(Variant value) const;

  FORCE_INLINE bool set(ArrayRef array) const;
  FORCE_INLINE bool set(const ArraySubscript &) const;
  FORCE_INLINE bool set(Object object) const;
  template <typename TString>
  FORCE_INLINE bool set(const ObjectSubscript<TString> &) const;

  // Get the variant as the specified type.
  //
  // std::string as<std::string>() const;
  // String as<String>() const;
  template <typename T>
  FORCE_INLINE typename enable_if<!is_same<T, ArrayRef>::value &&
                                      !is_same<T, Object>::value &&
                                      !is_same<T, Variant>::value,
                                  typename VariantAs<T>::type>::type
  as() const {
    return variantAs<T>(_data);
  }
  //
  // ArrayRef as<ArrayRef>() const;
  // const ArrayRef as<const ArrayRef>() const;
  template <typename T>
  FORCE_INLINE typename enable_if<is_same<T, ArrayRef>::value, T>::type as()
      const;
  //
  // Object as<Object>() const;
  // const Object as<const Object>() const;
  template <typename T>
  FORCE_INLINE typename enable_if<is_same<T, Object>::value, T>::type as()
      const;
  //
  // Variant as<Variant> const;
  template <typename T>
  FORCE_INLINE typename enable_if<is_same<T, Variant>::value, T>::type as()
      const {
    return *this;
  }

  template <typename Visitor>
  void accept(Visitor &visitor) const;

  FORCE_INLINE bool operator==(Variant lhs) const {
    return variantEquals(_data, lhs._data);
  }

  FORCE_INLINE bool operator!=(Variant lhs) const {
    return !variantEquals(_data, lhs._data);
  }

  // Change the type of the variant
  //
  // ArrayRef to<ArrayRef>()
  template <typename T>
  typename enable_if<is_same<T, ArrayRef>::value, ArrayRef>::type to() const;
  //
  // Object to<Object>()
  template <typename T>
  typename enable_if<is_same<T, Object>::value, Object>::type to() const;
  //
  // Object to<Variant>()
  template <typename T>
  typename enable_if<is_same<T, Variant>::value, Variant>::type to() const;

 private:
  MemoryPool *_memoryPool;
};

class VariantConst : public VariantProxy<const VariantData>,
                     public VariantBase<VariantConst>,
                     public Visitable {
  typedef VariantProxy<const VariantData> proxy_type;
  friend class Variant;

 public:
  VariantConst() : proxy_type(0) {}
  VariantConst(const VariantData *data) : proxy_type(data) {}
  VariantConst(Variant var) : proxy_type(var._data) {}

  template <typename Visitor>
  void accept(Visitor &visitor) const;

  // Get the variant as the specified type.
  //
  template <typename T>
  FORCE_INLINE typename VariantConstAs<T>::type as() const {
    return variantAs<typename VariantConstAs<T>::type>(_data);
  }

  FORCE_INLINE VariantConst operator[](size_t index) const;

  //
  // const VariantConst operator[](TKey) const;
  // TKey = const std::string&, const String&
  template <typename TString>
  FORCE_INLINE typename enable_if<IsString<TString>::value, VariantConst>::type
  operator[](const TString &key) const {
    return VariantConst(objectGet(variantAsObject(_data), makeString(key)));
  }
  //
  // VariantConst operator[](TKey);
  // TKey = const char*, const char[N], const FlashStringHelper*
  template <typename TString>
  FORCE_INLINE
      typename enable_if<IsString<TString *>::value, VariantConst>::type
      operator[](TString *key) const {
    return VariantConst(objectGet(variantAsObject(_data), makeString(key)));
  }
};
}  // namespace ARDUINOJSON_NAMESPACE
