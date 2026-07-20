#include "game.hpp"
#include "constants.hpp"
#include <raymath.h>

Border::Border (Vector2 pos, float thickness, float width, float height) {
	this->pos = pos;
	this->thickness = thickness;
	this->width = width;
	this->height = height;
}

GameUI::~GameUI() {
	delete this->border;
	delete this->map;
}

Game::~Game() {
	delete this->game_ui;
}

Rectangle *Game::spawn_food(Snake *snake) {
	int row = GetRandomValue(1, ROWS);
	int col = GetRandomValue(1, COLS);
	Vector2 grid_pos_to_pixel = {row * (float)MAP_CELL_SIZE - (float)MAP_CELL_SIZE, col * (float)MAP_CELL_SIZE - (float)MAP_CELL_SIZE};
	Vector2 offset_pos = Vector2Add(grid_pos_to_pixel, BORDER_POS);
	SnakeSegment *curr = snake->head;
	while (curr != nullptr) {
		if (curr->next == nullptr) {
			break;
		}
		if (offset_pos == (Vector2){curr->pos.x, curr->pos.y}) { // repositions the food if it overlaps with snake
			curr = snake->head; // resets the curr to make sure it scans the entire snake
			row = GetRandomValue(1, ROWS);
			col = GetRandomValue(1, COLS);
			grid_pos_to_pixel = {row * (float)MAP_CELL_SIZE - (float)MAP_CELL_SIZE, col * (float)MAP_CELL_SIZE - (float)MAP_CELL_SIZE};
			offset_pos = Vector2Add(grid_pos_to_pixel, BORDER_POS);
		}
		curr = curr->next;
	}
	return new Rectangle({offset_pos.x, offset_pos.y, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE});
}
