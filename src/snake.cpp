#include "snake.hpp"
#include "constants.hpp"
#include <raylib.h>
#include <raymath.h>

SnakeSegment::SnakeSegment() {}

Snake::~Snake() {
	SnakeSegment *curr = this->head;
	SnakeSegment *old_curr;
	while (curr != nullptr) {
		old_curr = curr;
		curr = curr->next;
		delete old_curr;
	}
}

void Snake::update() {
	float dt = GetFrameTime();
	move_timer += dt;

	if (move_timer >= MOVE_INTERNAL) {
		move_timer -= MOVE_INTERNAL;
		this->move();
	}
}

void Snake::append() {
	SnakeSegment *new_segment = new SnakeSegment;
	new_segment->next = nullptr;
	if (this->size == 0) {
		new_segment->pos = SNAKE_STARTING_POSITION;
		this->head = new_segment;
		this->tail = new_segment;
		this->size++;
		return;
	}
	new_segment->pos = this->tail->pos;
	SnakeSegment *old_tail = this->tail;
	this->tail = new_segment;
	old_tail->next = new_segment;
	this->size++;
}

void Snake::change_dir() {
	if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_K)) && this->dir != (Vector2){0, 1}) {
		this->next_dir = {0, -1};
	} else if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_H)) && this->dir != (Vector2){1, 0}) {
		this->next_dir = {-1, 0};
	} else if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_J)) && this->dir != (Vector2){0, -1}) {
		this->next_dir = {0, 1};
	} else if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_L)) && this->dir != (Vector2){-1, 0}) {
		this->next_dir = {1, 0};
	}
}

void Snake::move() {
	SnakeSegment *curr = this->head;
	Vector2 old_curr_pos = curr->pos;
	Vector2 old_next_pos;
	this->dir = this->next_dir;
	this->head->pos.x += this->dir.x * MAP_CELL_SIZE;
	this->head->pos.y += this->dir.y * MAP_CELL_SIZE;

	while (curr != nullptr) {
		if (curr->next == nullptr) {
			return;
		}
		old_next_pos = curr->next->pos;
		curr->next->pos = old_curr_pos;
		curr = curr->next;
		old_curr_pos = old_next_pos;
	}
}

void Snake::draw(Vector2 center) {
	SnakeSegment *curr = this->head;
	if (this->snake_bounds_check()) {
		return;
	}
	Vector2 segment_pos = Vector2Add(DYNAMIC_OFFSET(center), Vector2Subtract(curr->pos, BORDER_POS));
	Vector2 rectangle_pos = Vector2Add(Vector2Add(segment_pos, BORDER_POS), {BORDER_OFFSET, BORDER_OFFSET});
	DrawRectangleV(rectangle_pos, {SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE}, GREEN);
	curr = curr->next;

	while (curr != nullptr) {
		segment_pos = Vector2Add(DYNAMIC_OFFSET(center), Vector2Subtract(curr->pos, BORDER_POS));
		rectangle_pos = Vector2Add(Vector2Add(segment_pos, BORDER_POS), {BORDER_OFFSET, BORDER_OFFSET});
		DrawRectangleV(rectangle_pos, {SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE}, DARKGREEN);

		curr = curr->next;
	}
}

bool Snake::food_collision_check(Rectangle *food) {
	if (this->head->pos.x == food->x && this->head->pos.y == food->y) {
		return true;
	}
	return false;
}

bool Snake::snake_bounds_check() {
	if (this->head->pos.x < BORDER_POS.x ||
			this->head->pos.x >= BORDER_POS.x + BORDER_WIDTH ||
			this->head->pos.y < BORDER_POS.y ||
			this->head->pos.y >= BORDER_POS.y + BORDER_HEIGHT) {
		return true;
	}
	return false;
}

bool Snake::snake_self_collision() {
	if (this->size <= 2) {
		return false;
	}
	SnakeSegment *curr = this->head;
	while (curr != nullptr) {
		if (curr->next == nullptr) return false;
		if (this->head->pos == curr->next->pos) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}
