#include "menu.h"

template<class T>
NumberMenu<T>::NumberMenu(T initial, Oled& oled)
  : value_(initial), oled_(oled), last_millis_(0),
    pos_(KEY_UP), type_(KEY_NONE)
{}

template<class T>
bool NumberMenu<T>::on_key(KeyPos pos, KeyType type, unsigned long len) {
  return false;
}
