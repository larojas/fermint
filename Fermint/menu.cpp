#include "menu.h"
#include "pv_display.h"
#include "oled.h"

/////////////// Menu ///////////////
/*static*/
Oled* Menu::oled_;
/*static*/
Menu* Menu::active_;
/*static*/
void Menu::begin(Menu* active, Oled* oled) {
  active_ = active;
  oled_ = oled;
}


/////////////// NumberMenu ///////////////
template<class T>
NumberMenu<T>::NumberMenu(T initial, T delta, T min, T max)
  : value_(initial), delta_(delta), min_(min), max_(max)
{}

template<class T>
void NumberMenu<T>::on_key(KeyPos pos, KeyType type) {
  if (pos == KEYPOS_DOWN || pos == KEYPOS_REPEAT) {
    T old = value_;
    if (type == KEY_LEFT) {
      value_ = value_ > delta_ ? value_ - delta_ : min_;
    } else if (type == KEY_RIGHT) {
      value_ = max_ - value_ > delta_ ? value_ + delta_ : max_;
    }
    change_handler(value_, old);
  }
}



/////////////// OptionsMenu ///////////////
OptionsMenu::OptionsMenu(const char** options, uint8_t sz)
  : options_(options), sz_(sz), selected_(0)
{}

void OptionsMenu::on_key(KeyPos pos, KeyType type) {
  if (pos == KEYPOS_UP) {
    // act only on key up event
    if (type == KEY_LEFT) {
      selected_ = selected_ > 0? selected_ - 1 : sz_ - 1;
    } else if (type == KEY_RIGHT) {
      ++selected_;
      if (selected_ >= sz_) selected_ = 0;
    }
  }
}


/////////////// PvDisplayMenu ///////////////
PvDisplayMenu::PvDisplayMenu(PvDisplay* displays, uint8_t sz)
  : displays_(displays), sz_(sz), focus_(0)
{}

void PvDisplayMenu::on_key(KeyPos pos, KeyType type) {
  if (pos == KEYPOS_UP) {
    if (type == KEY_RIGHT) {
      focus_ = focus_ + 1 >= sz_? 0 : focus_ + 1;
    } else if (type == KEY_LEFT) {
      focus_ = focus_ > 0 ? focus_ - 1 : sz_ - 1;
    }
    draw();
    oled().show();
  }
}

void PvDisplayMenu::draw() {
  for (uint8_t i = 0; i < sz_; ++i) {
    displays_[i].draw_value(focus_ == i, oled());
  }
}
