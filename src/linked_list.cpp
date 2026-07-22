#include "linked_list.hpp"

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

void LinkedList::delete_node(Node *node) {
	if (this->size == 0 || node == nullptr) return;
	Node *node_to_be_deleted;
	if (node == this->head) {
		node_to_be_deleted = this->head;
		if (this->size == 1) {
			this->tail = nullptr;
			this->head = nullptr;
			delete node_to_be_deleted;
			this->size--;
			return;
		}
		this->head = this->head->next;
		delete node_to_be_deleted;
		this->size--;
		return;
	}
	Node *curr = this->head;

	while (curr != nullptr) {
		if (curr->next == nullptr) return;
		if (curr->next == node && node == this->tail) {
			node_to_be_deleted = curr->next;
			this->tail = curr;
			delete node_to_be_deleted;
			curr->next = nullptr;
			this->size--;
			return;
		}
		if (curr->next == node) {
			node_to_be_deleted = curr->next;
			curr->next = curr->next->next;
			delete node_to_be_deleted;
			this->size--;
			return;
		}
		curr = curr->next;
	}
}
