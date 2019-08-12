#include "key_manager.h"
#include "menu.h"

/* static */ KeyType KeyManager::key_down_type_;
/* static */ unsigned long KeyManager::next_action_millis_;
/* static */ unsigned long KeyManager::last_key_millis_;

/* static */
void KeyManager::key_up() {
  if (key_down_type_ != KEY_NONE) {
    Menu::active().on_key(KEYPOS_UP, key_down_type_);
    key_down_type_ = KEY_NONE;
  }
}

/* static */
int KeyManager::pin_for_key(KeyType key) {
  switch (key) {
  case KEY_LEFT: return PIN_KEY_LEFT;
  case KEY_RIGHT: return PIN_KEY_RIGHT;
  case KEY_ENTER: return PIN_KEY_ENTER;
  default: return 0;
  }
}

/* static */
void KeyManager::begin() {
  if (PIN_KEY_LEFT > 0) pinMode(PIN_KEY_LEFT, INPUT_PULLUP);
  if (PIN_KEY_RIGHT > 0) pinMode(PIN_KEY_RIGHT, INPUT_PULLUP);
  if (PIN_KEY_ENTER > 0) pinMode(PIN_KEY_ENTER, INPUT_PULLUP);
  next_action_millis_ = 0;
  last_key_millis_ = 0;
  key_down_type_ = KEY_NONE;
}

/* static */
void KeyManager::loop(unsigned long now) {
  if (now == 0) now = millis();

  if (key_down_type_ != KEY_NONE) {
    // We have a key down from previous cycle. Check if it's still down, in
    // which case we ignore any other key.
    if (is_down(pin_for_key(key_down_type_))) {
      // prior key still pressed
      if (now >= next_action_millis_) {
        next_action_millis_ += REPEAT_INTERVAL_MS;
        Menu::active().on_key(KEYPOS_REPEAT, key_down_type_);
      }
    } else {
      // button is released
      key_up();
      last_key_millis_ = now;
    }
  } else {
    // check all keys
    if (is_down(PIN_KEY_LEFT)) key_down_type_ = KEY_LEFT;
    else if (is_down(PIN_KEY_RIGHT)) key_down_type_ = KEY_RIGHT;
    else if (is_down(PIN_KEY_ENTER)) key_down_type_ = KEY_ENTER;
    if (key_down_type_ != KEY_NONE) {
      next_action_millis_ = now + REPEAT_DELAY_MS;
      Menu::active().on_key(KEYPOS_DOWN, key_down_type_);
    }
  }
}
