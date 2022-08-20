/*
** EPITECH PROJECT, 2022
** Nibbler.cpp
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

extern "C"
{
    std::unique_ptr<IGameModule> entryPoint(const std::string &path)
    {
        return (std::make_unique<Nibbler>(path));
    }
}

Nibbler::Nibbler(const std::string &name) : _name(name)
{
    std::cout << "[" << _name << "] Loading nibbler library..." << std::endl;
    initMap();
    srand(time(NULL));
    restart();
}

Nibbler::~Nibbler()
{
    std::cout << "[" << _name << "] Stopping nibbler library..." << std::endl;
}

const std::string &Nibbler::getName() const
{
    return _name;
}

std::vector<myPixel> Nibbler::getLayers()
{
    std::vector<myPixel> layers;

    for (std::size_t i = 0; i < _map.size(); i++)
        for (std::size_t j = 0; j < _map[i].size(); j++)
            layers.push_back(_map[i][j]);
    for (std::size_t i = 0; i < _snake.size(); i++)
        layers.push_back(_snake[i].first);
    layers.push_back(_fruit);
    return layers;
}

unsigned int Nibbler::getScore()
{
    return _score;
}

bool Nibbler::getGameOver()
{
    return _game_over;
}

std::pair<int, int> Nibbler::getMapSize()
{
    return std::make_pair(_map.front().size(), _map.size());
}

void Nibbler::initMap()
{
    std::ifstream file(MAP);
    std::string str;

    while (std::getline(file, str)) {
        std::vector<myPixel> tmp;
        for (std::size_t x = 0; x < str.length(); x++) {
            myPixel tmp_pixel;
            tmp_pixel.x = x;
            tmp_pixel.y = _map.size();
            if (str[x] == '*') {
                tmp_pixel.ncurses = WALL_NCURSES;
                tmp_pixel.other = WALL_OTHER;
            }
            else {
                tmp_pixel.ncurses = GRASS_NCURSES;
                tmp_pixel.other = GRASS_OTHER;
            }
            tmp.push_back(tmp_pixel);
        }
        _map.push_back(tmp);
    }
}

void Nibbler::processInput(const std::unique_ptr<Inputs> &input)
{
    if (input->getInput() == Inputs::input::RIGHT && _snake.front().second != LEFT && _moved == true) {
        _snake.front().second = RIGHT;
        _moved = false;
    }
    if (input->getInput() == Inputs::input::DOWN && _snake.front().second != UP && _moved == true) {
        _snake.front().second = DOWN;
        _moved = false;
    }
    if (input->getInput() == Inputs::input::LEFT && _snake.front().second != RIGHT && _moved == true) {
        _snake.front().second = LEFT;
        _moved = false;
    }
    if (input->getInput() == Inputs::input::TOP && _snake.front().second != DOWN && _moved == true) {
        _snake.front().second = UP;
        _moved = false;
    }
}

void Nibbler::update()
{
    double duration;

    duration = (std::clock() - _start) / (double) CLOCKS_PER_SEC;
    if (duration > static_cast<double>(SPEED)) {
        move();
        _start = std::clock();
    }
}

void Nibbler::restart()
{
    _score = 0;
    _game_over = false;
    _start = std::clock();
    _snake.clear();
    buildHead();
    while (_snake.size() < SNAKE_INIT_SIZE)
        buildBody();
    _fruit.x = _snake.front().first.x + SNAKE_INIT_SIZE;
    _fruit.y = _snake.front().first.y;
    _fruit.ncurses = FRUIT_NCURSES;
    _fruit.other = FRUIT_OTHER;
    _moved = false;
}

bool Nibbler::isSnake(int x, int y)
{
    for (std::size_t i = 0; i < _snake.size(); i++)
        if (_snake[i].first.x == x && _snake[i].first.y == y)
            return true;
    return false;
}

void Nibbler::buildHead()
{
    myPixel tmp_pixel;

    tmp_pixel.x = _map.front().size() / 2;
    tmp_pixel.y = _map.size() / 2;
    tmp_pixel.ncurses = SNAKE_HEAD_NCURSES;
    tmp_pixel.other = SNAKE_HEAD_RIGHT_OTHER;
    _snake.emplace_back(tmp_pixel, RIGHT);
}

void Nibbler::buildBody()
{
    myPixel tmp_pixel;
    Direction tmp_direction;
    int tail_x =_snake.back().first.x;
    int tail_y = _snake.back().first.y;
    Direction tail_direction = _snake.back().second;

    if (tail_direction == RIGHT) {
        if (_map[tail_y][tail_x - 1].ncurses == WALL_NCURSES ||
            _map[tail_y][tail_x - 1].other == WALL_OTHER ||
            isSnake(tail_x - 1, tail_y)) {
            tmp_pixel.x = tail_x;
            if (_map[tail_y - 1][tail_x].ncurses == WALL_NCURSES ||
                _map[tail_y - 1][tail_x].other == WALL_OTHER ||
                isSnake(tail_x, tail_y - 1)) {
                if (_map[tail_y + 1][tail_x].ncurses == WALL_NCURSES ||
                    _map[tail_y + 1][tail_x].other == WALL_OTHER ||
                    isSnake(tail_x, tail_y + 1)) {
                    _game_over = true;
                    return;
                } else {
                    tmp_pixel.y = tail_y + 1;
                    tmp_direction = UP;
                }
            } else {
                tmp_pixel.y = tail_y - 1;
                tmp_direction = DOWN;
            }
        } else {
            tmp_pixel.x = tail_x - 1;
            tmp_pixel.y = tail_y;
            tmp_direction = RIGHT;
        }
    }
    if (tail_direction == DOWN) {
        if (_map[tail_y - 1][tail_x].ncurses == WALL_NCURSES ||
            _map[tail_y - 1][tail_x].other == WALL_OTHER ||
            isSnake(tail_x, tail_y - 1)) {
            tmp_pixel.y = tail_y;
            if (_map[tail_y][tail_x - 1].ncurses == WALL_NCURSES ||
                _map[tail_y][tail_x - 1].other == WALL_OTHER ||
                isSnake(tail_x - 1, tail_y)) {
                if (_map[tail_y][tail_x + 1].ncurses == WALL_NCURSES ||
                    _map[tail_y][tail_x + 1].other == WALL_OTHER ||
                    isSnake(tail_x + 1, tail_y)) {
                    _game_over = true;
                    return;
                } else {
                    tmp_pixel.x = tail_x + 1;
                    tmp_direction = LEFT;
                }
            } else {
                tmp_pixel.x = tail_x - 1;
                tmp_direction = RIGHT;
            }
        } else {
            tmp_pixel.x = tail_x;
            tmp_pixel.y = tail_y - 1;
            tmp_direction = DOWN;
        }
    }
    if (tail_direction == LEFT) {
        if (_map[tail_y][tail_x + 1].ncurses == WALL_NCURSES ||
            _map[tail_y][tail_x + 1].other == WALL_OTHER ||
            isSnake(tail_x + 1, tail_y)) {
            tmp_pixel.x = tail_x;
            if (_map[tail_y - 1][tail_x].ncurses == WALL_NCURSES ||
                _map[tail_y - 1][tail_x].other == WALL_OTHER ||
                isSnake(tail_x, tail_y - 1)) {
                if (_map[tail_y + 1][tail_x].ncurses == WALL_NCURSES ||
                    _map[tail_y + 1][tail_x].other == WALL_OTHER ||
                    isSnake(tail_x, tail_y + 1)) {
                    _game_over = true;
                    return;
                } else {
                    tmp_pixel.y = tail_y + 1;
                    tmp_direction = UP;
                }
            } else {
                tmp_pixel.y = tail_y - 1;
                tmp_direction = DOWN;
            }
        } else {
            tmp_pixel.x = tail_x + 1;
            tmp_pixel.y = tail_y;
            tmp_direction = LEFT;
        }
    }
    if (tail_direction == UP) {
        if (_map[tail_y + 1][tail_x].ncurses == WALL_NCURSES ||
            _map[tail_y + 1][tail_x].other == WALL_OTHER ||
            isSnake(tail_x, tail_y + 1)) {
            tmp_pixel.y = tail_y;
            if (_map[tail_y][tail_x - 1].ncurses == WALL_NCURSES ||
                _map[tail_y][tail_x - 1].other == WALL_OTHER ||
                isSnake(tail_x - 1, tail_y)) {
                if (_map[tail_y][tail_x + 1].ncurses == WALL_NCURSES ||
                    _map[tail_y][tail_x + 1].other == WALL_OTHER ||
                    isSnake(tail_x + 1, tail_y)) {
                    _game_over = true;
                    return;
                } else {
                    tmp_pixel.x = tail_x + 1;
                    tmp_direction = LEFT;
                }
            } else {
                tmp_pixel.x = tail_x - 1;
                tmp_direction = RIGHT;
            }
        } else {
            tmp_pixel.x = tail_x;
            tmp_pixel.y = tail_y + 1;
            tmp_direction = UP;
        }
    }
    tmp_pixel.ncurses = SNAKE_BODY_NCURSES;
    tmp_pixel.other = SNAKE_BODY_OTHER;
    _snake.emplace_back(tmp_pixel, tmp_direction);
}

void Nibbler::newFruit()
{
    std::vector<std::pair<int, int>> free_cells;
    std::size_t chosen_cell;

    for (unsigned int i = 1; i < _map.size() - 1; i++)
        for (unsigned int j = 1; j < _map.front().size() - 1; j++)
            if (!isSnake(j, i))
                free_cells.emplace_back(j, i);
    chosen_cell = rand() % free_cells.size();
    _fruit.x = free_cells[chosen_cell].first;
    _fruit.y = free_cells[chosen_cell].second;
}

void Nibbler::move()
{
    if (_snake.front().second == RIGHT)
        moveRight();
    if (_snake.front().second == DOWN)
        moveDown();
    if (_snake.front().second == LEFT)
        moveLeft();
    if (_snake.front().second == UP)
        moveUp();
    _moved = true;
}

void Nibbler::moveSnake(const Direction &direction)
{
    _snake.front().second = direction;
    for (std::size_t i = _snake.size() - 1; i > 0; --i) {
        _snake[i].first.x = _snake[i - 1].first.x;
        _snake[i].first.y = _snake[i - 1].first.y;
        _snake[i].second = _snake[i - 1].second;
    }
    if (direction == RIGHT) {
        ++_snake.front().first.x;
        _snake.front().first.other = SNAKE_HEAD_RIGHT_OTHER;
    }
    if (direction == DOWN) {
        ++_snake.front().first.y;
        _snake.front().first.other = SNAKE_HEAD_DOWN_OTHER;
    }
    if (direction == LEFT) {
        --_snake.front().first.x;
        _snake.front().first.other = SNAKE_HEAD_LEFT_OTHER;
    }
    if (direction == UP) {
        --_snake.front().first.y;
        _snake.front().first.other = SNAKE_HEAD_UP_OTHER;
    }
}

void Nibbler::moveRight()
{
    int head_x =_snake.front().first.x;
    int head_y = _snake.front().first.y;

    if (_map[head_y][head_x + 1].ncurses == WALL_NCURSES ||
        _map[head_y][head_x + 1].other == WALL_OTHER ||
        isSnake(head_x + 1, head_y))
        _game_over = true;
    else if (head_x + 1 == _fruit.x && head_y == _fruit.y) {
        ++_score;
        moveSnake(RIGHT);
        buildBody();
        if (_game_over == false)
            newFruit();
    }
    else
        moveSnake(RIGHT);
}

void Nibbler::moveDown()
{
    int head_x =_snake.front().first.x;
    int head_y = _snake.front().first.y;

    if (_map[head_y + 1][head_x].ncurses == WALL_NCURSES ||
        _map[head_y + 1][head_x].other == WALL_OTHER ||
        isSnake(head_x, head_y + 1))
        _game_over = true;
    else if (head_x == _fruit.x && head_y + 1 == _fruit.y) {
        ++_score;
        moveSnake(DOWN);
        buildBody();
        if (_game_over == false)
            newFruit();
    }
    else
        moveSnake(DOWN);
}

void Nibbler::moveLeft()
{
    int head_x =_snake.front().first.x;
    int head_y = _snake.front().first.y;

    if (_map[head_y][head_x - 1].ncurses == WALL_NCURSES ||
        _map[head_y][head_x - 1].other == WALL_OTHER ||
        isSnake(head_x - 1, head_y))
        _game_over = true;
    else if (head_x - 1== _fruit.x && head_y == _fruit.y) {
        ++_score;
        moveSnake(LEFT);
        buildBody();
        if (_game_over == false)
            newFruit();
    }
    else
        moveSnake(LEFT);
}

void Nibbler::moveUp()
{
    int head_x =_snake.front().first.x;
    int head_y = _snake.front().first.y;

    if (_map[head_y - 1][head_x].ncurses == WALL_NCURSES ||
        _map[head_y - 1][head_x].other == WALL_OTHER ||
        isSnake(head_x, head_y - 1))
        _game_over = true;
    else if (head_x == _fruit.x && head_y - 1 == _fruit.y) {
        ++_score;
        moveSnake(UP);
        buildBody();
        if (_game_over == false)
            newFruit();
    }
    else
        moveSnake(UP);
}
