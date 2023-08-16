#include <iostream>

#include "Position.hpp"

Position Position::NextMove(const Position& desired_position) const {
    if (x == desired_position.x) {
        if (y < desired_position.y) return {.x=x, .y=y+1};
        else if (y > desired_position.y) return {.x=x, .y=y-1};
        else return {.x=x, .y=y};
    }
    if (y == desired_position.y) {
        if (x < desired_position.x) return {.x=x+1, .y=y};
        else if (x > desired_position.x) return {.x=x-1, .y=y};
        else return {.x=x, .y=y};
    }

    std::cout << "something went wrong. Can only move in linear pattern";
    throw std::runtime_error{"something went wrong. Can only move in linear pattern"};
}
