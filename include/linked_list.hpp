#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
// I figured that the snake is actually a linked list.
// Well, I could definitely use std::deque for this but
// I'm bored, and severely autistic
#include <stdlib.h>

class Node {
	public:
	Node *next;
	// void pointer ( ˶°ㅁ°) !! This makes it a generic linked list
	// I could've used a safer alternative with templates
	// but I'm a C programmer by heart <3.
	void *data;
};

class LinkedList {
	public:
	Node *head;	
	Node *tail;	
	size_t size = 0;
	LinkedList();
	void append(void *data);
	void delete_node(Node *node);
};
#endif
