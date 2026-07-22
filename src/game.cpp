#include "game.hpp"
#include "constants.hpp"
#include "snake.hpp"
#include <raylib.h>
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

Game::Game() {
	this->food_group = new LinkedList();
}

Game::~Game() {
	delete this->game_ui;
	Node *curr = this->food_group->head;
	Node *old_curr;
	while (curr != nullptr) {
		old_curr = curr;
		curr = curr->next;
		delete (Rectangle *)old_curr->data;
		delete old_curr;
	}
	delete this->food_group;
}

Vector2 food_pos[MAX_FOOD_GROUP_SIZE]; // this array is used to check for food overlaps

Rectangle *Game::spawn_food(Snake *snake) {
	int col = GetRandomValue(1, COLS);
	int row = GetRandomValue(1, ROWS);
	food_pos[0] = {(float)col, (float)row};
	Vector2 grid_pos_to_pixel = {row * (float)MAP_CELL_SIZE - (float)MAP_CELL_SIZE, col * (float)MAP_CELL_SIZE - (float)MAP_CELL_SIZE};
	Vector2 offset_pos = Vector2Add(grid_pos_to_pixel, BORDER_POS);
	Node *curr_snake = snake->snake_body->head;
	SnakeSegment *curr_snake_segment = (SnakeSegment *)curr_snake->data;
	int i = 0;
	while (curr_snake != nullptr) {
		curr_snake_segment = (SnakeSegment *)curr_snake->data;
		if (offset_pos == (Vector2){curr_snake_segment->pos.x, curr_snake_segment->pos.y}) { // repositions the food if it overlaps with snake
			curr_snake = snake->snake_body->head; // resets the curr to make sure it scans the entire snake
			row = GetRandomValue(1, ROWS);
			col = GetRandomValue(1, COLS);
			i++;
			food_pos[i] = {(float)col, (float)row};
			while (Vector2Equals((Vector2){(float)col, (float)row}, food_pos[i])) {
		 	// continously checks and reassigns row and col if there are overlaps between each food
				row = GetRandomValue(1, ROWS);
				col = GetRandomValue(1, COLS);
			}
			grid_pos_to_pixel = {row * (float)MAP_CELL_SIZE - (float)MAP_CELL_SIZE, col * (float)MAP_CELL_SIZE - (float)MAP_CELL_SIZE};
			offset_pos = Vector2Add(grid_pos_to_pixel, BORDER_POS);
		}
		curr_snake = curr_snake->next;
	}
	return new Rectangle({offset_pos.x, offset_pos.y, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE});
}

void Game::spawn_food_group(Snake *snake) {
	Rectangle *new_food;
	int amount_to_generate = MAX_FOOD_GROUP_SIZE;
	if (MAX_AMOUNT_OF_CELLS - snake->snake_body->size < MAX_FOOD_GROUP_SIZE) {
		// if snake gets too big, reduce amount of food to spawn
		amount_to_generate = MAX_AMOUNT_OF_CELLS - snake->snake_body->size;
	}

	for (int i = 0; i < amount_to_generate; i++) {
		new_food = this->spawn_food(snake);
		food_group->append(new_food);
	}
	this->food_group->size = amount_to_generate;
}

void Game::food_group_collision_check(Snake *snake) {
	Node *curr = this->food_group->head;
	Rectangle *curr_food = (Rectangle *)curr->data;
	while (curr != nullptr) {
		curr_food = (Rectangle *)curr->data;
		if (snake->food_collision_check(curr_food)) {
			snake->append_snake();
			this->score++;
			delete curr_food;
			this->food_group->delete_node(curr);
			return;
		}
		curr = curr->next;
	}
}

void Game::handle_empty_food_group(Snake *snake) {
	if (this->food_group->size == 0)
		this->spawn_food_group(snake);
}

void Game::draw_foods(Vector2 center) {
	Node *curr = this->food_group->head;
	Rectangle *curr_food = (Rectangle *)curr->data;
	while (curr != nullptr) {
		curr_food = (Rectangle *)curr->data;
		Vector2 curr_food_pos = Vector2Add(DYNAMIC_OFFSET(center), Vector2Subtract({curr_food->x, curr_food->y}, BORDER_POS));
		Vector2 offset_pos = Vector2Add(Vector2Add(curr_food_pos, BORDER_POS), {BORDER_OFFSET, BORDER_OFFSET});
		DrawRectangle(offset_pos.x, offset_pos.y, curr_food->width, curr_food->height, RED);
		curr = curr->next;
	}
}

void Game::game_intro_text(Vector2 snake_dir, Vector2 center) {
	if (!this->game_started) {
		DrawText(GAME_INTRO_TEXT, GAME_INTRO_TEXT_POS.x + DYNAMIC_OFFSET(center).x, GAME_INTRO_TEXT_POS.y + BORDER_OFFSET + DYNAMIC_OFFSET(center).y, 25, GREEN);
	}

	if (snake_dir != (Vector2){0, 0} && !game_started) {
		this->game_started = true;
	}
}
