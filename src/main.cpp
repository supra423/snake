#include "snake.hpp"
#include "game.hpp"
#include "constants.hpp"
#include <raylib.h>
#include <raymath.h>
#include <string>

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, WINDOW_TITLE);
	Game *game = new Game;
	game->game_ui = new GameUI;
	game->game_ui->border = new Border(BORDER_POS, BORDER_THICKNESS, BORDER_WIDTH, BORDER_HEIGHT);
	game->game_ui->map = new Map(ROWS, COLS, MAP_CELL_SIZE);
	SetTargetFPS(FPS);
	Vector2 center;
	Vector2 border_pos;
	Border *border = game->game_ui->border;
	Snake *snake = new Snake;
	snake->append();
	Rectangle *food = game->spawn_food(snake->head);
	game->food_eaten = false;
	game->game_ui->score_pos = {BORDER_POS.x, BORDER_POS.y + BORDER_HEIGHT};
	std::string score_string;
	Vector2 score_pos;

	while (WindowShouldClose() == false) {
		BeginDrawing();
		ClearBackground(BLACK);
		center = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
		score_pos = Vector2Add(DYNAMIC_OFFSET(center), game->game_ui->score_pos);
		border_pos = Vector2Add(DYNAMIC_OFFSET(center), border->pos);
		score_string = std::to_string(game->score);
		if (game->food_eaten) {
			food = game->spawn_food(snake->head);
			game->food_eaten = false;
		}
		DrawRectangleLinesEx({border_pos.x - BORDER_OFFSET, border_pos.y - BORDER_OFFSET, border->width + BORDER_OFFSET - 6, border->height + BORDER_OFFSET - 6}, border->thickness, GREEN);
		DrawText(score_string.c_str(), score_pos.x, score_pos.y, SCORE_FONT_SIZE, GREEN);
		if (!game->food_eaten) DrawRectangle(food->x + DYNAMIC_OFFSET(center).x, food->y + DYNAMIC_OFFSET(center).y, food->width, food->height, RED);
		if (snake->is_food_eaten(food)) {
			game->food_eaten = true;
			snake->append();
			game->score++;
			delete food;
		}
		if (snake->snake_bounds_check() || snake->snake_self_collision())  {
			delete snake;
			snake = new Snake;
			snake->append();
			game->score = 0;
		}
		snake->change_dir();
		snake->update();
		snake->draw(center);
		// printf("%d", MAP_CELL_SIZE);
		EndDrawing();
	}
	delete game;
	delete food;
	delete snake;
	CloseWindow();
	return 0;
}
