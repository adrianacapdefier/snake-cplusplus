#pragma once

#include "food.h"
#include "config.h"

class Apple : public Food {
public:
	std::string type() override {
		return APPLE_IMG_PATH;
	}
	int score() override {
		return APPLE_SCORE;
	}
};
