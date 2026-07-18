#include "game.hpp"

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

Rectangle *Game::spawn_food() {
	int row = GetRandomValue(1, MAP_ROWS);
	int col = GetRandomValue(1, MAP_COLS);
	Vector2 grid_pos_to_pixel = {row * MAP_CELL_SIZE - MAP_CELL_SIZE, col * MAP_CELL_SIZE - MAP_CELL_SIZE};
	Vector2 offset_pos = Vector2Add(Vector2Add(grid_pos_to_pixel, BORDER_POS), {BORDER_OFFSET + 1, BORDER_OFFSET + 1});
	Rectangle *food = new Rectangle({offset_pos.x, offset_pos.y, 20, 20});
	return food;
}
