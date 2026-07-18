#include <iostream>
#include <linked_list.hpp>

int main() {
	LinkedList *linked_list = new LinkedList;
	linked_list->append(new SnakeSegment({2, 2, 2, 2}));
	linked_list->append(new SnakeSegment({3, 3, 3, 3}));
	linked_list->append(new SnakeSegment({4, 4, 4, 4}));
	linked_list->append(new SnakeSegment({5, 5, 5, 5}));
	linked_list->append(new SnakeSegment({6, 6, 6, 6}));
	linked_list->append(new SnakeSegment({7, 7, 7, 7}));
	linked_list->append(new SnakeSegment({8, 8, 8, 8}));
	delete linked_list;
	return 0;
}
