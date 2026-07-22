#ifndef GAME_HPP
#define GAME_HPP
#include <raylib.h>
#include "snake.hpp"

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
	LinkedList *food_group;
	int score = 0;
	bool paused = false;
	bool game_started = false;
	bool food_eaten = false;
	~Game();
	Game();
	Rectangle *spawn_food(Snake *snake);
	void spawn_food_group(Snake *snake);
	void game_intro_text(Vector2 snake_dir, Vector2 center);
	void draw_foods(Vector2 center);
	void food_group_collision_check(Snake *snake);
	void handle_empty_food_group(Snake *snake);
};
#endif
