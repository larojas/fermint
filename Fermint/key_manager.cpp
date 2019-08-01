#include "key_manager.h"
#include "menu.h"

KeyManager::KeyManager()
  : next_action_millis_(0), key_down_type_(KEY_NONE),
    active_menu_(nullptr)
{}

void KeyManager::key_up(unsigned long now) {
  if (key_down_type_ != KEY_NONE) {
    active_menu_->on_key(KEY_UP, key_down_type_);
    key_down_type_ = KEY_NONE;
  }
}

void KeyManager::loop() {
  if (active_menu_ == nullptr) return;
  unsigned long now = millis();

  if (key_down_type_ != KEY_NONE) {
    // We have a key down from previous cycle. Check if it's still down, in
    // which case we ignore any other key.
    if (is_down(key_down_type_)) {
      // prior key still pressed
      if (now >= next_action_millis_) {
        next_action_millis_ += REPEAT_INTERVAL_MS;
        active_menu_->on_key(KEY_REPEAT, key_down_type_);
      }
    } else {
      // button is released
      key_up(now);
    }
  } else {
    // check all keys
    if (is_down(KEY_LEFT)) key_down_type_ = KEY_LEFT;
    else if (is_down(KEY_RIGHT)) key_down_type_ = KEY_RIGHT;
    else if (is_down(KEY_ENTER)) key_down_type_ = KEY_ENTER;
    if (key_down_type_ != KEY_NONE) {
      next_action_millis_ = now + REPEAT_DELAY_MS;
      active_menu_->on_key(KEY_DOWN, key_down_type_);
    }
  }
}
