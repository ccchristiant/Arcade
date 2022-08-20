#include "Core.hpp"

Core::Core(const std::string &path)
{
    try {
        _dispModsLoader.push_back(std::make_unique<DLLoader<IDisplayModule, ent_point_gr_ptr>>(path));
        _dispMods.push_back(_dispModsLoader.back()->getInstance());
        for (const auto & entry : std::filesystem::directory_iterator("lib/graphicals"))
            if (entry.path().extension() == ".so" && !modExists(_dispMods.front()->getName(), entry.path())) {
                _dispModsLoader.push_back(std::make_unique<DLLoader<IDisplayModule, ent_point_gr_ptr>>(entry.path().c_str()));
                _dispMods.push_back(_dispModsLoader.back()->getInstance());
            }
        for (const auto & entry : std::filesystem::directory_iterator("lib/games"))
            if (entry.path().extension() == ".so") {
                _gameModsLoader.push_back(std::make_unique<DLLoader<IGameModule, ent_point_gm_ptr>>(entry.path().c_str()));
                _gameMods.push_back(_gameModsLoader.back()->getInstance());
            }
        _curDispMod = 0;
        _curGameMod = MENU;
        _running = true;
        _selector = NAME;
        _curMenuDispMod = 0;
        _curMenuGameMod = 0;
        _curUserName = "";
        _paused = false;
    }
    catch (std::exception &e) {
        throw e;
    }
}

int Core::modExists(const std::string &mod_name, const std::string &path)
{
    std::string shortened_path = path.substr(path.find_last_of('/') + 1);

    if (shortened_path.compare(mod_name + ".so") == 0)
        return 1;
    return 0;
}

void Core::loop()
{
    this->_dispMods[_curDispMod]->initWindow(1000, 800, "arcade");
    while (_running) {
        std::unique_ptr<Inputs> event = this->_dispMods[_curDispMod]->event();
        _dispMods[_curDispMod]->clear();
        if (_curGameMod == MENU)
            menu(event);
        else
            game(event);
        _dispMods[_curDispMod]->display();
    }
    this->_dispMods[_curDispMod]->destroyWindow();
}

bool Core::bothEvents(const std::unique_ptr<Inputs> &event)
{
    if (event->getInput() == Inputs::input::CLOSE || event->getInput() == Inputs::input::Q) {
        _running = false;
        return false;
    }
    return true;
}

bool Core::menuEvents(const std::unique_ptr<Inputs> &event)
{
    if (event->getInput() == Inputs::input::TOP) {
        if (_selector == NAME)
            _selector = GAME;
        else if (_selector == GRAPHIC)
            _selector = NAME;
        else
            _selector = GRAPHIC;
    } else if (event->getInput() == Inputs::input::DOWN) {
            if (_selector == NAME)
                _selector = GRAPHIC;
            else if (_selector == GRAPHIC)
                _selector = GAME;
            else
                _selector = NAME;
    } else if (event->getInput() == Inputs::input::SPACE) {
        if (_curMenuDispMod != _curDispMod) {
            _dispMods[_curDispMod]->destroyWindow();
            _curDispMod =_curMenuDispMod;
            _dispMods[_curDispMod]->initWindow(1000, 800, "arcade");
        }
        _curGameMod = _curMenuGameMod;
    } else if (_selector == NAME) {
        if (event->getInput() >= Inputs::input::A && event->getInput() <= Inputs::input::Z && _curUserName.size() <= 15)
            _curUserName.push_back(static_cast<char>('A') + static_cast<char>(event->getInput()) - 9);
        if (event->getInput() == Inputs::input::BACKSPACE && _curUserName.size() > 0)
            _curUserName = _curUserName.substr(0, _curUserName.size() - 1);
        if (event->getInput() == Inputs::input::CLOSE) {
            _running = false;
            return false;
        }
    } else {
        if (!bothEvents(event))
            return false;
        else if (event->getInput() == Inputs::input::LEFT) {
            if (_selector == GRAPHIC) {
                if (_curMenuDispMod == 0)
                    _curMenuDispMod = _dispMods.size() - 1;
                else
                    --_curMenuDispMod;
            } else {
                if (_curMenuGameMod == 0)
                    _curMenuGameMod = _gameMods.size() - 1;
                else
                    --_curMenuGameMod;
            }
        } else if (event->getInput() == Inputs::input::RIGHT) {
            if (_selector == GRAPHIC) {
                if (_curMenuDispMod == _dispMods.size() - 1)
                    _curMenuDispMod = 0;
                else
                    ++_curMenuDispMod;
            } else {
                if (_curMenuGameMod == _gameMods.size() - 1)
                    _curMenuGameMod = 0;
                else
                    ++_curMenuGameMod;
            }
        } else if (event->getInput() == Inputs::input::G) {
            _dispMods[_curDispMod]->destroyWindow();
            if (_curDispMod == 0)
                _curDispMod = _dispMods.size() - 1;
            else
                --_curDispMod;
            _dispMods[_curDispMod]->initWindow(1000, 800, "arcade");
            _curMenuDispMod = _curDispMod;
        } else if (event->getInput() == Inputs::input::H) {
            _dispMods[_curDispMod]->destroyWindow();
            if (_curDispMod == _dispMods.size() - 1)
                _curDispMod = 0;
            else
                ++_curDispMod;
            _dispMods[_curDispMod]->initWindow(1000, 800, "arcade");
            _curMenuDispMod = _curDispMod;
        } else if (event->getInput() == Inputs::input::B) {
            if (_curMenuGameMod == 0)
                _curMenuGameMod = _gameMods.size() - 1;
            else
                --_curMenuGameMod;
        } else if (event->getInput() == Inputs::input::N) {
            if (_curMenuGameMod == _gameMods.size() - 1)
                _curMenuGameMod = 0;
            else
                ++_curMenuGameMod;
        }
    }
    return true;
}

void Core::menu(const std::unique_ptr<Inputs> &event)
{
    if (!menuEvents(event))
        return;
    _dispMods[_curDispMod]->drawBackground("assets/menu/bg.png");
    _dispMods[_curDispMod]->drawText({.x = 15, .y = 13, .text = "prev graphical lib:   G", .width = 400, .height = 12, .selected = false, .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    _dispMods[_curDispMod]->drawText({.x = 15, .y = 14, .text = "next graphical lib:   H", .width = 400, .height = 12, .selected = false, .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    _dispMods[_curDispMod]->drawText({.x = 15, .y = 15, .text = "prev game lib:   B", .width = 400, .height = 12, .selected = false, .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    _dispMods[_curDispMod]->drawText({.x = 15, .y = 16, .text = "next game lib:   N", .width = 400, .height = 12, .selected = false, .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    _dispMods[_curDispMod]->drawText({.x = 15, .y = 17, .text = "restart the game:   R", .width = 400, .height = 12, .selected = false, .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    _dispMods[_curDispMod]->drawText({.x = 15, .y = 18, .text = "pause the game:   P", .width = 400, .height = 12, .selected = false, .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    _dispMods[_curDispMod]->drawText({.x = 15, .y = 19, .text = "go back to menu:   M", .width = 400, .height = 12, .selected = false, .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    _dispMods[_curDispMod]->drawText({.x = 15, .y = 20, .text = "start the game:   SPACE", .width = 400, .height = 12, .selected = false, .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    _dispMods[_curDispMod]->drawText({.x = 15, .y = 24, .text = "Your name: " + _curUserName, .width = 400, .height = 12, .selected = (_selector == NAME), .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    _dispMods[_curDispMod]->drawText({.x = 15, .y = 25, .text = "Selected graphical lib: " + _dispMods[_curMenuDispMod]->getName(), .width = 400, .height = 12, .selected = (_selector == GRAPHIC), .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    _dispMods[_curDispMod]->drawText({.x = 15, .y = 26, .text = "Selected game lib: " + _gameMods[_curMenuGameMod]->getName(), .width = 400, .height = 12, .selected = (_selector == GAME), .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
}

bool Core::gameEvents(const std::unique_ptr<Inputs> &event)
{
    if (!bothEvents(event))
        return false;
    else if (event->getInput() == Inputs::input::P) {
        _paused = (_paused == true) ? false : true;
    } else if (event->getInput() == Inputs::input::R) {
        _gameMods[_curGameMod]->restart();
        _paused = false;
    } else if (event->getInput() == Inputs::input::M) {
        _gameMods[_curGameMod]->restart();
        _paused = false;
        _curGameMod = MENU;
        return false;
    } else if (event->getInput() == Inputs::input::G) {
        _dispMods[_curDispMod]->destroyWindow();
        if (_curDispMod == 0)
            _curDispMod = _dispMods.size() - 1;
        else
            --_curDispMod;
        _dispMods[_curDispMod]->initWindow(1000, 800, "arcade");
        _curMenuDispMod = _curDispMod;
    } else if (event->getInput() == Inputs::input::H) {
        _dispMods[_curDispMod]->destroyWindow();
        if (_curDispMod == _dispMods.size() - 1)
            _curDispMod = 0;
        else
            ++_curDispMod;
        _dispMods[_curDispMod]->initWindow(1000, 800, "arcade");
        _curMenuDispMod = _curDispMod;
    } else if (event->getInput() == Inputs::input::B) {
        _gameMods[_curGameMod]->restart();
        _paused = false;
        if (_curGameMod == 0)
            _curGameMod = _gameMods.size() - 1;
        else
            --_curGameMod;
        _curMenuGameMod = _curGameMod;
        return false;
    } else if (event->getInput() == Inputs::input::N) {
        _gameMods[_curGameMod]->restart();
        _paused = false;
        if (_curGameMod == static_cast<int>(_gameMods.size() - 1))
            _curGameMod = 0;
        else
            ++_curGameMod;
        _curMenuGameMod = _curGameMod;
        return false;
    }
    return true;
}

void Core::game(const std::unique_ptr<Inputs> &event)
{
    if (!gameEvents(event))
        return;
    _dispMods[_curDispMod]->drawText({.x = 2, .y = 2 , .text = "Score: " + std::to_string(_gameMods[_curGameMod]->getScore()), .width = 100, .height = 25, .selected = false, .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    _gameMods[_curGameMod]->processInput(event);
    if (_paused == true)
        _dispMods[_curDispMod]->drawText({.x = 2, .y = 4, .text = "PAUSE", .width = 100, .height = 25, .selected = false, .ncurses = TEXT_NCURSES, .other = TEXT_OTHER});
    else {
        _gameMods[_curGameMod]->update();
        if (_gameMods[_curGameMod]->getGameOver() == true) {
            _users_score.emplace_back(std::make_pair(_curUserName, std::make_pair(_gameMods[_curGameMod]->getName(), _gameMods[_curGameMod]->getScore())));
            _gameMods[_curGameMod]->restart();
        }
    }
    _dispMods[_curDispMod]->drawLayers(_gameMods[_curGameMod]->getLayers(), _gameMods[_curGameMod]->getMapSize());
}
