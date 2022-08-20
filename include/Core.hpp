/*
** EPITECH PROJECT, 2022
** Core.hpp
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "DLLoader.hpp"
#include <cstring>
#include <filesystem>
#include <unordered_map>

#define MENU -1

enum Selector {
    NAME = 0,
    GRAPHIC,
    GAME
};

static const NcursesColor TEXT_NCURSES = {.text_in = COLOR_WHITE, .text_out = COLOR_BLACK};
static const OtherColor TEXT_OTHER = {.r = 255, .g = 255, .b = 255, .a = 255};

class Core {
public:
    Core(const std::string &path);
    ~Core() = default;

    void loop();

protected:
private:
    std::vector<std::unique_ptr<DLLoader<IDisplayModule, ent_point_gr_ptr>>> _dispModsLoader;
    std::vector<std::unique_ptr<DLLoader<IGameModule, ent_point_gm_ptr>>> _gameModsLoader;
    std::vector<std::unique_ptr<IDisplayModule>> _dispMods;
    std::vector<std::unique_ptr<IGameModule>> _gameMods;
    std::size_t _curDispMod;
    int _curGameMod;
    bool _running;
    Selector _selector;
    std::size_t _curMenuDispMod;
    std::size_t _curMenuGameMod;
    std::string _curUserName;
    std::vector<std::pair<std::string, std::pair<std::string, std::size_t>>> _users_score;
    bool _paused;
    int modExists(const std::string &mod_name, const std::string &path);
    bool bothEvents(const std::unique_ptr<Inputs> &event);
    bool menuEvents(const std::unique_ptr<Inputs> &event);
    void menu(const std::unique_ptr<Inputs> &event);
    bool gameEvents(const std::unique_ptr<Inputs> &event);
    void game(const std::unique_ptr<Inputs> &event);
};

#endif /* !CORE_HPP_ */
