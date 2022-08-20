
#ifndef PACMAN_H
#define PACMAN_H

#include "IGameModule.hpp"

#define SPEED 0.15
#define MAP "conf/pacman/pacman_map.txt"

static const NcursesPixel WALL_NCURSES = {.color = {.ncurses = {COLOR_BLACK, COLOR_BLUE}}, .c = ' '};
static const NcursesPixel GROUND_NCURSES = {.color = {.ncurses = {COLOR_BLACK, COLOR_BLACK}}, .c = ' '};
static const NcursesPixel PACMAN_NCURSES = {.color = {.ncurses = {COLOR_YELLOW, COLOR_YELLOW}}, .c = ' '};
static const NcursesPixel PACGUM_NCURSES = {.color = {.ncurses = {COLOR_YELLOW, COLOR_BLACK}}, .c = '*'};
static const NcursesPixel GHOST_RED_NCURSES = {.color = {.ncurses = {COLOR_RED, COLOR_RED}}, .c = ' '};
static const NcursesPixel GHOST_BLUE_NCURSES = {.color = {.ncurses = {COLOR_CYAN, COLOR_CYAN}}, .c = ' '};
static const NcursesPixel GHOST_PINK_NCURSES = {.color = {.ncurses = {COLOR_GREEN, COLOR_GREEN}}, .c = ' '};
static const NcursesPixel GHOST_YELLOW_NCURSES = {.color = {.ncurses = {COLOR_WHITE, COLOR_WHITE}}, .c = ' '};
static const OtherPixel WALL_OTHER = {.color = {.other = {25, 25, 112, 255}}, .pathText = "assets/pacman/wall.png"};
static const OtherPixel GROUND_OTHER = {.color = {.other = {0, 0, 0, 255}}, .pathText = "assets/pacman/ground.png"};
static const OtherPixel PACMAN_RIGHT_OTHER = {.color = {.other = {255, 255, 0, 255}}, .pathText = "assets/pacman/pacman_right.png"};
static const OtherPixel PACMAN_DOWN_OTHER = {.color = {.other = {255, 255, 0, 255}}, .pathText = "assets/pacman/pacman_down.png"};
static const OtherPixel PACMAN_LEFT_OTHER = {.color = {.other = {255, 255, 0, 255}}, .pathText = "assets/pacman/pacman_left.png"};
static const OtherPixel PACMAN_UP_OTHER = {.color = {.other = {255, 255, 0, 255}}, .pathText = "assets/pacman/pacman_up.png"};
static const OtherPixel PACGUM_OTHER = {.color = {.other = {250, 250, 210, 255}}, .pathText = "assets/pacman/pacgum.png"};
static const OtherPixel GHOST_RED_OTHER = {.color = {.other = {255, 0, 0, 255}}, .pathText = "assets/pacman/ghost_red.png"};
static const OtherPixel GHOST_BLUE_OTHER = {.color = {.other = {0, 0, 255, 255}}, .pathText = "assets/pacman/ghost_blue.png"};
static const OtherPixel GHOST_PINK_OTHER = {.color = {.other = {255, 20, 147, 255}}, .pathText = "assets/pacman/ghost_pink.png"};
static const OtherPixel GHOST_YELLOW_OTHER = {.color = {.other = {255, 215, 0, 255}}, .pathText = "assets/pacman/ghost_yellow.png"};

class Pacman : public IGameModule
{
public:
    Pacman(const std::string &name);
    ~Pacman();

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
    std::clock_t _game_start;
    bool _game_started;
    std::clock_t _start;
    bool _released;
    myPixel _pacman;
    Direction _direction;
    std::vector<myPixel> _pacgums;
    std::vector<std::pair<myPixel, Direction>> _ghosts;
    bool isPacgum(int x, int y);
    int checkDir(int x, int y);
    Direction getDir(int tmpDir[]);
    bool isOnGhost(int x, int y) const;
    void move();
    void moveGhosts();
};

#endif
