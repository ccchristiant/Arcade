/*
** EPITECH PROJECT, 2022
** foo.hpp
** File description:
** foo
*/

#ifndef FOO_HPP_
#define FOO_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "IDisplayModule.hpp"

static const OtherColor SELECTED_COLOR = {.r = 255, .g = 213, .b = 0, .a = 255};

class FooModule : public IDisplayModule {
public:
    FooModule(const std::string &name);
    ~FooModule();

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
    sf::RenderWindow _window;
    sf::Font _font;
    sf::Text _text;
    sf::Color _color;
};

#endif /* !FOO_HPP_ */
