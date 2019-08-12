#include "util.h"

static char print_str[PRINT_STR_LEN];

namespace Util {

  const char* print_float(float val) {
    sprintf(print_str, "%05.1f", val);
    return print_str;
  }

  const char* print_int(int val) {
    sprintf(print_str, "%03d", val);
    return print_str;
  }

} // namespace Util;
