#pragma once
#include "Tree.h"

struct TreePair
{
	Tree* t1;
	Tree* t2;
	std::vector<std::pair<Tree*, Tree*>> mappings;
	TreePair(Tree* tree1, Tree* tree2, std::vector<std::pair<Tree*, Tree*>>& M) : t1(tree1), t2(tree2), mappings(M) {}

	static bool findPair(Tree* t1, Tree* t2, std::vector<std::pair<Tree*, Tree*>>& map);
	static bool isMatched(Tree* t, std::vector < std::pair<Tree*, Tree*> >& map);
	static bool hasMatchedChild(Tree* t, std::vector<std::pair<Tree*, Tree*>>& map);
};

struct dice_sort
{
	inline bool operator() (const TreePair& pair1, const TreePair& pair2)
	{
		return pair1.t1->dice(pair1.t1, pair1.t2, pair1.mappings) > pair2.t2->dice(pair2.t1, pair2.t2, pair2.mappings);
	}
};

