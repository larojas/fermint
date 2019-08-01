#ifndef MENU_H
#define MENU_H

#include "util.h"
#include "key_manager.h"

using Util::dim;
class Oled;

class Menu {
 public:
  virtual void on_key(KeyPos pos, KeyType type) {}
  static void begin(Oled* oled) { oled_ = oled; }
  static Oled& oled() { return *oled_; }
 private:
  static Oled* oled_;

};

template<class T> class NumberMenu : public Menu {
 public:
  NumberMenu(T initial);
  void on_key(KeyPos pos, KeyType type) override;

 private:
  T value_;
  unsigned long last_millis_;
  KeyPos pos_;
  KeyType type_;
};


class OptionsMenu : public Menu {
 public:
  OptionsMenu(const char** options, uint8_t sz);
  void on_key(KeyPos pos, KeyType type) override;

 private:
  const char** options_;
  uint8_t sz_;
  uint8_t selected_;
};

class PvDisplayMenu : public Menu {
 public:
  PvDisplayMenu() {}
  //TODO: finish
};

#endif // MENU_H
