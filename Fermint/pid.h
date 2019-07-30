#ifndef PID_H
#define PID_H

#include <Arduino.h>

// Max: 128 (IDX is 8-bit)
#define PID_LOG_SZ 10
#define PID_LOG_IDX uint8_t
// Min interval between samples
#define PID_LOG_MIN_MS 1000

/*
 *  The PID class only does integer math, but you can use it as a rudimentary
 *  fixed point by changing the unit (e.g. 100ths of a degree).
 */
class PID {
 public:
  // -16k to +16k
  typedef int val_t;
  typedef int sum_t;
  typedef unsigned long ts_t;
  struct Entry {
    ts_t ts;
    val_t val;
    Entry() : ts(0), val(0) {}
  };

  PID();
  void loop(ts_t ts, val_t pv);

 private:
  val_t sv_;
  sum_t sum_;
  Entry log_[PID_LOG_SZ];
  PID_LOG_IDX log_pos_;
  ts_t last_ts_;
};

#endif // PID_H
