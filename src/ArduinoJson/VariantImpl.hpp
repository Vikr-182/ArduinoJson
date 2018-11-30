// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Configuration.hpp"
#include "Numbers/parseFloat.hpp"
#include "Numbers/parseInteger.hpp"
#include "Variant.hpp"

#include <string.h>  // for strcmp

namespace ARDUINOJSON_NAMESPACE {

inline bool Variant::set(Array array) const {
  return to<Array>().copyFrom(array);
}

inline bool Variant::set(const ArraySubscript& value) const {
  return set(value.as<Variant>());
}

inline bool Variant::set(Object object) const {
  return to<Object>().copyFrom(object);
}

template <typename TString>
inline bool Variant::set(const ObjectSubscript<TString>& value) const {
  return set(value.template as<Variant>());
}

inline bool Variant::set(VariantConst value) const {
  return variantCopy(_data, value._data, _memoryPool);
}

inline bool Variant::set(Variant value) const {
  return variantCopy(_data, value._data, _memoryPool);
}

template <typename T>
inline typename enable_if<is_same<T, Array>::value, T>::type Variant::as()
    const {
  return Array(_memoryPool, variantAsArray(_data));
}

template <typename T>
inline typename enable_if<is_same<T, Object>::value, T>::type Variant::as()
    const {
  return Object(_memoryPool, variantAsObject(_data));
}

template <typename T>
inline typename enable_if<is_same<T, Array>::value, Array>::type Variant::to()
    const {
  return Array(_memoryPool, variantToArray(_data));
}

template <typename T>
typename enable_if<is_same<T, Object>::value, Object>::type Variant::to()
    const {
  return Object(_memoryPool, variantToObject(_data));
}

template <typename T>
typename enable_if<is_same<T, Variant>::value, Variant>::type Variant::to()
    const {
  variantSetNull(_data);
  return *this;
}

template <typename Visitor>
inline void Variant::accept(Visitor& visitor) const {
  return VariantConst(_data).accept(visitor);
}

template <typename Visitor>
inline void VariantConst::accept(Visitor& visitor) const {
  if (!_data) return visitor.visitNull();

  switch (_data->type) {
    case JSON_FLOAT:
      return visitor.visitFloat(_data->content.asFloat);

    case JSON_ARRAY:
      return visitor.visitArray(ArrayConst(&_data->content.asArray));

    case JSON_OBJECT:
      return visitor.visitObject(ObjectConst(&_data->content.asObject));

    case JSON_LINKED_STRING:
    case JSON_OWNED_STRING:
      return visitor.visitString(_data->content.asString);

    case JSON_OWNED_RAW:
    case JSON_LINKED_RAW:
      return visitor.visitRawJson(_data->content.asRaw.data,
                                  _data->content.asRaw.size);

    case JSON_NEGATIVE_INTEGER:
      return visitor.visitNegativeInteger(_data->content.asInteger);

    case JSON_POSITIVE_INTEGER:
      return visitor.visitPositiveInteger(_data->content.asInteger);

    case JSON_BOOLEAN:
      return visitor.visitBoolean(_data->content.asInteger != 0);

    default:
      return visitor.visitNull();
  }
}

inline VariantConst VariantConst::operator[](size_t index) const {
  return ArrayConst(variantAsArray(_data))[index];
}

}  // namespace ARDUINOJSON_NAMESPACE
