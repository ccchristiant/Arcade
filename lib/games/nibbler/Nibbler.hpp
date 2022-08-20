/*
** EPITECH PROJECT, 2022
** Nibbler.hpp
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "IGameModule.hpp"

#define SPEED 0.15
#define SNAKE_INIT_SIZE 4
#define MAP "conf/nibbler/map.txt"

static const NcursesPixel WALL_NCURSES = {.color = {.ncurses = {COLOR_BLACK, COLOR_YELLOW}}, .c = ' '};
static const NcursesPixel GRASS_NCURSES = {.color = {.ncurses = {COLOR_GREEN, COLOR_GREEN}}, .c = ' '};
static const NcursesPixel SNAKE_HEAD_NCURSES = {.color = {.ncurses = {COLOR_CYAN, COLOR_BLUE}}, .c = 'O'};
static const NcursesPixel SNAKE_BODY_NCURSES = {.color = {.ncurses = {COLOR_CYAN, COLOR_BLUE}}, .c = 'o'};
static const NcursesPixel FRUIT_NCURSES = {.color = {.ncurses = {COLOR_WHITE, COLOR_RED}}, .c = ':'};
static const OtherPixel WALL_OTHER = {.color = {.other = {139, 69, 19, 255}}, .pathText = "assets/nibbler/brickwall.jpg"};
static const OtherPixel GRASS_OTHER = {.color = {.other = {107, 142, 35, 255}}, .pathText = "assets/nibbler/grass.png"};
static const OtherPixel SNAKE_HEAD_RIGHT_OTHER = {.color = {.other = {65, 105, 225, 255}}, .pathText = "assets/nibbler/snake_head_right.png"};
static const OtherPixel SNAKE_HEAD_DOWN_OTHER = {.color = {.other = {65, 105, 225, 255}}, .pathText = "assets/nibbler/snake_head_down.png"};
static const OtherPixel SNAKE_HEAD_LEFT_OTHER = {.color = {.other = {65, 105, 225, 255}}, .pathText = "assets/nibbler/snake_head_left.png"};
static const OtherPixel SNAKE_HEAD_UP_OTHER = {.color = {.other = {65, 105, 225, 255}}, .pathText = "assets/nibbler/snake_head_up.png"};
static const OtherPixel SNAKE_BODY_OTHER = {.color = {.other = {70, 130, 180, 255}}, .pathText = "assets/nibbler/snake_body.png"};
static const OtherPixel FRUIT_OTHER = {.color = {.other = {220, 20, 60, 255}}, .pathText = "assets/nibbler/apple.png"};

class Nibbler : public IGameModule {
    public:
        Nibbler(const std::string &name);
        ~Nibbler();

        const std::string &getName() const;
        std::vector<myPixel> getLayers();
        unsigned int getScore();
        bool getGameOver();
        std::pair<int, int> getMapSize();
        void initMap();
        void processInput(const std::unique_ptr<Inputs> &input);
        void update();
        void restart();

    protected:
        std::string _name;
    private:
        std::vector<std::vector<myPixel>> _map;
        unsigned int _score;
        bool _game_over;
        std::clock_t _start;
        std::vector<std::pair<myPixel, Direction>> _snake;
        myPixel _fruit;
        bool _moved;
        bool isSnake(int x, int y);
        void buildHead();
        void buildBody();
        void newFruit();
        void move();
        void moveSnake(const Direction & direction);
        void moveRight();
        void moveDown();
        void moveLeft();
        void moveUp();
};

#endif /* !NIBBLER_HPP_ */
