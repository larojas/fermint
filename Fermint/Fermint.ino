/*

  Fermint - Advanced temperature control for fermenting.

  Optimized for driving on-off cool/heat equipment.
  (read: cheap chest freezer)

  Uses PID to compensate for a lagging process variable
  (the liquid temperature lags behind the freezer air
  temperature, and might never fully converge since
  fermentation is exothermic).

*/

#define LOOP_DELAY_MS 10
#define GRAPH_LEFT 21
#define PLOT_MIN 70
#define PLOT_MAX 90
#define AXIS_TICKS 5
#define PV_SPACE 45
#define PIN_TOGGLE_UP 3
#define POLL_INTERVAL_MS 10000

#include "temp.h"
#include "oled.h"
#include "graph.h"
#include "pv_display.h"
#include "menu.h"

Temp temp;
Oled oled;
Graph graph(GRAPH_LEFT, 34, 127 - GRAPH_LEFT, 83, oled);
PvDisplay pv[] = {{"PV1", 0, 0},
		  {"PV2", PV_SPACE, 0},
		  {"PV3", PV_SPACE * 2, 0}};
#define PV_CNT (sizeof(pv)/sizeof(PvDisplay))
PvDisplayMenu pv_menu(pv, PV_CNT);
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
  Menu::begin(&pv_menu, &oled);
  KeyManager::begin();
  draw_temps(/*with_read*/true);
  oled.show();
}

void show_splash() {
  oled.set_font(FONT_BIG);
  oled.print_at("Chongolele!", 30, 20);
  oled.show();
  delay(3000);
  oled.clear();
}

void draw_temps(bool with_read) {
  if (with_read) {
    pv[0].set(temp.get_f(0));
    pv[1].set(0.0);
    pv[2].set(123.4);
  }
  pv_menu.draw();
}

void poll_temps(unsigned long now) {
  if (now > last_poll + POLL_INTERVAL_MS) {
    if (now > last_poll + 2 * POLL_INTERVAL_MS) {
      // if too far behind, just match current time
      last_poll = now;
    } else {
      // try to keep up
      last_poll += POLL_INTERVAL_MS;
    }
    oled.set_font(FONT_BIG);
    oled.print_boxed("POLLING", 2, 0, 124, 25, OLED_BLACK);
    oled.show();
    temp.poll();
    oled.print_boxed("", 2, 0, 124, 25, OLED_WHITE);
    draw_temps(/*with_read*/true);
    graph.plot(temp.get_f(0));
    oled.show();
  }
}

void loop(void) {
  unsigned long now = millis();
  KeyManager::loop(now);
  poll_temps(now);
  delay(LOOP_DELAY_MS);
}
