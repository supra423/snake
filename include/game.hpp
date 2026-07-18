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
	Border (Vector2 pos, float thickness, float width, float height) {
		this->pos = pos;
		this->thickness = thickness;
		this->width = width;
		this->height = height;
	}
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
};

class Game {
	public:
	GameUI *game_ui;
	int score;
	bool paused = true;
	bool food_eaten = false;
	~Game() {
		delete this->game_ui->border;
		delete this->game_ui->map;
		delete this->game_ui;
	}

	Rectangle *spawn_food(Vector2 center) {
		int row = GetRandomValue(1, MAP_ROWS);
		int col = GetRandomValue(1, MAP_COLS);
		Vector2 grid_pos_to_pixel = {row * MAP_CELL_SIZE - MAP_CELL_SIZE, col * MAP_CELL_SIZE - MAP_CELL_SIZE};
		Vector2 offset_pos = Vector2Add(Vector2Add(grid_pos_to_pixel, BORDER_POS), {BORDER_OFFSET + 1, BORDER_OFFSET + 1});
		Rectangle *food = new Rectangle({offset_pos.x, offset_pos.y, 20, 20});
		return food;
	}
};
#endif
