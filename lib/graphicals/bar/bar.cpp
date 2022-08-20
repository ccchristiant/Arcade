/*
** EPITECH PROJECT, 2022
** bar.cpp
** File description:
** bar
*/

#include "bar.hpp"

extern "C"
{
    std::unique_ptr<IDisplayModule> entryPoint(const std::string &path)
    {
        return (std::make_unique<BarModule>(path));
    }
}

BarModule::BarModule(const std::string &name) : _name(name)
{
    std::cout << "[" << _name << "] Loading ncurses library..." << std::endl;
}

BarModule::~BarModule()
{
    std::cout << "[" << _name << "] Closing ncurses..." << std::endl;
}

void BarModule::clear()
{
    erase();
}

void BarModule::initWindow(int width, int height, const std::string &name)
{
    static_cast<void>(width);
    static_cast<void>(height);
    static_cast<void>(name);
    initscr();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    start_color();
    _pair = 1;
}

void BarModule::destroyWindow()
{
    nodelay(stdscr, false);
    endwin();
    erase();
}

void BarModule::display()
{
    refresh();
}

const std::string &BarModule::getName() const
{
    return _name;
}

std::unique_ptr<Inputs> BarModule::event()
{
    int c = getch();
		switch(c) {	
            case 'a': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::A);
            case 'b': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::B);
            case 'c': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::C);
            case 'd': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::D);
            case 'e': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::E);
            case 'f': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::F);
            case 'g': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::G);
            case 'h': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::H);
            case 'i': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::I);
            case 'j': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::J);
            case 'k': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::K);
            case 'l': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::L);
            case 'm': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::M);
            case 'n': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::N);
            case 'o': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::O);
            case 'p': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::P);
            case 'q': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::Q);
            case 'r': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::R);
            case 's': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::S);
            case 't': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::T);
            case 'u': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::U);
            case 'v': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::V);
            case 'w': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::W);
            case 'x': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::X);
            case 'y': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::Y);
            case 'z': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::Z);
            case ' ': return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::SPACE);
            case KEY_ENTER: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::ENTER);
            case KEY_BACKSPACE: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::BACKSPACE);
            case KEY_LEFT: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::LEFT);
            case KEY_RIGHT: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::RIGHT);
            case KEY_DOWN: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::DOWN);
            case KEY_UP: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::TOP);
            default: return std::make_unique<Inputs>(Inputs::type::NONE);
        }
    return std::make_unique<Inputs>(Inputs::type::NONE);
}

void BarModule::drawBackground(const std::string &)
{
}

void BarModule::drawText(const myText &text)
{
    int i = getColorPair(text.ncurses);
    int j;

    if (i != -1) {
        i += (text.selected == true);
        attron(COLOR_PAIR(_color_pairs[i]));
        mvaddstr(text.y, text.x, text.text.c_str());
        attroff(COLOR_PAIR(_color_pairs[i]));
    } else {
        setColorPair(text.ncurses);
        j = getColorPair(text.ncurses);
        j += (text.selected == true);
        attron(COLOR_PAIR(_color_pairs[j]));
        mvaddstr(text.y, text.x, text.text.c_str());
        attroff(COLOR_PAIR(_color_pairs[j]));
    }
}

void BarModule::drawPixel(const myPixel &pixel, const std::pair<int, int> &map_size)
{
    int i = getColorPair(pixel.ncurses.color.ncurses);
    int j;

    if (i != -1) {
        attron(COLOR_PAIR(_color_pairs[i]));
        mvaddch(LINES / 2 - map_size.second / 2 + pixel.y,  COLS / 2 - map_size.first / 2 + pixel.x, pixel.ncurses.c);
        attroff(COLOR_PAIR(_color_pairs[i]));
    } else {
        setColorPair(pixel.ncurses.color.ncurses);
        j = getColorPair(pixel.ncurses.color.ncurses);
        attron(COLOR_PAIR(_color_pairs[j]));
        mvaddch(LINES / 2 - map_size.second / 2 + pixel.y,  COLS / 2 - map_size.first / 2 + pixel.x, pixel.ncurses.c);
        attroff(COLOR_PAIR(_color_pairs[j]));
    }
}

void BarModule::drawLayers(const std::vector<myPixel> &layers, const std::pair<int, int> &map_size)
{
    for (std::size_t i = 0; i < layers.size(); ++i)
        drawPixel(layers[i], map_size);
}

int BarModule::getColorPair(const NcursesColor &color)
{
    short tmp_text_in;
    short tmp_text_out;

    for (std::size_t i = 0; i < _color_pairs.size(); ++i) {
        pair_content(_color_pairs[i], &tmp_text_in, &tmp_text_out);
        if (color.text_in == tmp_text_in && color.text_out == tmp_text_out)
            return i;
    }
    return -1;
}

void BarModule::setColorPair(const NcursesColor &color)
{
    _color_pairs.push_back(_pair);
    init_pair(_pair++, color.text_in, color.text_out);
    _color_pairs.push_back(_pair);
    init_pair(_pair++, color.text_out, color.text_in);
}
