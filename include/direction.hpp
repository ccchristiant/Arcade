/*
** EPITECH PROJECT, 2022
** direction.hpp
** File description:
** direction
*/

#ifndef DIRECTION_HPP_
#define DIRECTION_HPP_

enum Direction {
    RIGHT = 0,
    DOWN,
    LEFT,
    UP,
};

inline Direction operator--(Direction &direction)
{
    if (direction == RIGHT)
        direction = UP;
    else
        direction = static_cast<Direction>(direction - 1);
    return direction;
}

inline Direction operator--(Direction &direction, int)
{
    Direction rVal = direction;

    --direction;
    return rVal;
}

inline Direction operator++(Direction &direction)
{
    if (direction == UP)
        direction = RIGHT;
    else
        direction = static_cast<Direction>(direction + 1);
    return direction;
}

inline Direction operator++(Direction &direction, int)
{
    Direction rVal = direction;

    ++direction;
    return rVal;
}

#endif /* !DIRECTION_HPP_ */
