#ifndef PV_DISPLAY_H
#define PV_DISPLAY_H

#define SELECTED_SZ 36

#include "util.h"

class Oled;
using Util::dim;

class PvDisplay {
 public:
  PvDisplay(const char* name, dim x, dim y, Oled& oled);
  void draw_value(const char* val, bool selected=false);
 private:
  const char* const name_;
  dim x_;
  dim y_;
  Oled& oled_;
};

#endif // PV_DISPLAY_H
