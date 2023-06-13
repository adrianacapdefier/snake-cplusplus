#pragma once

#include <SDL.h>
#undef main
#include <string>

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

constexpr int REDRAW_TIMEOUT = 100;
constexpr int GRID_TILE_SIZE = 20;
constexpr int SCENE_X_START = 10;
constexpr int SCENE_Y_START = 100;
constexpr int SCENE_X_END = 1279;
constexpr int SCENE_Y_END = 719;

constexpr int TEXT_FONT_NORMAL = 21;
constexpr int TEXT_FONT_BIG = 32;

constexpr auto FONT_PATH = "C:\\Users\\maria\\OneDrive\\Desktop\\snake\\snake\\roboto.ttf";
constexpr auto SNAKE_IMG_PATH = "C:\\Users\\maria\\OneDrive\\Desktop\\snake\\snake\\snake.jpg";
constexpr auto APPLE_IMG_PATH = "C:\\Users\\maria\\OneDrive\\Desktop\\snake\\snake\\apple.png";
constexpr auto ORANGE_IMG_PATH = "C:\\Users\\maria\\OneDrive\\Desktop\\snake\\snake\\orange.png";
constexpr auto GRAPES_IMG_PATH = "C:\\Users\\maria\\OneDrive\\Desktop\\snake\\snake\\grapes.png";

constexpr int FRUIT_SIZE = 40;
constexpr int SNAKE_SIZE_DEFAULT = 5;
constexpr int FRUIT_HITBOX = 20;

constexpr int SPEED_TURNS = 5;
constexpr int FPS_CAP = 1000 / 60;

constexpr SDL_Color SCENE_BACKGROUND_COLOR = {0x00, 0x00, 0x00, 0xFF};
constexpr SDL_Color SCORE_TEXT_COLOR = {0xFF, 0xFF, 0xFF, 0xFF};
constexpr SDL_Color START_TEXT_COLOR = {0xFF, 0xFF, 0xFF, 0xFF};
constexpr SDL_Color SNAKE_COLOR = {0x00, 0xFF, 0x00, 0xFF};

constexpr int SNAKE_IMG_X = 500;
constexpr int SNAKE_IMG_Y = 150;
constexpr int SNAKE_IMG_W = 200;
constexpr int SNAKE_IMG_H = 200;

constexpr int START_TEXT_X = 530;
constexpr int START_TEXT_Y = 400;
constexpr int START_TEXT_W = 140;

constexpr int APPLE_SCORE = 10;
constexpr int ORANGE_SCORE = 50;
constexpr int GRAPES_SCORE = 100;
