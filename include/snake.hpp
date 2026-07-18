#ifndef SNAKE_HPP
#define SNAKE_HPP
// I figured that the snake is actually a linked list.
// Well, I could definitely use std::deque for this but
// I'm bored, and severely autistic
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdint.h>
#include "constants.hpp"
#include <iostream>
#include <string>

class SnakeSegment {
	public:
	Vector2 pos;
	SnakeSegment *next;
	SnakeSegment(Vector2 pos) {
		this->pos = pos;
	}
	SnakeSegment() {
	}
};

class Snake {
	public:
	SnakeSegment *head;
	SnakeSegment *tail;
	Vector2 dir = {0, 0};
	Vector2 next_dir = {0, 0};
	size_t size = 0;
	double last_update_time = 0.0;
	float move_timer = 0.0f;
    float move_interval = 0.15f;
	bool allow_move = false;

	~Snake() {
		SnakeSegment *curr = this->head;
		SnakeSegment *old_curr;
		for (size_t i = 0; i < this->size; i++) {
			old_curr = curr;
			curr = curr->next;
			delete old_curr;
		}
	}

	void update() {
        float dt = GetFrameTime();
        move_timer += dt;

        if (move_timer >= move_interval) {
            move_timer -= move_interval;
            this->move();
        }
    }

	void append() {
		SnakeSegment *new_segment = new SnakeSegment;
		if (this->size == 0) {
			new_segment->pos = SNAKE_STARTING_POSITION;
			this->head = new_segment;
			this->tail = new_segment;
			this->size++;
			return;
		}
		SnakeSegment *old_tail = this->tail;
		this->tail = new_segment;
		old_tail->next = new_segment;
		this->size++;
	}

	void change_dir() {
		if (IsKeyPressed(KEY_UP) && this->dir != (Vector2){0, 1}) {
			this->next_dir = {0, -1};
		} else if (IsKeyPressed(KEY_LEFT) && this->dir != (Vector2){1, 0}) {
			this->next_dir = {-1, 0};
		} else if (IsKeyPressed(KEY_DOWN) && this->dir != (Vector2){0, -1}) {
			this->next_dir = {0, 1};
		} else if (IsKeyPressed(KEY_RIGHT) && this->dir != (Vector2){-1, 0}) {
			this->next_dir = {1, 0};
		}
		allow_move = true;
	}
	
	void move() {
		SnakeSegment *curr = this->head;
		Vector2 old_curr_pos = curr->pos;
		Vector2 old_next_pos;
		this->dir = this->next_dir;
		this->head->pos.x += this->dir.x * MAP_CELL_SIZE;
		this->head->pos.y += this->dir.y * MAP_CELL_SIZE;

		for (size_t i = 0; i < this->size - 1; i++) {
			// if (curr->next == nullptr) {
			// 	break;
			// }
			old_next_pos = curr->next->pos;
			curr->next->pos = old_curr_pos;
			curr = curr->next;
			old_curr_pos = old_next_pos;
		}
	}

	void draw(Vector2 center) {
		Vector2 pos_in_grid;
		SnakeSegment *curr = this->head;
		std::string text;

		for (size_t i = 0; i < this->size; i++) {
			int pos_in_grid_x = floor(((curr->pos.x - BORDER_POS.x) / MAP_CELL_SIZE));
			int pos_in_grid_y = floor(((curr->pos.y - BORDER_POS.y) / MAP_CELL_SIZE));

			pos_in_grid = {(float)pos_in_grid_x, (float)pos_in_grid_y};

			Vector2 pos_back_to_pixels;
			float pos_back_to_pixels_x = pos_in_grid_x * MAP_CELL_SIZE;
			float pos_back_to_pixels_y = pos_in_grid_y * MAP_CELL_SIZE;
			pos_back_to_pixels = {pos_back_to_pixels_x, pos_back_to_pixels_y};

			Vector2 segment_pos = Vector2Add(DYNAMIC_OFFSET, pos_back_to_pixels);
			Vector2 rectangle_pos = Vector2Add(Vector2Add(segment_pos, BORDER_POS), {BORDER_OFFSET + 1, BORDER_OFFSET + 1});
			DrawRectangleV(rectangle_pos, {SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE}, GREEN);

			curr = curr->next;
		}
	}

	bool is_food_eaten(Rectangle *food) {
		if (this->head->pos.x + 5 == food->x && this->head->pos.y + 5 == food->y) {
			return true;
		}
		return false;
	}

	bool snake_bounds_check() {
		if (this->head->pos.x + 5 <= BORDER_POS.x ||
				this->head->pos.x >= BORDER_POS.x + BORDER_WIDTH ||
				this->head->pos.y + 5 <= BORDER_POS.y ||
				this->head->pos.y >= BORDER_HEIGHT + MAP_CELL_SIZE) {
			return true;
		}
		return false;
	}
};
#endif
