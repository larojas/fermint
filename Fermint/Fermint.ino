/*

  Fermint - Advanced temperature control for fermenting.

  Optimized for driving on-off cool/heat equipment.
  (read: cheap chest freezer)

  Uses PID to compensate for a lagging process variable
  (the liquid temperature lags behind the freezer air
  temperature, and might never fully converge since
  fermentation is exothermic).

*/

#define LOOP_DELAY_MS 100
#define GRAPH_LEFT 21
#define PLOT_MIN 70
#define PLOT_MAX 90
#define AXIS_TICKS 5
#define PV_SPACE 45
#define PIN_TOGGLE_UP 3
#define POLL_INTERVAL_MS 60000

#include "temp.h"
#include "oled.h"
#include "graph.h"
#include "pv_display.h"
#include "menu.h"

Temp temp;
Oled oled;
Graph graph(GRAPH_LEFT, 34, 127 - GRAPH_LEFT, 83, oled);
PvDisplay pv[] = {{"PV1", 0, 0, oled},
		  {"PV2", PV_SPACE, 0, oled},
		  {"PV3", PV_SPACE * 2, 0, oled}};
#define PV_CNT (sizeof(pv)/sizeof(PvDisplay))
uint8_t toggle_up_state = 1;
uint8_t active = 0;
unsigned long last_poll;

void setup(void) {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting!");
  temp.begin();
  oled.begin();
  show_splash();
  graph.v_axis().set_scale(PLOT_MIN, PLOT_MAX, AXIS_TICKS);
  graph.begin();
  Menu::begin(&oled);
  oled.show();

  pinMode(PIN_TOGGLE_UP, INPUT_PULLUP);
}

void show_splash() {
  oled.set_font(FONT_SMALL);
  oled.print_at("Chongolele", 30, 9);
  oled.show();
  delay(3000);
  oled.clear();
}

void show_temps() {
  char temp_str[] = "Temp: 999.9f";
  /*
  for (uint8_t i = 0; i < PV_CNT; ++i) {
    float tf = temp.get_f(i);
    sprintf(temp_str, "%3.1f", tf > -100? tf : 0.0);
    pv[i].draw_value(temp_str);
  }
  */
  
  float tf = temp.get_f(0);
  sprintf(temp_str, "%05.1f", tf > -100? tf : 0.0);
  pv[0].draw_value(temp_str, active == 0);
  pv[1].draw_value("000.0", active == 1);
  pv[2].draw_value("123.4", active == 2);
  oled.show();
}

void loop(void) {
  uint8_t toggle = digitalRead(PIN_TOGGLE_UP);
  if (toggle != toggle_up_state) {
    if (toggle) {
      active++;
      if (active >= 3) active = 0;
      show_temps();
    }
    toggle_up_state = toggle;
  }

  unsigned long time = millis();
  if (time > last_poll + POLL_INTERVAL_MS) {
    if (time > last_poll + 2 * POLL_INTERVAL_MS) {
      // if too far behind, just match current time
      last_poll = time;
    } else {
      // try to keep up
      last_poll += POLL_INTERVAL_MS;
    }
    temp.poll();
    float temp_f = temp.get_f(0);
    show_temps();
    graph.plot(temp_f);
  }
  //delay(LOOP_DELAY_MS);
}
