#pragma once

struct Position
{
    size_t x;
    size_t y;

    Position NextMove(const Position &desired_position) const;

    bool operator!=(const Position &rhs) const
    {
        return x != rhs.x || y != rhs.y;
    }

    bool operator==(const Position &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
};
