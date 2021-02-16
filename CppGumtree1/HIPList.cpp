#include "HIPList.h"

HIPList::HIPList()
{
}

void HIPList::push(int h, Tree* l)
{
	m_nodes.insert(std::pair<int, Tree*>(h, l));
}

int HIPList::peekMax()
{
	if (!m_nodes.empty())
	{
		std::multimap<int, Tree*>::iterator it = m_nodes.begin();
		return (*it).first;
	}
	return 0;
}

std::vector<Tree*> HIPList::pop()
{
	std::vector<Tree*> _nodes;
	if (!m_nodes.empty())
	{
		typedef std::multimap <int, Tree*>::iterator MMAPIterator;
		std::pair<MMAPIterator, MMAPIterator> result = m_nodes.equal_range(peekMax());

		for (MMAPIterator it = result.first; it != result.second; ++it)
		{
			_nodes.push_back((*it).second);
		}

		int _peekMax = peekMax();
		for (MMAPIterator it = m_nodes.begin(); it != m_nodes.end();)
		{
			if ((*it).first == _peekMax)
			{
				std::cout << "debugg: " << (*it).first << std::endl;
				it = m_nodes.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	return _nodes;
}

void HIPList::open(Tree* t)
{
	if (t != nullptr)
	{
		if (t->hasChildrens())
		{
			std::deque<Tree*> childs = t->getChildrens();
			for (Tree* node : childs)
			{
				m_nodes.insert(std::pair<int, Tree*>(node->height(node), node));
			}
		}
	}
}

void HIPList::print()
{
	std::multimap<int, Tree*>::iterator it;
	for (it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		std::cout << "(" << (*it).first << ", " << (*it).second->label() << ", " << (*it).second->value() << ")" << std::endl;
	}
}
