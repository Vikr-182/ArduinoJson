// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Polyfills/type_traits.hpp"
#include "../Variant/VariantData.hpp"

namespace ARDUINOJSON_NAMESPACE {

typedef conditional<sizeof(void*) <= 2, int8_t, int16_t>::type VariantSlotDiff;

struct VariantSlot {
  VariantData value;
  VariantSlotDiff next;
  const char* key;

  // Must be a POD!
  // - no constructor
  // - no destructor
  // - no virtual
  // - no inheritance

  VariantSlot* getNext() {
    return next ? this + next : 0;
  }

  const VariantSlot* getNext() const {
    return const_cast<VariantSlot*>(this)->getNext();
  }

  VariantSlot* getNext(size_t distance) {
    VariantSlot* slot = this;
    while (distance--) {
      if (!slot->next) return 0;
      slot += slot->next;
    }
    return slot;
  }

  VariantSlot* getPrev(VariantSlot* head) {
    while (head) {
      VariantSlot* nxt = head->getNext();
      if (nxt == this) return head;
      head = nxt;
    }
    return head;
  }

  const VariantSlot* getNext(size_t distance) const {
    return const_cast<VariantSlot*>(this)->getNext(distance);
  }

  void setNext(VariantSlot* slot) {
    this->next = VariantSlotDiff(slot ? slot - this : 0);
  }

  void attachTo(VariantSlot* tail) {
    tail->next = VariantSlotDiff(this - tail);
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
