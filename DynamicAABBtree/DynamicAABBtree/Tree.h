#pragma once
#include<vector>
#include<set>
#include<map>
#include"Object.h"
#include"Collision.h"

constexpr int NULL_NODE = -1;
constexpr int LEAF_NODE = -2;
constexpr float MERGE_SIZE = 10.f;

extern int node_count;

class Node {
public:
	bool need_update=false;
	int id;
	int parent= NULL_NODE, child1 = NULL_NODE, child2 = NULL_NODE;
	std::set<int> userdata;
	sf::FloatRect mask;

	Node();
};

class Tree{
public:
	int root;
	bool update_alltime = false;
	std::map<int,Node*> nodes;
	std::map<int,Object*> objects;

	int compute_cost(sf::FloatRect mask);

	void insert_node(int index);
	void remove_node(int index);

	Object *insert_object(float x, float y);
	void remove_object(int index);
	void update_object(int index);

	void update();

	void rotate(int index);
	int &sibling(int index);

	Object *query(sf::FloatRect mask, int index = 0);
	int raycast(sf::Vector2f position,float direction);
};
