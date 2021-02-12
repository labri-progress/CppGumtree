#pragma once
#include <map>
#include "Tree.h"

class HIPList
{
public:
	HIPList();

	void push(Tree* l, int h);
private:
	std::map<int, Tree*> m_nodes;
};

