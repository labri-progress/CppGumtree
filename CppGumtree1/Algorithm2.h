#pragma once
#include "Tree.h"

namespace Util
{
	static int max(int A, int B);
}

class Algorithm2
{
public:
	void compute(Tree* T1, Tree* T2, std::vector<std::pair<Tree*, Tree*>>& resultMapping, float minDice, int maxSize);
};

int Util::max(int A, int B)
{
	if (A > B)
		return A;
	else
		return B;
}

