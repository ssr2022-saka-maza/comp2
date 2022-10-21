#pragma once

#include "ssr2/Vector2D.hpp"
#include <Arduino.h>

namespace ssr2 {

struct PS4Value {
public:
    Vector2D<uint8_t> lstick;
    Vector2D<uint8_t> rstick;
    bool up, right, down, left;
    bool triangle, circle, cross, square;
    bool l1;
    uint8_t l2;
    bool l3;
    bool r1;
    uint8_t r2;
    bool r3;
    bool ps, share, options;
    bool finger1Touch;
    Vector2D<uint16_t> finger1Pos;
    bool finger2Touch;
    Vector2D<uint16_t> finger2Pos;

    explicit PS4Value(
        uint8_t lstick_x = 0, uint8_t lstick_y = 0, uint8_t rstick_x = 0, uint8_t rstick_y = 0,
        bool up = false, bool right = false, bool down = false, bool left = false,
        bool triangle = false, bool circle = false, bool cross = false, bool square = false,
        bool l1 = false, uint8_t l2 = 0, bool l3 = false,
        bool r1 = false, uint8_t r2 = 0, bool r3 = false,
        bool ps = false, bool share = false, bool options = false,
        bool finger1Touch = false, uint16_t finger1Pos_x = 0, uint16_t finger1Pos_y = 0,
        bool finger2Touch = false, uint16_t finger2Pos_x = 0, uint16_t finger2Pos_y = 0);
}; // struct PS4Value

} // namespace ssr2

bool operator==(const ssr2::PS4Value &lhs, const ssr2::PS4Value &rhs);
bool operator!=(const ssr2::PS4Value &lhs, const ssr2::PS4Value &rhs);
