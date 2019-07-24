#ifndef MENU_H
#define MENU_H

#include "util.h"
#include "key_manager.h"

using Util::dim;
class Oled;

class Menu {
 public:
  virtual void on_key(KeyPos pos, KeyType type, unsigned long len) {}
  virtual void on_loop() {}
};

template<class T> class NumberMenu : public Menu {
 public:
  NumberMenu(T initial, Oled& oled);
  bool on_key(KeyPos pos, KeyType type, unsigned long len) override;

 private:
  T value_;
  Oled& oled_;
  unsigned long last_millis_;
  KeyPos pos_;
  KeyType type_;
};

#endif // MENU_H
