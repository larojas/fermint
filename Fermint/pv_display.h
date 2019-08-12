#ifndef PV_DISPLAY_H
#define PV_DISPLAY_H

#define SELECTED_SZ 36

#include "util.h"

class Oled;
using Util::dim;

class PvDisplay {
 public:
  PvDisplay(const char* name, dim x, dim y);
  void set(float val);
  void draw_value(bool selected, Oled& oled);
 private:
  const char* const name_;
  dim x_;
  dim y_;
  float val_;
};

#endif // PV_DISPLAY_H
