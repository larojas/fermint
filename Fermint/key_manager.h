#ifndef KEY_MANAGER_H
#define KEY_MANAGER_H

#include <Arduino.h>

// Delay before a key is repeated
#define REPEAT_DELAY_MS 1000
// Interval for repeated actions
#define REPEAT_INTERVAL_MS 250

class Menu;

enum KeyPos {
  KEY_UP,
  KEY_DOWN,
  KEY_REPEAT
};

// Here you define the digital pin where the buttons are connected.
enum KeyType {
  KEY_LEFT=0,
  KEY_RIGHT=3,
  KEY_ENTER=0,
  KEY_NONE=0
};

class KeyManager {
 public:
  KeyManager();
  void loop();
 private:
  void key_up(unsigned long now);
  bool is_down(int pin) { return digitalRead(pin) == LOW; }
  
  unsigned long next_action_millis_;
  KeyType key_down_type_;
  Menu* active_menu_;
};

#endif // KEY_MANAGER_H
