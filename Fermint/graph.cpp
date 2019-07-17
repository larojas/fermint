#include "graph.h"
#include "oled.h"

Graph::Graph(dim left, dim top, dim width, dim height, Oled& oled)
  : left_(left), top_(top), width_(width), height_(height),
    v_axis_(left, top, height, oled),
    h_axis_(left, top + height, width, oled),
    oled_(oled), plot_seq_(0), last_y_(top + height)
{}

void Graph::begin() {
  v_axis_.draw(/*is_vertical*/true);
  h_axis_.draw(/*is_vertical*/false);
}

void Graph::plot(float point) {

  dim x = left_ + plot_seq_;
  dim y_delta = (point - v_axis_.scale_min()) * v_axis_.px_per_unit() + 0.5;
  dim y = top_ + height_ - y_delta;
  oled_.mode(OLED_BLACK);
  oled_.vline(x, top_, height_);
  oled_.mode(OLED_WHITE);
  oled_.line(x - 1, last_y_, x, y);
  oled_.show();
  last_y_ = y;
  plot_seq_ += 1;
  if (plot_seq_ >= width_) {
    plot_seq_ = 0;
  }
}

