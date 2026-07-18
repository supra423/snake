#include "snake.hpp"
#include "game.hpp"
#include "constants.hpp"
#include <cstdio>
#include <raylib.h>
#include <raymath.h>

void draw_map(Vector2 border_pos, float map_cell_size) {
	Vector2 curr_cell = border_pos;
	Vector2 offset = {2.0f, 2.0f};
	for (int i = 0; i < MAP_COLS; i++) {
		for (int j = 0; j < MAP_ROWS; j++) {
			DrawLineV({curr_cell.x + offset.x, curr_cell.y + offset.y}, 
					{curr_cell.x + offset.x + CELL_CORNER_LINE_LENGTH, curr_cell.y + offset.y},
					GREEN); // top left line horizontal
			DrawLineV({curr_cell.x + offset.x, curr_cell.y + CELL_CORNER_LINE_LENGTH + offset.y + 1},
					{curr_cell.x + offset.x, curr_cell.y + offset.y},
					GREEN); // top left line vertical

			DrawLineV({curr_cell.x + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH * 2.0f) + offset.x / 2.0f, curr_cell.y + offset.y},
					{curr_cell.x + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH * 2.0f) + CELL_CORNER_LINE_LENGTH + offset.x, curr_cell.y + offset.y},
					GREEN); // top right line horizontal
			DrawLineV({curr_cell.x + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH) + offset.x, curr_cell.y + offset.y},
					{curr_cell.x + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH) + offset.x, curr_cell.y + CELL_CORNER_LINE_LENGTH + offset.y + 1},
					GREEN); // top right line vertical

			DrawLineV({curr_cell.x + offset.x, curr_cell.y + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH) + offset.y}, 
					{curr_cell.x + offset.x + CELL_CORNER_LINE_LENGTH, curr_cell.y + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH) + offset.y},
					GREEN); // bot left line horizontal
			DrawLineV({curr_cell.x + offset.x, curr_cell.y + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH) + offset.y + 1},
					{curr_cell.x + offset.x, curr_cell.y + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH * 2.0f) + offset.y}, 
					GREEN); // bot left line vertical

			DrawLineV({curr_cell.x + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH) + offset.x, curr_cell.y + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH) + offset.y}, 
					{curr_cell.x + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH * 2.0f) + offset.x - 1, curr_cell.y + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH) + offset.y},
					GREEN); // bot right line horizontal
			DrawLineV({curr_cell.x + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH) + offset.x, curr_cell.y + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH) + offset.y}, 
					{curr_cell.x + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH) + offset.x, curr_cell.y + (INNER_CELL_SIZE - CELL_CORNER_LINE_LENGTH * 2.0f) + offset.y},
					GREEN); // bot right line vertical
			curr_cell.x += map_cell_size;
		}
		curr_cell.y += map_cell_size;
		curr_cell.x = border_pos.x;
	}
}

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, WINDOW_TITLE);
	Game *game = new Game;
	game->game_ui = new GameUI;
	game->game_ui->border = new Border(BORDER_POS, BORDER_THICKNESS, BORDER_WIDTH, BORDER_HEIGHT);
	game->game_ui->map = new Map(MAP_ROWS, MAP_COLS, MAP_CELL_SIZE);
	SetTargetFPS(FPS);
	Vector2 center;
	Vector2 border_pos;
	Border *border = game->game_ui->border;
	Map *map = game->game_ui->map;
	Snake *snake = new Snake;
	snake->append();
	Rectangle *food;
	game->food_eaten = true;

	while (WindowShouldClose() == false) {
		BeginDrawing();
		ClearBackground(BLACK);
		center = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
		border_pos = Vector2Add(DYNAMIC_OFFSET, border->pos);
		if (game->food_eaten) {
			food = game->spawn_food(center);
			game->food_eaten = false;
		}
		draw_map(border_pos, map->cell_size);
		DrawRectangleLinesEx({border_pos.x - border->thickness - BORDER_OFFSET, border_pos.y - border->thickness - BORDER_OFFSET, border->width + border->thickness + BORDER_OFFSET, border->height + border->thickness + BORDER_OFFSET}, border->thickness, GREEN);
		if (!game->food_eaten) {
			DrawRectangle(food->x + DYNAMIC_OFFSET.x, food->y + DYNAMIC_OFFSET.y, food->width, food->height, RED);
		}
		snake->change_dir();
		snake->update();
		snake->draw(center);
		std::cout << snake->size << std::endl;
		if (snake->is_food_eaten(food)) {
			game->food_eaten = true;
			snake->append();
			delete food;
		}
		EndDrawing();
	}
	CloseWindow();
	delete game;
	return 0;
}
