#include "axis.h"
#include "oled.h"

Axis::Axis(dim x, dim y, dim len, Oled& oled, const char* fmt)
  : x_(x), y_(y), len_(len), oled_(oled),
    min_(0), max_(0), num_ticks_(0)
{
  if (fmt == nullptr) {
    fmt_ = "3.1f";
  } else {
    fmt_ = fmt;
  }
}

void Axis::set_scale(float min, float max, uint8_t num_ticks) {
  min_ = min;
  max_ = max;
  num_ticks_ = num_ticks;
}

void Axis::draw(bool is_vertical) {
  if (is_vertical) {
    oled_.vline(x_ - 1, y_, len_);
  } else {
    oled_.hline(x_, y_, len_);
  }
  tickers();
}

void Axis::tickers() {
  dim px_int = (len_ - 1) / (num_ticks_ - 1);
  //dim px_mod = (len_ - 1) % (num_ticks_ - 1);

  dim tk_int = (max_ - min_) / (num_ticks_ - 1);
  //dim tk_mod = (max_ - min_) % (num_ticks_ - 1);

  oled_.set_font(FONT_AXIS);
  uint8_t adj_y = oled_.get_font_height() >> 1;
  char ticker_str[] = "000";

  for (uint8_t i = 0; i < num_ticks_; ++i) {
    dim y = y_ + len_ - (i * px_int);
    uint8_t ticker = min_ + (i * tk_int);
    oled_.hline(x_ - TICK_SZ, y, TICK_SZ);
    sprintf(ticker_str, "%3d", ticker);
    oled_.print_at(ticker_str, 0, y + adj_y);
  }
}

