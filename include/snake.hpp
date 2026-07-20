#ifndef SNAKE_HPP
#define SNAKE_HPP
// I figured that the snake is actually a linked list.
// Well, I could definitely use std::deque for this but
// I'm bored, and severely autistic
#include <raylib.h>
#include <stdlib.h>

class SnakeSegment {
	public:
	Vector2 pos;
	SnakeSegment *next;
	SnakeSegment(Vector2 pos) {
		this->pos = pos;
	}
	SnakeSegment();
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

	~Snake();
	void update();
	void append();
	void change_dir();
	void move();
	void draw(Vector2 center);
	bool food_collision_check(Rectangle *food);
	bool snake_bounds_check();
	bool snake_self_collision();
};
#endif
