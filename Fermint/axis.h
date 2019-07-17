#ifndef AXIS_H
#define AXIS_H

#include "util.h"

class Oled; // forward declaration
using Util::dim;

#define TICK_SZ 4

class Axis {
 public:
  Axis(dim x, dim y, dim len, Oled& oled, const char* fmt=nullptr);
  void set_scale(float min, float max, uint8_t num_ticks);
  float px_per_unit() const { return float(len_ - 1) / float(max_ - min_); }
  float scale_min() const { return min_; }
  void draw(bool is_vertical=true);

 private:
  void tickers();
  const dim x_;
  const dim y_;
  const dim len_;
  Oled& oled_;
  const char* fmt_;
  float min_;
  float max_;
  uint8_t num_ticks_;
  boolean vertical_;
};

#endif // AXIS_H
