#include "pacman.hpp"

extern "C"
{
    std::unique_ptr<IGameModule> entryPoint(const std::string &path)
    {
        return (std::make_unique<Pacman>(path));
    }
}

Pacman::Pacman(const std::string &name) : _name(name)
{
    std::cout << "[" << _name << "] Loading pacman library..." << std::endl;
    srand(time(NULL));
    restart();
}

Pacman::~Pacman()
{
    std::cout << "[" << _name << "] Stopping pacman library..." << std::endl;
}

const std::string &Pacman::getName() const
{
    return _name;
}

std::vector<myPixel> Pacman::getLayers()
{
    std::vector<myPixel> layers;

    for (std::size_t i = 0; i < _map.size(); ++i)
        for (std::size_t j = 0; j < _map[i].size(); ++j)
            layers.push_back(_map[i][j]);
    for (std::size_t i = 0; i < _pacgums.size(); ++i)
        layers.push_back(_pacgums[i]);
    layers.push_back(_pacman);
    for (std::size_t i = 0; i < _ghosts.size(); ++i)
        layers.push_back(_ghosts[i].first);
    return layers;
}

unsigned int Pacman::getScore()
{
    return _score;
}

bool Pacman::getGameOver()
{
    return _game_over;
}

std::pair<int, int> Pacman::getMapSize()
{
    return std::make_pair(_map.front().size(), _map.size());
}

void Pacman::initMap()
{
    std::ifstream file(MAP);
    std::string str;

    while (std::getline(file, str)) {
        std::vector<myPixel> tmp;
        for (std::size_t x = 0; x < str.length(); x++) {
            myPixel tmp_pixel;
            myPixel tmp_pixel_2;
            tmp_pixel.x = x;
            tmp_pixel.y = _map.size();
            tmp_pixel_2.x = x;
            tmp_pixel_2.y = _map.size();
            if (str[x] == '1') {
                tmp_pixel.ncurses = WALL_NCURSES;
                tmp_pixel.other = WALL_OTHER;
            }
            else if (str[x] == ' ') {
                tmp_pixel.ncurses = GROUND_NCURSES;
                tmp_pixel.other = GROUND_OTHER;
                tmp_pixel_2.ncurses = PACGUM_NCURSES;
                tmp_pixel_2.other = PACGUM_OTHER;
                _pacgums.push_back(tmp_pixel_2);
            }
            else {
                tmp_pixel.ncurses = GROUND_NCURSES;
                tmp_pixel.other = GROUND_OTHER;
            }
            tmp.push_back(tmp_pixel);
        }
        _map.push_back(tmp);
    }
}

void Pacman::processInput(const std::unique_ptr<Inputs> &input)
{
    if (input->getInput() == Inputs::input::RIGHT)
        _direction = RIGHT;
    if (input->getInput() == Inputs::input::DOWN)
        _direction = DOWN;
    if (input->getInput() == Inputs::input::LEFT)
        _direction = LEFT;
    if (input->getInput() == Inputs::input::TOP)
        _direction = UP;
}

void Pacman::update()
{
    double duration;
    double game_duration;

    if (_game_started == false) {
        _game_start = std::clock();
        _game_started = true;
    }
    duration = (std::clock() - _start) / (double) CLOCKS_PER_SEC;
    game_duration = (std::clock() - _game_start) / (double) CLOCKS_PER_SEC;
    if (game_duration >= 5.0 && _released == false) {
        _released = true;
        for (std::size_t i = 0; i < _ghosts.size(); ++i) {
            _ghosts[i].first.x = (_ghosts[i].second == LEFT) ? _ghosts[i].first.x - 1 : _ghosts[i].first.x + 1;
            for (std::size_t j = 0; j < 2; ++j)
                _ghosts[i].first.y -= 1;
            _ghosts[i].first.y -= (i > 1) ? 1 : 0;
            _ghosts[i].second = (rand() % 2 == 0) ? LEFT : RIGHT;
        }
    }
    if (duration > static_cast<double>(SPEED)) {
        move();
        _game_over = (_pacgums.size() == 0);
        if (_game_over == false &&_released == true)
            moveGhosts();
        _start = std::clock();
    }
}

void Pacman::restart()
{
    myPixel tmp_pixel;

    for (std::size_t i = 0; i < _map.size(); ++i)
        _map[i].clear();
    _map.clear();
    _pacgums.clear();
    initMap();
    _score = 0;
    _game_over = false;
    _game_start = std::clock();
    _game_started = false;
    _start = std::clock();
    _released = false;
    _pacman.x = _map.front().size() / 2;
    _pacman.y = _map.size() / 2 + 2;
    _pacman.ncurses = PACMAN_NCURSES;
    _pacman.other = PACMAN_LEFT_OTHER;
    _direction = LEFT;
    _ghosts.clear();
    tmp_pixel.x = _map.front().size() / 2 - 1;
    tmp_pixel.y = _map.size() / 2 - 1;
    tmp_pixel.ncurses = GHOST_RED_NCURSES;
    tmp_pixel.other = GHOST_RED_OTHER;
    _ghosts.emplace_back(tmp_pixel, RIGHT);
    tmp_pixel.x = _map.front().size() / 2 + 1;
    tmp_pixel.y = _map.size() / 2 - 1;
    tmp_pixel.ncurses = GHOST_BLUE_NCURSES;
    tmp_pixel.other = GHOST_BLUE_OTHER;
    _ghosts.emplace_back(tmp_pixel, LEFT);
    tmp_pixel.x = _map.front().size() / 2 - 1;
    tmp_pixel.y = _map.size() / 2;
    tmp_pixel.ncurses = GHOST_PINK_NCURSES;
    tmp_pixel.other = GHOST_PINK_OTHER;
    _ghosts.emplace_back(tmp_pixel, RIGHT);
    tmp_pixel.x = _map.front().size() / 2 + 1;
    tmp_pixel.y = _map.size() / 2;
    tmp_pixel.ncurses = GHOST_YELLOW_NCURSES;
    tmp_pixel.other = GHOST_YELLOW_OTHER;
    _ghosts.emplace_back(tmp_pixel, LEFT);
}

bool Pacman::isPacgum(int x, int y)
{
    for (std::size_t i = 0; i < _pacgums.size(); ++i)
        if (_pacgums[i].x == x && _pacgums[i].y == y) {
            _pacgums.erase(_pacgums.begin() + i);
            return true;
        }
    return false;
}

int Pacman::checkDir(int x, int y)
{
    if ((_map[y][x].ncurses == GROUND_NCURSES || _map[y][x].other == GROUND_OTHER) && !isOnGhost(x, y))
        return true;
    return false;
}

Direction Pacman::getDir(int tmpDir[])
{
    int i = rand() % 4;
    if (tmpDir[i] == 1)
        return static_cast<Direction>(i);
    return getDir(tmpDir);
}

bool Pacman::isOnGhost(int x, int y) const
{
    for (std::size_t i = 0; i < _ghosts.size(); i++)
        if (_ghosts[i].first.x == x && _ghosts[i].first.y == y)
            return true;
    return false;
}

void Pacman::move()
{
    switch(_direction) {
        case RIGHT:
            _pacman.other = PACMAN_RIGHT_OTHER;
            _pacman.x = (_pacman.x == static_cast<int>(_map.front().size() - 1)) ? -1 : _pacman.x;
            if (_map[_pacman.y][_pacman.x + 1].ncurses == GROUND_NCURSES ||
                _map[_pacman.y][_pacman.x + 1].other == GROUND_OTHER) {
                if (isPacgum(_pacman.x + 1, _pacman.y))
                    _score += 10;
                _pacman.x += 1;
            }
            break;
        case DOWN:
            _pacman.other = PACMAN_DOWN_OTHER;
            _pacman.y = (_pacman.y == static_cast<int>(_map.size() - 1)) ? -1 : _pacman.y;
            if (_map[_pacman.y + 1][_pacman.x].ncurses == GROUND_NCURSES ||
                _map[_pacman.y + 1][_pacman.x].other == GROUND_OTHER) {
                if (isPacgum(_pacman.x, _pacman.y + 1))
                    _score += 10;
                _pacman.y += 1;
            }
            break;
        case LEFT:
            _pacman.other = PACMAN_LEFT_OTHER;
            _pacman.x = (_pacman.x == 0) ? _map.front().size() : _pacman.x;
            if (_map[_pacman.y][_pacman.x - 1].ncurses == GROUND_NCURSES ||
                _map[_pacman.y][_pacman.x - 1].other == GROUND_OTHER) {
                if (isPacgum(_pacman.x - 1, _pacman.y))
                    _score += 10;
                _pacman.x -= 1;
            }
            break;
        case UP:
            _pacman.other = PACMAN_UP_OTHER;
            _pacman.y = (_pacman.y == 0) ? _map.size() : _pacman.y;
            if (_map[_pacman.y - 1][_pacman.x].ncurses == GROUND_NCURSES ||
                _map[_pacman.y - 1][_pacman.x].other == GROUND_OTHER) {
                if (isPacgum(_pacman.x, _pacman.y - 1))
                    _score += 10;
                _pacman.y -= 1;
            }
            break;
    }
}

void Pacman::moveGhosts()
{
    int tmpDir[] = {0, 0, 0, 0};

    for (std::size_t i = 0; i < _ghosts.size(); ++i) {
        tmpDir[0] = ((_ghosts[i].second == UP || _ghosts[i].second == DOWN) && checkDir(_ghosts[i].first.x - 1, _ghosts[i].first.y) == 1) ? 1 : 0;
        tmpDir[1] = ((_ghosts[i].second == UP || _ghosts[i].second == DOWN) && checkDir(_ghosts[i].first.x + 1, _ghosts[i].first.y) == 1) ? 1 : 0;
        tmpDir[2] = ((_ghosts[i].second == LEFT || _ghosts[i].second == RIGHT) && checkDir(_ghosts[i].first.x, _ghosts[i].first.y - 1) == 1) ? 1 : 0;
        tmpDir[3] = ((_ghosts[i].second == LEFT || _ghosts[i].second == RIGHT) && checkDir(_ghosts[i].first.x, _ghosts[i].first.y + 1) == 1) ? 1 : 0;
        if (tmpDir[0] == 1 || tmpDir[1] == 1 || tmpDir[2] == 1 || tmpDir[3] == 1)
            _ghosts[i].second = getDir(tmpDir);
        if (_pacman.x < _ghosts[i].first.x)
            _ghosts[i].second = (tmpDir[0] == 1) ? LEFT : _ghosts[i].second;
        else
            _ghosts[i].second = (tmpDir[1] == 1) ? RIGHT : _ghosts[i].second;
        if (_pacman.y < _ghosts[i].first.y)
            _ghosts[i].second = (tmpDir[2] == 1) ? UP : _ghosts[i].second;
        else
            _ghosts[i].second = (tmpDir[3] == 1) ? DOWN : _ghosts[i].second;
        if (_ghosts[i].first.x == 0) {
            _ghosts[i].first.x = _map.front().size() - 1;
            _ghosts[i].second = LEFT;
        } else if (_ghosts[i].first.x == static_cast<int>(_map.front().size() - 1)) {
            _ghosts[i].first.x = 0;
            _ghosts[i].second = RIGHT;
        } else if (_ghosts[i].first.y == 0) {
            _ghosts[i].first.y = _map.size() - 1;
            _ghosts[i].second = UP;
        } else if (_ghosts[i].first.y == static_cast<int>(_map.size() - 1)) {
            _ghosts[i].first.y = 0;
            _ghosts[i].second = DOWN;
        }
        _ghosts[i].first.x -= (_ghosts[i].second == LEFT) ? 1 : 0;
        _ghosts[i].first.x += (_ghosts[i].second == RIGHT) ? 1 : 0;
        _ghosts[i].first.y -= (_ghosts[i].second == UP) ? 1 : 0;
        _ghosts[i].first.y += (_ghosts[i].second == DOWN) ? 1 : 0;
        if (_pacman.x == _ghosts[i].first.x && _pacman.y == _ghosts[i].first.y) {
            _game_over = true;
            return;
        }
        for (int j = 0; j < 4; ++j)
            tmpDir[j] = 0;
    }
}