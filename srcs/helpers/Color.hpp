//
//  Color.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/16/18.
//

#pragma once

/// Color rgb with value 0-255
struct Color {
  float r;
  float g;
  float b;
  float a;

  Color(int r, int g, int b, float a = 1) : r(static_cast<float>(r) / 255), g(static_cast<float>(g) / 255),
                                            b(static_cast<float>(b) / 255), a(a) {}

  void setColor(int r, int g, int b, int a = 1) {
    this->r = r / 255.0f;
    this->g = g / 255.0f;
    this->b = b / 255.0f;
    this->a = a;
  }
};