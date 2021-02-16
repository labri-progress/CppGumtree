#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Tree.h"

class HIPList
{
public:
	HIPList();

	void push(int h, Tree* l);
	int peekMax();
	std::vector<Tree*> pop();
	void open(Tree* t);

	int size();
	void print();
	bool contains(Tree* node);
	
private:
	std::multimap<int, Tree*, std::greater<int>> m_nodes;
};

