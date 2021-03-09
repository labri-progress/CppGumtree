#include "TreePair.h"

bool TreePair::findPair(Tree* t1, Tree* t2, std::vector<std::pair<Tree*, Tree*>>& map)
{
	std::vector <std::pair<Tree*, Tree*>>::iterator mapIt;
	for (mapIt = map.begin(); mapIt != map.end(); ++mapIt)
	{
		if ((*mapIt).first->label() == t1->label() && (*mapIt).first->value() == t1->value() &&
			 (*mapIt).second->label() == t2->label() && (*mapIt).second->value() == t2->value())
		{
			return true;
		}
	}
	return false;
}

bool TreePair::isMatched(Tree* t, std::vector<std::pair<Tree*, Tree*>>& map)
{
	std::vector <std::pair<Tree*, Tree*>>::iterator mapIt;
	for (mapIt = map.begin(); mapIt != map.end(); ++mapIt)
	{
		if (((*mapIt).first->label() == t->label() && (*mapIt).first->value() == t->value()) ||
			(*mapIt).second->label() == t->label() && (*mapIt).second->value() == t->value())
		{
			return true;
		}
	}
	return false;
}

bool TreePair::hasMatchedChild(Tree* t, std::vector<std::pair<Tree*, Tree*>>& map)
{
	std::deque<Tree*> childs = t->getChildrens();
	for (Tree* child : childs)
	{
		bool result = TreePair::isMatched(child, map);
		if (result)
		{
			return true;
		}
	}
	return false;
}
