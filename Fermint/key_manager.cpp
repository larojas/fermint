#include "key_manager.h"
#include "menu.h"

KeyManager::KeyManager(const uint8_t* key_pin_map)
  : map_(key_pin_map), key_down_millis_(0), key_down_type_(KEY_NONE),
    active_menu_(nullptr)
{}

void KeyManager::key_down(KeyType type, unsigned long now) {
  key_down_type_ = type;
  key_down_millis_ = now;
  active_menu_->on_key(KEY_DOWN, type, 0UL);
}

void KeyManager::key_up(unsigned long now) {
  if (key_down_type_ != KEY_NONE) {
    active_menu_->on_key(KEY_UP, key_down_type_, 0UL);
    key_down_type_ = KEY_NONE;
  }
}

void KeyManager::loop() {
  if (active_menu_ == nullptr) return;
  unsigned long now = millis();

  // sweep through our pins
  for (uint8_t i=0; i < NUM_KEYS; ++i) {
    if (map_[i] == 0) continue;
    uint8_t state = digitalRead(map_[i]);
    KeyType probe_key = KeyType(i);
    if (state) {
      // button is pressed
      if (probe_key != key_down_type_) {
	// new key has been pressed
        key_up(now);
	key_down(probe_key, now);
      } else {
	// prior key still pressed
	unsigned long delta = now - key_down_millis_;
	if (delta > REPEAT_DELAY_MS) {
	  active_menu_->on_key(KEY_DOWN, key_down_type_, delta - REPEAT_DELAY_MS);
	  
	}
      }
    } else {
      // button is released
      if (probe_key == key_down_type_) {
	key_up(now);
      }
    }
  }
}
