#include "snake.hpp"
#include "game.hpp"
#include "constants.hpp"
#include <raylib.h>
#include <raymath.h>
#include <string>

void draw_map_lines (Vector2 center) { // for debug
	Vector2 start_pos = BORDER_POS;
	Vector2 end_pos = {BORDER_POS.x, BORDER_POS.y + BORDER_HEIGHT};
	for (int i = 0; i <= ROWS; i++) {
		DrawLineV(Vector2Add(start_pos, DYNAMIC_OFFSET(center)), Vector2Add(end_pos, DYNAMIC_OFFSET(center)), GREEN);
		start_pos.x += 40;
		end_pos.x += 40;
	}
	start_pos = BORDER_POS;
	end_pos = {BORDER_POS.x + BORDER_WIDTH, BORDER_POS.y};
	for (int i = 0; i <= COLS; i++) {
		DrawLineV(Vector2Add(start_pos, DYNAMIC_OFFSET(center)), Vector2Add(end_pos, DYNAMIC_OFFSET(center)), GREEN);
		start_pos.y += 40;
		end_pos.y += 40;
	}
}

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
	snake->append_snake();
	Rectangle *food = game->spawn_food(snake);
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
		score_string = "SCORE: " + std::to_string(game->score);
		game->game_intro_text(snake->dir, center);
		if (snake->food_collision_check(food)) {
			game->food_eaten = true;
			snake->append_snake();
			game->score++;
			delete food;
		}

		if (game->food_eaten) {
			food = game->spawn_food(snake);
			game->food_eaten = false;
		} else
			if (game->game_started)
				DrawRectangle(food->x + DYNAMIC_OFFSET(center).x + BORDER_OFFSET,
					food->y + DYNAMIC_OFFSET(center).y + BORDER_OFFSET,
					food->width,
					food->height, RED);
		

		if (snake->snake_bounds_check() /*|| snake->snake_self_collision()*/)  {
			delete snake;
			snake = new Snake;
			snake->append_snake();
			game->score = 0;
		}

		DrawRectangleLinesEx({border_pos.x, border_pos.y, border->width, border->height}, border->thickness, GREEN);
		DrawText(score_string.c_str(), score_pos.x, score_pos.y, SCORE_FONT_SIZE, GREEN);

		if (!game->paused) {
			snake->change_dir();
			snake->update();
		} else {
			DrawText("PAUSED", PAUSE_TEXT_POS(center).x, PAUSE_TEXT_POS(center).y, PAUSE_FONT_SIZE, GREEN);
		}

		if (IsKeyPressed(KEY_SPACE) && game->paused == false) {
			game->paused = true;
		} else if (IsKeyPressed(KEY_SPACE) && game->paused == true) {
			game->paused = false;
		}

		snake->draw(center);
		EndDrawing();
	}
	delete game;
	delete food;
	delete snake;
	CloseWindow();
	return 0;
}
