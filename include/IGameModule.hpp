/*
** EPITECH PROJECT, 2022
** IGameModule.hpp
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include "IDisplayModule.hpp"
#include "direction.hpp"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <utility>

class IGameModule {
public:
    virtual ~IGameModule() = default;
    virtual const std::string &getName() const = 0;
    virtual std::vector<myPixel> getLayers() = 0;
    virtual unsigned int getScore() = 0;
    virtual bool getGameOver() = 0;
    virtual std::pair<int, int> getMapSize() = 0;
    virtual void initMap() = 0;
    virtual void processInput(const std::unique_ptr<Inputs> &input) = 0;
    virtual void update() = 0;
    virtual void restart() = 0;

protected:
private:
};

#endif /* !IGAMEMODULE_HPP_ */
