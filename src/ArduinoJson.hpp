// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "ArduinoJson/Namespace.hpp"

#include "ArduinoJson/Array.hpp"
#include "ArduinoJson/Object.hpp"
#include "ArduinoJson/Variant.hpp"

#include "ArduinoJson/DynamicJsonDocument.hpp"
#include "ArduinoJson/StaticJsonDocument.hpp"

#include "ArduinoJson/ArrayImpl.hpp"
#include "ArduinoJson/ArraySubscript.hpp"
#include "ArduinoJson/Data/VariantAsImpl.hpp"
#include "ArduinoJson/ObjectImpl.hpp"
#include "ArduinoJson/ObjectSubscript.hpp"
#include "ArduinoJson/VariantImpl.hpp"

#include "ArduinoJson/Json/JsonDeserializer.hpp"
#include "ArduinoJson/Json/JsonSerializer.hpp"
#include "ArduinoJson/Json/PrettyJsonSerializer.hpp"
#include "ArduinoJson/MsgPack/MsgPackDeserializer.hpp"
#include "ArduinoJson/MsgPack/MsgPackSerializer.hpp"

namespace ArduinoJson {
typedef ARDUINOJSON_NAMESPACE::Array JsonArray;
typedef ARDUINOJSON_NAMESPACE::ArrayConst JsonArrayConst;
using ARDUINOJSON_NAMESPACE::DeserializationError;
using ARDUINOJSON_NAMESPACE::DynamicJsonDocument;
typedef ARDUINOJSON_NAMESPACE::Integer JsonInteger;
typedef ARDUINOJSON_NAMESPACE::Float JsonFloat;
using ARDUINOJSON_NAMESPACE::JsonKey;
using ARDUINOJSON_NAMESPACE::JsonUInt;
typedef ARDUINOJSON_NAMESPACE::Pair JsonPair;
typedef ARDUINOJSON_NAMESPACE::Variant JsonVariant;
typedef ARDUINOJSON_NAMESPACE::VariantConst JsonVariantConst;
typedef ARDUINOJSON_NAMESPACE::Object JsonObject;
typedef ARDUINOJSON_NAMESPACE::ObjectConst JsonObjectConst;
using ARDUINOJSON_NAMESPACE::serialized;
using ARDUINOJSON_NAMESPACE::StaticJsonDocument;
}  // namespace ArduinoJson
