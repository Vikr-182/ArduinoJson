// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "ArduinoJson/Namespace.hpp"

#include "ArduinoJson/Array.hpp"
#include "ArduinoJson/JsonObject.hpp"
#include "ArduinoJson/JsonVariant.hpp"

#include "ArduinoJson/DynamicJsonDocument.hpp"
#include "ArduinoJson/StaticJsonDocument.hpp"

#include "ArduinoJson/ArrayImpl.hpp"
#include "ArduinoJson/ArraySubscript.hpp"
#include "ArduinoJson/Data/VariantAsImpl.hpp"
#include "ArduinoJson/JsonObjectImpl.hpp"
#include "ArduinoJson/JsonObjectSubscript.hpp"
#include "ArduinoJson/JsonVariantImpl.hpp"

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
using ARDUINOJSON_NAMESPACE::JsonFloat;
using ARDUINOJSON_NAMESPACE::JsonInteger;
using ARDUINOJSON_NAMESPACE::JsonKey;
using ARDUINOJSON_NAMESPACE::JsonObject;
using ARDUINOJSON_NAMESPACE::JsonObjectConst;
using ARDUINOJSON_NAMESPACE::JsonPair;
using ARDUINOJSON_NAMESPACE::JsonUInt;
using ARDUINOJSON_NAMESPACE::JsonVariant;
using ARDUINOJSON_NAMESPACE::JsonVariantConst;
using ARDUINOJSON_NAMESPACE::serialized;
using ARDUINOJSON_NAMESPACE::StaticJsonDocument;
}  // namespace ArduinoJson
