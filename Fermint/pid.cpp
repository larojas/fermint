#include "pid.h"

PID::PID()
  : sv_(0), sum_(0), log_pos_(0), last_ts_(0)
{
  for (PID_LOG_IDX i = 0; i < PID_LOG_SZ; ++i) {
    log_[i].val = val_t(0);
    log_[i].ts = 0UL;
  }
}

void PID::loop(PID::ts_t ts, PID::val_t pv) {
  if (ts - last_ts_ >= PID_LOG_MIN_MS) {
    
    log_[log_pos_].ts = ts;
    log_[log_pos_].val = pv;
    if (++log_pos_ >= PID_LOG_SZ) log_pos_ = 0;
    last_ts_ = ts;
  }
}
