#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
// I figured that the snake is actually a linked list.
// Well, I could definitely use std::deque for this but
// I'm bored, and severely autistic
#include <stdlib.h>
#include <raylib.h>
#include <stdint.h>

class SnakeSegment {
	public:
	SnakeSegment *next;
	Rectangle rect;
	SnakeSegment(Rectangle rect) {
		this->rect = rect;
	}
};

class Snake {
	public:
	SnakeSegment *head;
	SnakeSegment *tail;
	size_t size = 0;

	~Snake() {
		SnakeSegment *curr = this->head;
		SnakeSegment *old_curr;
		for (size_t i = 0; i < this->size; i++) {
			old_curr = curr;
			curr = curr->next;
			delete old_curr;
		}
	}

	void append(Rectangle rect) {
		SnakeSegment *new_node = new SnakeSegment(rect);
		if (this->size == 0) {
			this->head = new_node;
			this->tail = new_node;
			this->size++;
			return;
		}
		SnakeSegment *old_tail = this->tail;
		this->tail = new_node;
		old_tail->next = new_node;
		this->size++;
	}
};
#endif
