#include "pv_display.h"
#include "oled.h"

PvDisplay::PvDisplay(const char* name, dim x, dim y, Oled& oled)
  : name_(name), x_(x), y_(y), oled_(oled)
{}

void PvDisplay::draw_value(const char* val, bool selected) {
  oled_.set_font(FONT_SMALL);
  dim y_bottom = y_ + oled_.get_font_height();
  oled_.print_at(name_, x_, y_bottom);
  oled_.set_font(FONT_BIGNUM);
  y_bottom += oled_.get_font_height();
  oled_.print_at(val, x_, y_bottom);
  if (selected) {
    oled_.mode(OLED_WHITE);
  } else {
    oled_.mode(OLED_BLACK);
  }
  oled_.hline(x_, y_bottom + 2, SELECTED_SZ);
}
