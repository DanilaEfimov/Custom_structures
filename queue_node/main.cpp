#include"queue_node.h"
#include<iostream>

int main() {
	queue_node<int> Q;
	for(size_t i = 0; i < 10; i++) {
		Q.add(i, parent);
		Q.add(i * 8 % 5, right);
		if (i % 2) {
			Q.add(i * 5 % 8, left);
		}
	}

	Q.terminate();

	for (size_t i = 0; i < 10; i++) {
		Q.add(i, parent);
		Q.add(i * 8 % 5, right);
		if (i % 2) {
			Q.add(i * 5 % 8, left);
		}
	}

	for (size_t i = 0; i < 3; i++) {
		Q.push();
	}

	std::cout << std::endl;
	Q.terminate();

	// queue-tree:
	queue_node<queue_node<int>> queue_tree;

	return 0;
}