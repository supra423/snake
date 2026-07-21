#include "snake.hpp"
#include "linked_list.hpp"
#include "constants.hpp"
#include <raylib.h>
#include <raymath.h>

SnakeSegment::SnakeSegment() {}

Snake::Snake() {
	this->snake_body = new LinkedList;
}

Snake::~Snake() {
	Node *curr = this->snake_body->head;
	Node *old_curr;
	while (curr != nullptr) {
		old_curr = curr;
		curr = curr->next;
		delete (SnakeSegment *)old_curr->data;
		delete old_curr;
	}
	delete this->snake_body;
}

void Snake::update() {
	float dt = GetFrameTime();
	move_timer += dt;

	if (move_timer >= MOVE_INTERNAL) {
		move_timer -= MOVE_INTERNAL;
		this->move();
	}
}

void Snake::append_snake() {
	SnakeSegment *new_segment = new SnakeSegment;
	if (this->snake_body->size == 0) {
		new_segment->pos = SNAKE_STARTING_POSITION;
		this->snake_body->append(new_segment);
		return;
	}
	Node *tail = (Node *)this->snake_body->tail;
	SnakeSegment *snake_tail = (SnakeSegment *)tail->data;
	new_segment->pos = snake_tail->pos;
	this->snake_body->append(new_segment);
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
	Node *curr = this->snake_body->head;
	SnakeSegment *curr_snake_segment = (SnakeSegment *)curr->data;
	Vector2 old_curr_pos = curr_snake_segment->pos;
	Vector2 old_next_pos;
	this->dir = this->next_dir;
	curr_snake_segment->pos.x += this->dir.x * MAP_CELL_SIZE;
	curr_snake_segment->pos.y += this->dir.y * MAP_CELL_SIZE;
	SnakeSegment *curr_snake_segment_next;

	while (curr != nullptr) {
		if (curr->next == nullptr) {
			return;
		}
		curr_snake_segment_next = (SnakeSegment *)curr->next->data;
		old_next_pos = curr_snake_segment_next->pos;
		curr_snake_segment_next->pos = old_curr_pos;
		curr = curr->next;
		old_curr_pos = old_next_pos;
	}
}

void Snake::draw(Vector2 center) {
	if (this->snake_bounds_check()) { // prevents drawing after snake hits bounds
		return;
	}
	Node *curr = this->snake_body->head;
	SnakeSegment *curr_snake_segment = (SnakeSegment *)curr->data;
	SnakeSegment *curr_snake_segment_next;
	Vector2 segment_pos = Vector2Add(DYNAMIC_OFFSET(center), Vector2Subtract(curr_snake_segment->pos, BORDER_POS));
	Vector2 rectangle_pos = Vector2Add(Vector2Add(segment_pos, BORDER_POS), {BORDER_OFFSET, BORDER_OFFSET});
	DrawRectangleV(rectangle_pos, {SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE}, GREEN);
	while (curr != nullptr) {
		if (curr->next == nullptr) {
			return;
		}
		curr_snake_segment_next = (SnakeSegment *)curr->next->data;
		curr_snake_segment = curr_snake_segment_next;
		segment_pos = Vector2Add(DYNAMIC_OFFSET(center), Vector2Subtract(curr_snake_segment->pos, BORDER_POS));
		rectangle_pos = Vector2Add(Vector2Add(segment_pos, BORDER_POS), {BORDER_OFFSET, BORDER_OFFSET});
		DrawRectangleV(rectangle_pos, {SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE}, DARKGREEN);

		curr = curr->next;
	}
}

bool Snake::food_collision_check(Rectangle *food) {
	Node *head = this->snake_body->head;
	SnakeSegment *snake_head = (SnakeSegment *)head->data;
	if (snake_head->pos.x == food->x && snake_head->pos.y == food->y) {
		return true;
	}
	return false;
}

bool Snake::snake_bounds_check() {
	Node *head = this->snake_body->head;
	SnakeSegment *snake_head = (SnakeSegment *)head->data;
	if (snake_head->pos.x < BORDER_POS.x ||
			snake_head->pos.x >= BORDER_POS.x + BORDER_WIDTH ||
			snake_head->pos.y < BORDER_POS.y ||
			snake_head->pos.y >= BORDER_POS.y + BORDER_HEIGHT) {
		return true;
	}
	return false;
}

bool Snake::snake_self_collision() {
	if (this->snake_body->size <= 2) {
		return false;
	}
	Node *curr = this->snake_body->head;
	SnakeSegment *curr_snake_segment = (SnakeSegment *)curr->data;
	SnakeSegment *curr_snake_segment_next;
	while (curr != nullptr) {
		if (curr->next == nullptr) return false;
		curr_snake_segment_next = (SnakeSegment *)curr->next->data;
		if (curr_snake_segment->pos == curr_snake_segment_next->pos) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}
