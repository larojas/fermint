#include "pv_display.h"
#include "oled.h"

PvDisplay::PvDisplay(const char* name, dim x, dim y)
  : name_(name), x_(x), y_(y), val_(0.0)
{}

void PvDisplay::draw_value(bool selected, Oled& oled) {
  oled.set_font(FONT_SMALL);
  dim y_bottom = y_ + oled.get_font_height();
  oled.print_at(name_, x_, y_bottom);
  oled.set_font(FONT_BIGNUM);
  y_bottom += oled.get_font_height();
  oled.print_at(Util::print_float(val_), x_, y_bottom);
  oled.mode(selected ? OLED_WHITE : OLED_BLACK);
  oled.hline(x_, y_bottom + 2, SELECTED_SZ);
}

void PvDisplay::set(float val) {
  val_ = val;
}
