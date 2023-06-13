#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <list>
#include "position.h"
#include "size.h"
#include "config.h"


class Draw {
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    TTF_Font* font = nullptr;
    
public:
   Draw() {
        if(TTF_Init() == -1) {
            std::cout << TTF_GetError() << '\n';
        }
        font = TTF_OpenFont(FONT_PATH, 32);
        if(font == nullptr) {
            std::cout << "Could not load font\n";
        }
    }
    void setRenderer(SDL_Renderer* renderer);
    void drawStartView();
    void drawSnake(const std::list<Position>& segments);
    void drawFruit(const std::string& type, Point2D position);
    void drawText(const std::string& text, SDL_Color color, Point2D position, Size size);
};

