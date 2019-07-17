/*
 * Routines for Temperature reading. Supports DS18B20 type sensors.
 */

#ifndef TEMP_H
#define TEMP_H

// Data wire is conntec to the Arduino digital pin 2
#define ONE_WIRE_BUS 2

#include <OneWire.h>
#include <DallasTemperature.h>

class Temp {
 public:
  Temp(): 
    one_wire_(ONE_WIRE_BUS),
    sensors_(&one_wire_)
  {}

  void begin() {
    sensors_.begin();
  }

  void poll() {
    sensors_.requestTemperatures();
  }

  float get_f(int index) {
    return sensors_.getTempFByIndex(index);
  }

  float get_c(int index) {
    return sensors_.getTempCByIndex(index);
  }

 private:
  OneWire one_wire_;
  DallasTemperature sensors_;
};

#endif // TEMP_H
