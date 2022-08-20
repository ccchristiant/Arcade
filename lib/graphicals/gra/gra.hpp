/*
** EPITECH PROJECT, 2022
** gra.hpp
** File description:
** gra
*/

#ifndef GRA_HPP_
#define GRA_HPP_

#include "IDisplayModule.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

static const OtherColor SELECTED_COLOR = {.r = 255, .g = 213, .b = 0, .a = 255};

class GraModule : public IDisplayModule {
public:
    GraModule(const std::string &name);
    ~GraModule();

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
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    SDL_Texture * _texture;
    TTF_Font *_font;
    SDL_Color _color;
    SDL_Surface *_text;
    SDL_Texture* _message;
};

#endif /* !GRA_HPP_ */
