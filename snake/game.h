#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <list>
#include <memory>
#include "snake.h"
#include "food.h"
#include "apple.h"
#include "orange.h"
#include "grapes.h"
#include "config.h"
#include "draw.hpp"

enum GameSM {
    STARTED,
    RUNNING,
    STOPPED,
};

class Game
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    Draw pen;
	Snake* snake = nullptr;
	Food* food = nullptr;
	Direction direction;
	int score;
    bool isQuit;
    SDL_KeyCode keyPressed = SDL_KeyCode::SDLK_UNKNOWN;
    GameSM sm;
public:
	Game(){
		direction = Direction::RIGHT;
	}
    ~Game() {
        delete snake;
        delete food;
    }
	void run();
	void init();
    void initScene();
private:
	bool checkStopCondition();
	void generateRandomFood();
	void moveSnake();
	void checkFood();
	void redraw();
    void getUserInput(SDL_Event* e, bool* quit);
};
