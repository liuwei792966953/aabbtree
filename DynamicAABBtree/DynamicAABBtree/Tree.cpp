#include "Tree.h"

int node_count = 0;

Node::Node() :id(node_count++) {

}
int Tree::compute_cost(sf::FloatRect mask) {
	int best = root, best_cost = -1;

	std::map<int, Node*>::iterator iter;
	for (iter = nodes.begin(); iter != nodes.end(); ++iter) {
		if (iter->second->child1 == LEAF_NODE && iter->second->parent != NULL_NODE) {
			int b_cost = 0;
			int a_cost = 0;

			for (int j = iter->first; j != NULL_NODE; j = nodes[j]->parent) {
				b_cost += area(nodes[j]->mask);
			}
			for (int j = iter->first; j != NULL_NODE; j = nodes[j]->parent) {
				a_cost += area(merge(nodes[j]->mask, mask, MERGE_SIZE));
			}
			if (best_cost > a_cost - b_cost || best_cost == -1) {
				best_cost = a_cost - b_cost;
				best = iter->first;
			}
		}
	}
	return best;
}

void Tree::insert_node(int index) {
	if (nodes.size() == 1) {
		root = index;
		return;
	}

	Node* child = new Node();

	int best = compute_cost(nodes[index]->mask);

	child->child1 = nodes[best]->child1;
	child->child2 = nodes[best]->child2;
	child->mask = nodes[best]->mask;
	child->parent = best;
	objects[child->child2]->node = child->id;
	nodes[index]->parent = best;

	nodes[best]->child1 = index;
	nodes[best]->child2 = child->id;

	nodes[child->id] = child;

	for (int i = index; i != NULL_NODE; i = nodes[i]->parent) {
		if (nodes[i]->child1 != LEAF_NODE) {
			nodes[i]->need_update = true;
		}
	}
}
void Tree::remove_node(int index) {
	if (nodes[index]->parent == root) {
		root = sibling(index);
		nodes[root]->parent = NULL_NODE;
	}
	else {
		if (nodes[nodes[nodes[index]->parent]->parent]->child1 == nodes[index]->parent)
			nodes[nodes[nodes[index]->parent]->parent]->child1 = sibling(index);
		else
			nodes[nodes[nodes[index]->parent]->parent]->child2 = sibling(index);
	}
	nodes[sibling(index)]->parent = nodes[nodes[index]->parent]->parent;
	if (nodes[index]->parent != NULL_NODE)
		nodes.erase(nodes[index]->parent);
	nodes.erase(index);
}

Object* Tree::insert_object(float x, float y) {
	Object* o = new Object(x, y);
	Node* n = new Node();

	o->node = n->id;
	n->child1 = LEAF_NODE;
	n->child2 = o->id;
	n->mask = o->mask;

	objects[o->id] = o;
	nodes[n->id] = n;

	insert_node(o->node);

	return o;
}
void Tree::remove_object(int index) {
	objects.erase(index);
	remove_node(objects[index]->node);
}
void Tree::update_object(int index) {
	nodes[objects[index]->node]->mask = objects[index]->mask;

	if (objects[index]->node != root && !contains(objects[index]->mask, nodes[nodes[objects[index]->node]->parent]->mask)) {
		remove_node(objects[index]->node);

		Node* n = new Node();
		objects[index]->node = n->id;
		n->child1 = LEAF_NODE;
		n->child2 = objects[index]->id;
		n->mask = objects[index]->mask;
		nodes[n->id] = n;

		insert_node(objects[index]->node);
	}
}

void Tree::update() {
	std::vector<int> stack;
	std::map<int, Node*>::iterator iter;

	for (iter = nodes.begin();iter != nodes.end();++iter) {
		if (iter->second->need_update) {
			stack.push_back(iter->first);
		}
	}

	for (; stack.size();) {
		int index = stack.back();
		stack.pop_back();
		nodes[index]->need_update = false;
		nodes[index]->mask = merge(nodes[nodes[index]->child1]->mask, nodes[nodes[index]->child2]->mask, MERGE_SIZE);
	}
}

void Tree::rotate(int index) {
	int change = sibling(nodes[index]->parent);

	//nodes[nodes[nodes[index]->parent]->parent]->child1 == nodes[index]->parent ?
	//	nodes[nodes[nodes[index]->parent]->parent]->child2 :
	//	nodes[nodes[nodes[index]->parent]->parent]->child1;

	int temp = nodes[index]->parent;
	nodes[index]->parent = nodes[change]->parent;
	nodes[change]->parent = temp;
}

int& Tree::sibling(int index) {
	return nodes[nodes[index]->parent]->child1 == index ?
		nodes[nodes[index]->parent]->child2 :
		nodes[nodes[index]->parent]->child1;
}

Object* Tree::query(sf::FloatRect mask, int index) {
	std::vector<int> stack;
	stack.push_back(root);

	for (; stack.size();) {
		int node = stack.back();
		stack.pop_back();

		std::set<int>::iterator iter;
		iter = nodes[node]->userdata.find(index);

		if (overlap(nodes[node]->mask, mask)){// && iter != nodes[node]->userdata.end()) {
			if (nodes[node]->child1 == LEAF_NODE) {
				return objects[nodes[node]->child2];
			}
			else {
				stack.push_back(nodes[node]->child1);
				stack.push_back(nodes[node]->child2);
			}
		}
	}
	return NULL;
}
int Tree::raycast(sf::Vector2f position, float direction) {
	return 0;
}
