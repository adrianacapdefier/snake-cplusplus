#include "draw.hpp"

void Draw::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Draw::drawStartView() {
    SDL_Texture *img = nullptr;
    int w,h;
    
    img = IMG_LoadTexture(renderer, SNAKE_IMG_PATH);
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    SDL_Rect rectangle; rectangle.x = SNAKE_IMG_X; rectangle.y = SNAKE_IMG_Y; rectangle.w = SNAKE_IMG_W; rectangle.h = SNAKE_IMG_H;
    SDL_RenderCopy(renderer, img, NULL, &rectangle);
    drawText("Press SPACE to play", START_TEXT_COLOR, {START_TEXT_X, START_TEXT_Y}, {START_TEXT_W, TEXT_FONT_BIG});
    
    SDL_DestroyTexture(img);
}

void Draw::drawSnake(const std::list<Position>& segments) {
    for(auto it = segments.begin(); it != segments.end(); it++) {
        SDL_Rect fillRect = { it->currentPosition.x, it->currentPosition.y, GRID_TILE_SIZE, GRID_TILE_SIZE };
        SDL_SetRenderDrawColor( renderer, SNAKE_COLOR.r, SNAKE_COLOR.g, SNAKE_COLOR.b, SNAKE_COLOR.a );
        SDL_RenderFillRect( renderer, &fillRect );
    }
    
    auto head = segments.front();
    
    SDL_Rect snakeFace = { head.currentPosition.x + 8, head.currentPosition.y + 5, 2, 2 };
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( renderer, &snakeFace );

    snakeFace = { head.currentPosition.x + 14, head.currentPosition.y + 5, 2, 2 };
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( renderer, &snakeFace );

    snakeFace = { head.currentPosition.x + 16, head.currentPosition.y + 15, 8, 2 };
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( renderer, &snakeFace );
}

void Draw::drawFruit(const std::string& type, Point2D position) {
    SDL_Texture *img = nullptr;
    int w,h;
    
    img = IMG_LoadTexture(renderer, type.c_str());
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    SDL_Rect rectangle; rectangle.x = position.x; rectangle.y = position.y; rectangle.w = FRUIT_SIZE; rectangle.h = FRUIT_SIZE;
    SDL_RenderCopy(renderer, img, NULL, &rectangle);
    
    SDL_DestroyTexture(img);
}

void Draw::drawText(const std::string& text, SDL_Color color, Point2D position, Size size) {
    SDL_Surface* surfaceText = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
    SDL_Rect rectangle;
    rectangle.x = position.x;
    rectangle.y = position.y;
    rectangle.w = size.width;
    rectangle.h = size.height;
    
    SDL_RenderCopy(renderer, textureText, NULL, &rectangle);
    
    SDL_FreeSurface(surfaceText);
    SDL_DestroyTexture(textureText);
}

