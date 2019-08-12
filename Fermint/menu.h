#ifndef MENU_H
#define MENU_H

#include "util.h"
#include "key_manager.h"

using Util::dim;
class Oled;
class PvDisplay;

class Menu {
 public:
  virtual void on_key(KeyPos pos, KeyType type) = 0;
  static void begin(Menu* active, Oled* oled);
  static Oled& oled() { return *oled_; }
  static Menu& active() { return *active_; }
 protected:
  static Menu* active_;
 private:
  static Oled* oled_;
};

template<class T> class NumberMenu : public Menu {
 public:
  NumberMenu(T initial, T delta, T min, T max);
  void on_key(KeyPos pos, KeyType type) override;

 private:
  virtual void change_handler(T new_value, T old_value);
  T value_;
  T delta_;
  T min_;
  T max_;
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
  PvDisplayMenu(PvDisplay* displays, uint8_t sz);
  void on_key(KeyPos pos, KeyType type) override;
  void draw();
 private:
  PvDisplay* displays_;
  uint8_t sz_;
  uint8_t focus_;
};

#endif // MENU_H
