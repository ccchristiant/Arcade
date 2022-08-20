/*
** EPITECH PROJECT, 2022
** IDisplayModule.hpp
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include "input.hpp"
#include "myPixel.hpp"
#include <memory>
#include <map>
#include <vector>
#include <fstream>
#include <string>

class IDisplayModule {
public:
    virtual ~IDisplayModule() = default;
    virtual void initWindow(int width, int height, const std::string &name) = 0;
    virtual void destroyWindow() = 0;
    virtual const std::string &getName() const = 0;
    virtual std::unique_ptr<Inputs> event() = 0;
    virtual void drawBackground(const std::string &path) = 0;
    virtual void drawText(const myText &text) = 0;
    virtual void drawPixel(const myPixel &pixel, const std::pair<int, int> &map_size) = 0;
    virtual void drawLayers(const std::vector<myPixel> &layers, const std::pair<int, int> &map_size) = 0;
    virtual void clear() = 0;
    virtual void display() = 0;

protected:
private:
};

#endif /* !IDISPLAYMODULE_HPP_ */
