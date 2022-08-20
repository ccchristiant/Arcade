/*
** EPITECH PROJECT, 2022
** bar.hpp
** File description:
** bar
*/

#ifndef BAR_HPP_
#define BAR_HPP_

#include "IDisplayModule.hpp"
#include <ncurses.h>
#include <unistd.h>

class BarModule : public IDisplayModule {
public:
    BarModule(const std::string &name);
    ~BarModule();

    void initWindow(int width, int height, const std::string &name);
    void destroyWindow();
    const std::string &getName() const;
    std::unique_ptr<Inputs> event();
    void drawBackground(const std::string &path);
    void drawText(const myText &text);
    void drawPixel(const myPixel &pixel, const std::pair<int, int> &map_size);
    void drawLayers(const std::vector<myPixel> &layers, const std::pair<int, int> &map_size);
    void clear();
    void display();
protected:
    std::string _name;
private:
    std::vector<short> _color_pairs;
    short _pair;
    int getColorPair(const NcursesColor &color);
    void setColorPair(const NcursesColor &color);
};

#endif /* !BAR_HPP_ */
