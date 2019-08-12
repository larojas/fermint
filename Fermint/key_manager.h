#ifndef KEY_MANAGER_H
#define KEY_MANAGER_H

#include <Arduino.h>

// Delay before entering repeat mode
#define REPEAT_DELAY_MS 1000
// Interval for each repetition in repeat mode
#define REPEAT_INTERVAL_MS 250

// One entry here for each KeyType member (except KEY_NONE)
// For non-connected keys, use 0.
#define PIN_KEY_LEFT 0
#define PIN_KEY_RIGHT 3
#define PIN_KEY_ENTER 0

enum KeyPos {
  KEYPOS_UP,
  KEYPOS_DOWN,
  KEYPOS_REPEAT
};

// Has to correspond to the #defined values above (except for KEY_NONE).
enum KeyType {
  KEY_LEFT,
  KEY_RIGHT,
  KEY_ENTER,
  KEY_NONE
};

class KeyManager {
 public:
  static void loop(unsigned long now);
  static void begin();
 private:
  static void key_up();
  static bool is_down(int pin) { return pin > 0 ? digitalRead(pin) == LOW : false; }
  static int pin_for_key(KeyType key);
  static unsigned long next_action_millis_;
  static unsigned long last_key_millis_;
  static KeyType key_down_type_;
};

#endif // KEY_MANAGER_H
