/*
** EPITECH PROJECT, 2022
** foo.cpp
** File description:
** foo
*/

#include "foo.hpp"

extern "C"
{
    std::unique_ptr<IDisplayModule> entryPoint(const std::string &path)
    {
        return (std::make_unique<FooModule>(path));
    }
}

FooModule::FooModule(const std::string &name) : _name(name)
{
    std::cout << "[" << _name << "] Loading SFML library..." << std::endl;
}

FooModule::~FooModule()
{
    std::cout << "[" << _name << "] SFML closing..." << std::endl;
}

void FooModule::destroyWindow()
{
    _window.close();
}

void FooModule::clear()
{
    _window.clear(sf::Color::Black);
}

void FooModule::display()
{
    _window.display();
}

const std::string &FooModule::getName() const
{
    return _name;
}

std::unique_ptr<Inputs> FooModule::event()
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return std::make_unique<Inputs>(Inputs::type::MOUSE, Inputs::input::CLOSE);
    
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::RIGHT);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::LEFT);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::TOP);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::DOWN);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::ENTER);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::SPACE);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::A);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::B);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::C);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::D);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::E);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::F);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::G);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::H);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::I);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::J)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::J);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::K);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::L);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::M);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::N);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::O);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::P);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::Q);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::R);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::S);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::T);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::U);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::V);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::W);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::X);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::Y);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::Z);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
            return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::BACKSPACE);
    }
    return std::make_unique<Inputs>(Inputs::type::NONE);
}

void FooModule::initWindow(int width, int height, const std::string &name)
{
    _window.create(sf::VideoMode(width, height), name + "_sfml", sf::Style::Titlebar | sf::Style::Close);
    _font.loadFromFile("assets/font_arcade.TTF");
    _text.setFont(_font);
}

void FooModule::drawBackground(const std::string &path)
{
    sf::Vector2u window_size = _window.getSize();
    sf::Texture texture;
    sf::RectangleShape rect_shape;

    texture.loadFromFile(path);
    rect_shape.setTexture(&texture);
    rect_shape.setSize({static_cast<float>(window_size.x), static_cast<float>(window_size.y)});
    rect_shape.setPosition(0, 0);
    _window.draw(rect_shape);
}

void FooModule::drawText(const myText &text)
{
    _text.setString(text.text);
    _text.setCharacterSize(11);
    if (text.selected == true)
        _color = {SELECTED_COLOR.r, SELECTED_COLOR.g, SELECTED_COLOR.b, SELECTED_COLOR.a};
    else
        _color = {text.other.r, text.other.g, text.other.b, text.other.a};
    _text.setFillColor(_color);
    _text.setPosition(text.x * PIXEL_SIZE, text.y * PIXEL_SIZE);
    _window.draw(_text);
}

void FooModule::drawPixel(const myPixel &pixel, const std::pair<int, int> &map_size)
{
    sf::Vector2u window_size = _window.getSize();
    sf::RectangleShape rect_shape;

    rect_shape.setSize({PIXEL_SIZE, PIXEL_SIZE});
    rect_shape.setPosition(window_size.x / 2 - PIXEL_SIZE * map_size.first / 2 + PIXEL_SIZE * pixel.x, window_size.y / 2 - PIXEL_SIZE * map_size.second / 2 + PIXEL_SIZE * pixel.y);
    if (pixel.other.pathText.empty()) {
        _color = {pixel.other.color.other.r, pixel.other.color.other.g, pixel.other.color.other.b, pixel.other.color.other.a};
        rect_shape.setFillColor(_color);
        _window.draw(rect_shape);
    } else {
        sf::Texture texture;
        texture.loadFromFile(pixel.other.pathText);
        rect_shape.setTexture(&texture);
        _window.draw(rect_shape);
    }
}

void FooModule::drawLayers(const std::vector<myPixel> &layers, const std::pair<int, int> &map_size)
{
    for (std::size_t i = 0; i < layers.size(); ++i)
        drawPixel(layers[i], map_size);
}
