/*
** EPITECH PROJECT, 2022
** input.hpp
** File description:
** input
*/

#ifndef INPUT_HPP
    #define INPUT_HPP

class Inputs
{
public:
    enum class input
    {
        RIGHT,
        LEFT,
        TOP,
        DOWN,
        ENTER,
        CLOSE,
        INPUT,
        SPACE,
        NONE,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        BACKSPACE
    };
    enum class type
    {
        KEYBOARD,
        MOUSE,
        NONE
    };
    Inputs(const Inputs::type &type, const Inputs::input &input = Inputs::input::NONE, const int xpos = -1, const int ypos = -1) : _type(type), _input(input), _xPos(xpos), _yPos(ypos) {};
    ~Inputs() = default;
    const input &getInput()
    {
        return this->_input;
    };
    const type &getType()
    {
        return this->_type;
    };
    const int &getXPos()
    {
        return this->_xPos;
    };
    const int &getYPos()
    {
        return this->_yPos;
    };
private:
    type _type;
    input _input;
    const int _xPos;
    const int _yPos;
};

#endif
