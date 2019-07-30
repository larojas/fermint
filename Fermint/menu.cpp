#include "menu.h"

/////////////// Menu ///////////////
/*static*/
Oled* Menu::oled_;

/////////////// NumberMenu ///////////////
template<class T>
NumberMenu<T>::NumberMenu(T initial)
  : value_(initial), last_millis_(0),
    pos_(KEY_UP), type_(KEY_NONE)
{}

template<class T>
bool NumberMenu<T>::on_key(KeyPos pos, KeyType type, unsigned long len) {
  if (pos == KEY_UP) {
    // act only on key_up event
    switch(type) {
    case KEY_LEFT:
      value_ -= value_ > 0 ? 1 : 0;
      return true;
    case KEY_RIGHT:
      ++value_;
      return true;
    case KEY_ENTER:
    case KEY_NONE:
      break;
    }
  }
  return false;
}

/////////////// OptionsMenu ///////////////
OptionsMenu::OptionsMenu(const char** options, uint8_t sz)
  : options_(options), sz_(sz), selected_(0)
{}

bool OptionsMenu::on_key(KeyPos pos, KeyType type, unsigned long len) {
  if (pos == KEY_UP) {
    // act only on key up event
    switch(type) {
    case KEY_LEFT:
      selected_ = selected_ > 0? selected_ - 1 : sz_ - 1;
      return true;
    case KEY_RIGHT:
      ++selected_;
      if (selected_ >= sz_) selected_ = 0;
      return true;
    case KEY_ENTER:
    case KEY_NONE:
      break;
    }
  }
  return false;
}
