//
// Created by wilmot_g on 02/04/18.
//

#include "helpers/Shape.hpp"

constexpr float Shape::defaultDelta;

Shape::Shape(std::vector<Coordinates> parts, GLenum mode, Color color)
: _deltaX(defaultDelta), _deltaY(defaultDelta), color(color), parts(std::move(parts)), mode(mode), size(1) {
}

Shape::Shape(std::vector<Coordinates> parts, GLenum mode, const float& deltaX, const float& deltaY, Color color)
: _deltaX(deltaX), _deltaY(deltaY), color(color), parts(std::move(parts)), mode(mode), size(1) {
}

Shape::Shape(const float& deltaX, const float& deltaY, std::vector<Coordinates> parts, GLenum mode, Color color)
    : _deltaX(deltaX), _deltaY(deltaY), color(color), parts(std::move(parts)), mode(mode), size(1) {
}
