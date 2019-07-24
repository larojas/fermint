#ifndef KEY_MANAGER_H
#define KEY_MANAGER_H

#include <Arduino.h>

// Delay before a key is repeated
#define REPEAT_DELAY_MS 1000


class Menu;

enum KeyPos {
  KEY_UP,
  KEY_DOWN
};

enum KeyType {
  KEY_LEFT,
  KEY_RIGHT,
  KEY_ENTER,
  KEY_NONE = 99
};

#define NUM_KEYS (sizeof(KeyType)/sizeof(KEY_NONE) - 1)

class KeyManager {
 public:
  KeyManager(const uint8_t* key_pin_map);
  void loop();
 private:
  void key_down(KeyType type, unsigned long now);
  void key_up(unsigned long now);
  
  const uint8_t* map_;
  unsigned long key_down_millis_;
  unsigned long last_action_millis_;
  KeyType key_down_type_;
  Menu* active_menu_;
};

#endif // KEY_MANAGER_H
