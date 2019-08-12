#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>

// Make sure all your print_*() numbers fit in this many bytes (incl. terminator).
#define PRINT_STR_LEN 10

namespace Util {
  // Dimension type: for our 128x128 oled, an unsigned byte is enough.
  typedef uint8_t dim;

  // Printing functions. Caution: not reentrant. Use immediately (string is shared).
  const char* print_float(float val);
  const char* print_int(int val);

} // namespace Util;
#endif // UTIL_H
