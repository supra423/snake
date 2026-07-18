#include "snake.hpp"

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

	if (move_timer >= move_interval) {
		move_timer -= move_interval;
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
	Vector2 pos_in_grid;
	SnakeSegment *curr = this->head;

	while (curr != nullptr) {
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

bool Snake::is_food_eaten(Rectangle *food) {
	if (this->head->pos.x + 5 == food->x && this->head->pos.y + 5 == food->y) {
		return true;
	}
	return false;
}

bool Snake::snake_bounds_check() {
	if (this->head->pos.x + 5 <= BORDER_POS.x ||
			this->head->pos.x >= BORDER_POS.x + BORDER_WIDTH ||
			this->head->pos.y + 5 <= BORDER_POS.y ||
			this->head->pos.y >= BORDER_HEIGHT + MAP_CELL_SIZE) {
		return true;
	}
	return false;
}
