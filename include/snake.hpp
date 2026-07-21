#ifndef SNAKE_HPP
#define SNAKE_HPP
#include "linked_list.hpp"
#include <raylib.h>
#include <stdlib.h>

class SnakeSegment {
	public:
	Vector2 pos;
	SnakeSegment(Vector2 pos) {
		this->pos = pos;
	}
	SnakeSegment();
};

class Snake { // my problem with this implementation, is that it merges to concept of linkedlist and the snake
			  // I want to make it so that it is separate, so that it makes it more scalable.
			  // I want to use the linked list for other things, like for example, multiple food spawns
			  // I don't want to use the snake for the "food group"
	public:
	LinkedList *snake_body;
	Vector2 dir = {0, 0};
	Vector2 next_dir = {0, 0};
	double last_update_time = 0.0;
	float move_timer = 0.0f;

	Snake();
	~Snake();
	void update();
	void append_snake();
	void change_dir();
	void move();
	void draw(Vector2 center);
	bool food_collision_check(Rectangle *food);
	bool snake_bounds_check();
	bool snake_self_collision();
};
#endif
