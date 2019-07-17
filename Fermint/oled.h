/*
 *  OLED handling routines.
 *  Currently supports SSD1327 128x128 OLED controller.
 *  Requires u8g2.
 */

#ifndef OLED_H
#define OLED_H

////////////////////////////////////////////////////
// Begin user configurable section
////////////////////////////////////////////////////

#define OLED_DC_PIN 7
#define OLED_RESET_PIN 8
#define OLED_CS_PIN 10

#define OLED_DEBUG_ENABLE

////////////////////////////////////////////////////
// End user configurable section
////////////////////////////////////////////////////

#define OLED_DEBUG_STR_SZ 18
#ifdef OLED_DEBUG_ENABLE
#  define OLED_DEBUG(...) \
   snprintf(OLED_DEBUG_STR, OLED_DEBUG_STR_SZ, __VA_ARGS__)
extern char OLED_DEBUG_STR[];
#else
#  define OLED_DEBUG(...)
#endif // OLED_DEBUG_ENABLE

enum OledFont {
  FONT_AXIS,
  FONT_BIGNUM,
  FONT_SMALL,
  FONT_BIG
};

enum OledColor {
  OLED_BLACK=0,
  OLED_WHITE=1
};

class Oled {
 public:

  Oled();
  void begin();
  void print_at(const char* str, uint8_t x, uint8_t y);
  void print(const char* str);
  void print_next(const char* str);
  void set_font(OledFont);
  uint8_t get_font_height();
  void vline(uint8_t x, uint8_t y, uint8_t len);
  void hline(uint8_t x, uint8_t y, uint8_t len);
  void line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  void set_pixel(uint8_t x, uint8_t y);
  void mode(OledColor);
  void debug_display(bool enable);
  void show();

 private:
  uint8_t pitch_;
  uint8_t row_;
  uint8_t col_;
  bool debug_;
};

#endif // OLED_H
