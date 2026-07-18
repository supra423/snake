#include "linked_list.hpp"

int main() {
	Snake *linked_list = new Snake;
	linked_list->append({2, 2, 2, 2});
	linked_list->append({3, 3, 3, 3});
	linked_list->append({4, 4, 4, 4});
	linked_list->append({5, 5, 5, 5});
	linked_list->append({6, 6, 6, 6});
	linked_list->append({7, 7, 7, 7});
	linked_list->append({8, 8, 8, 8});
	delete linked_list;
	return 0;
}
