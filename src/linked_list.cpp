#include "linked_list.hpp"
#include <cstring>

LinkedList::LinkedList() {
	this->head = nullptr;
	this->tail = nullptr;
}

void LinkedList::append(void *data) {
	Node *new_node = new Node;
	new_node->data = data;
	new_node->next = nullptr;
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

LinkedList::~LinkedList() {}
