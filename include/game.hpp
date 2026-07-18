#ifndef GAME_HPP
#define GAME_HPP
#include "constants.hpp"
#include <raylib.h>
#include <raymath.h>

class Border {
	public:
	Vector2 pos;
	int thickness;
	float width;
	float height;
	Border (Vector2 pos, float thickness, float width, float height);
};

class Map {
	public:
	int rows;
	int cols;
	float cell_size;
	Map(int rows, int cols, float cell_size) {
		this->rows = rows;
        this->cols = cols;
        this->cell_size = cell_size;
	}
};

class GameUI {
	public:
	Border *border;
	Map *map;
	Vector2 score_pos;
	~GameUI();
};

class Game {
	public:
	GameUI *game_ui;
	int score = 0;
	bool paused = true;
	bool food_eaten = false;
	~Game();
	Rectangle *spawn_food();
};
#endif
