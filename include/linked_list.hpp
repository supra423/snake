#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
// I figured that the snake is actually a linked list.
// Well, I could definitely use std::deque for this but
// I'm bored, and severely autistic
#include <cstdlib>
#include <raylib.h>
#include <stdint.h>

class SnakeSegment {
	public:
	Rectangle rect;
	SnakeSegment(Rectangle rect) {
		this->rect = rect;
	}
};

class Node {
	public:
	Node *next;
	SnakeSegment *snake_segment;
};

class LinkedList {
	public:
	Node *head;
	Node *tail;
	size_t size = 0;

	~LinkedList() {
		Node *curr = this->head;
		Node *old_curr = curr;
		for (size_t i = 0; i < this->size; i++) {
			old_curr = curr;
			delete curr->snake_segment;
			curr = curr->next;
			delete old_curr;
		}
	}

	void append(SnakeSegment *snake_segment) {
		Node *new_node = new Node();
		new_node->snake_segment = snake_segment;
		if (this->size == 0) {
			this->head = new_node;
			this->tail = new_node;
			this->size++;
			return;
		}
		Node *old_tail = this->tail;
		this->tail = new_node;
		old_tail->next = new_node;
		this->size++;
	}
};
#endif
