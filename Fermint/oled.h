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

#include "util.h"
using Util::dim;

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
  void clear(bool clearDisplay=false);
  void print_at(const char* str, dim x, dim y);
  void print_boxed(const char* str, dim x, dim y, dim w, dim h, OledColor fg);
  void print(const char* str);
  void print_next(const char* str);
  void set_font(OledFont);
  dim get_font_height();
  void vline(dim x, dim y, dim len);
  void hline(dim x, dim y, dim len);
  void line(dim x1, dim y1, dim x2, dim y2);
  void set_pixel(dim x, dim y);
  void mode(OledColor);
  void debug_display(bool enable);
  void show();

 private:
  dim pitch_;
  dim row_;
  dim col_;
  bool debug_;
};

#endif // OLED_H
