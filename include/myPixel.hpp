/*
** EPITECH PROJECT, 2022
** myPixel.hpp
** File description:
** myPixel
*/

#ifndef MYPIXEL_HPP_
#define MYPIXEL_HPP_

#include <iostream>

#define PIXEL_SIZE 20

struct NcursesColor {
    bool operator==(const NcursesColor &color) const {
    	return this->text_in == color.text_in && this->text_out == color.text_out;
    };
    short text_in;
    short text_out;
};

struct OtherColor {
    bool operator==(const OtherColor &color) const {
    	return this->r == color.r && this->g == color.g && this->b == color.b && this->a == color.a;
    };
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

union myColor {
    bool operator==(const myColor &color) const {
        return this->ncurses == color.ncurses || this->other == color.other;
    };
    NcursesColor ncurses;
    OtherColor other;
};

struct NcursesPixel {
    bool operator==(const NcursesPixel &pixel) const {
        return this->color == pixel.color && this->c == pixel.c;
    };
    myColor color;
    char c;
};

struct OtherPixel {
    bool operator==(const OtherPixel &pixel) const {
        return this->color == pixel.color && this->pathText.compare(pixel.pathText) == 0;
    };
    myColor color;
    std::string pathText;
};

struct myPixel {
    int x;
    int y;
    NcursesPixel ncurses;
    OtherPixel other;
};

struct myText {
    int x;
    int y;
    std::string text;
    int width;
    int height;
    bool selected;
    NcursesColor ncurses;
    OtherColor other;
};

#endif /* !MYPIXEL_HPP_ */
