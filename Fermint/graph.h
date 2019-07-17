/*
 * Routines for plotting a simple graph.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "util.h"
#include "axis.h"

// Forward declaration
class Oled;
using Util::dim;

class Graph {
 public:
  Graph(dim left, dim top, dim width, dim height, Oled& oled);
  void begin();
  void plot(float point);
  Axis& v_axis() { return v_axis_; }
  Axis& h_axis() { return h_axis_; }

 private:
  dim left_;
  dim top_;
  dim width_;
  dim height_;

  Axis v_axis_;
  Axis h_axis_;
  
  Oled& oled_;
  dim plot_seq_;
  dim last_y_;
};


#endif // GRAPH_H
