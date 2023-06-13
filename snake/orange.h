#pragma once

#include "food.h"
#include "orange.h"

class Orange : public Food {
public:
	std::string type() override {
		return ORANGE_IMG_PATH;
	}
	int score() override {
		return ORANGE_SCORE;
	}
};
