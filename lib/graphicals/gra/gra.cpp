/*
** EPITECH PROJECT, 2022
** gra.cpp
** File description:
** gra
*/

#include "gra.hpp"

extern "C"
{
    std::unique_ptr<IDisplayModule> entryPoint(const std::string &path)
    {
        return (std::make_unique<GraModule>(path));
    }
}

GraModule::GraModule(const std::string &name) : _name(name)
{
    std::cout << "[" << _name << "] Loading SDL2 library..." << std::endl;
}

GraModule::~GraModule()
{
    std::cout << "[" << _name << "] SDL2's getting out..." << std::endl;
}

void GraModule::initWindow(int width, int height, const std::string &name)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    this->_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    this->_font = TTF_OpenFont("assets/font_arcade.TTF", 30);
}

void GraModule::display()
{
    SDL_RenderPresent(this->_renderer);   
}

void GraModule::destroyWindow()
{
    TTF_CloseFont(this->_font);
    SDL_DestroyRenderer(this->_renderer);
    SDL_DestroyWindow(this->_window);
    TTF_Quit();
    SDL_Quit();
}

void GraModule::clear()
{
    SDL_RenderClear(_renderer);
}

std::unique_ptr<Inputs> GraModule::event()
{
    SDL_Event events;

    while (SDL_PollEvent(&events)) {
        if (events.type == SDL_QUIT) {
            return std::make_unique<Inputs>(Inputs::type::MOUSE, Inputs::input::CLOSE);
        }
        if (events.type == SDL_KEYDOWN) {
            switch (events.key.keysym.sym) {
                case SDLK_LEFT: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::LEFT);
                case SDLK_RIGHT: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::RIGHT);
                case SDLK_UP: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::TOP);
                case SDLK_DOWN: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::DOWN);
                case SDLK_RETURN: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::ENTER);
                case SDLK_SPACE: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::SPACE);
                case SDLK_a: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::A);
                case SDLK_b: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::B);
                case SDLK_c: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::C);
                case SDLK_d: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::D);
                case SDLK_e: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::E);
                case SDLK_f: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::F);
                case SDLK_g: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::G);
                case SDLK_h: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::H);
                case SDLK_i: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::I);
                case SDLK_j: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::J);
                case SDLK_k: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::K);
                case SDLK_l: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::L);
                case SDLK_m: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::M);
                case SDLK_n: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::N);
                case SDLK_o: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::O);
                case SDLK_p: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::P);
                case SDLK_q: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::Q);
                case SDLK_r: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::R);
                case SDLK_s: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::S);
                case SDLK_t: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::T);
                case SDLK_u: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::U);
                case SDLK_v: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::V);
                case SDLK_w: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::W);
                case SDLK_x: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::X);
                case SDLK_y: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::Y);
                case SDLK_z: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::Z);
                case SDLK_BACKSPACE: return std::make_unique<Inputs>(Inputs::type::KEYBOARD, Inputs::input::BACKSPACE);
            }
        }
        break;
    }
    return std::make_unique<Inputs>(Inputs::type::NONE);
}

const std::string &GraModule::getName() const
{
    return _name;
}

void GraModule::drawBackground(const std::string &path)
{
    int w, h;
    SDL_GetWindowSize(_window, &w, &h);
    SDL_Rect r = {0, 0, w, h};

    this->_texture = IMG_LoadTexture(this->_renderer, path.c_str());
    SDL_RenderCopy(this->_renderer, this->_texture, NULL, &r);
    SDL_DestroyTexture(this->_texture);
}

void GraModule::drawText(const myText &text)
{
    SDL_Rect position = {text.x * PIXEL_SIZE, text.y * PIXEL_SIZE, text.width, text.height};

    if (text.selected == true)
        this->_color = {SELECTED_COLOR.r, SELECTED_COLOR.g, SELECTED_COLOR.b, SELECTED_COLOR.a};
    else
        this->_color = {text.other.r, text.other.g, text.other.b, text.other.a};
    this->_text = TTF_RenderText_Solid(this->_font, text.text.c_str(), this->_color);
    this->_message = SDL_CreateTextureFromSurface(this->_renderer, this->_text);
    SDL_RenderCopy(this->_renderer, this->_message, NULL, &position);
    SDL_FreeSurface(this->_text);
    SDL_DestroyTexture(this->_message);
}

void GraModule::drawPixel(const myPixel &pixel, const std::pair<int, int> &map_size)
{
    int w, h;
    SDL_GetWindowSize(_window, &w, &h);
    SDL_Rect r = {w / 2 - (PIXEL_SIZE * map_size.first / 2) + PIXEL_SIZE * pixel.x, h / 2 - (PIXEL_SIZE * map_size.second / 2) + PIXEL_SIZE * pixel.y, PIXEL_SIZE, PIXEL_SIZE};

    if (pixel.other.pathText.empty()) {
        this->_color = {pixel.other.color.other.r, pixel.other.color.other.g, pixel.other.color.other.b, pixel.other.color.other.a};
        SDL_SetRenderDrawColor(this->_renderer, _color.r, _color.g, _color.b, _color.a);
        SDL_RenderFillRect(this->_renderer, &r);
    } else {
        this->_texture = IMG_LoadTexture(this->_renderer, pixel.other.pathText.c_str());
        SDL_RenderCopy(this->_renderer, this->_texture, NULL, &r);
        SDL_DestroyTexture(this->_texture);
    }
}

void GraModule::drawLayers(const std::vector<myPixel> &layers, const std::pair<int, int> &map_size)
{
    for (std::size_t i = 0; i < layers.size(); ++i)
        drawPixel(layers[i], map_size);
}
