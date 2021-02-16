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

	void print();
	
private:
	std::multimap<int, Tree*, std::greater<int>> m_nodes;
};

