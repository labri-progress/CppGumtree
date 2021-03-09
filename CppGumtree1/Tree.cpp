#include "pch.h"
#include "Tree.h"
#include "TreePair.h"

Tree::Tree()
{
	m_parent = nullptr;
	setLabel("root");
	setValue("");
}

Tree::Tree(std::string label, std::string val)
{
	m_parent = nullptr;
	setLabel(label);
	setValue(val);
}


Tree::~Tree()
{
}

void Tree::setValue(std::string v)
{
	m_value = v;
}

void Tree::setLabel(std::string l)
{
	m_label = l;
}

std::string Tree::value()
{
	return m_value;
}

std::string Tree::label()
{
	return m_label;
}

bool Tree::isChild(Tree * Child)
{
	for (Tree* ch : m_childrens)
	{
		if (ch == Child)
			return true;
	}
	return false;
}

int Tree::height(Tree* node)
{
	if (node->getChildrens().empty())
	{
		return 1;
	}
	else
	{
		std::deque<Tree*> childrens;
		std::deque<int> heightDeque;
		if (!node->getChildrens().empty())
		{
			childrens = node->getChildrens();
		}
		while (!childrens.empty())
		{
			heightDeque.push_front(height(childrens.front()));
			childrens.pop_front();
		}
		int max = 0;
		for (int elem : heightDeque)
		{
			if (elem > max)
			{
				max = elem;
			}
		}
		return max + 1;
	}
}

bool Tree::isomorphic(Tree* t)
{
	if (label() != t->label() && value() != t->value())
	{
		return false;
	}

	if (getChildrens().size() != t->getChildrens().size())
	{
		return false;
	}

	for (int i = 0; i < getChildrens().size(); ++i)
	{
		bool childIsomorphic = getChild(i)->isomorphic(t->getChild(i));
		if (!childIsomorphic)
		{
			return false;
		}
	}

	return true;
}

std::vector<Tree*> Tree::preorder(Tree* t)
{
	std::vector<Tree*> nodes;
	preorder(t, nodes);
	return nodes;
}

void Tree::preorder(Tree* t, std::vector<Tree*>& nodes)
{
	nodes.push_back(t);

	if (t->hasChildrens())
	{
		for (Tree* element : t->getChildrens())
		{
			preorder(element, nodes);
		}
	}
}

std::vector<Tree*> Tree::postorder(Tree* t)
{
	std::vector<Tree*> nodes;
	postorder(t, nodes);
	return nodes;
}

void Tree::postorder(Tree* t, std::vector<Tree*>& nodes)
{
	if (t->hasChildrens())
	{
		for (Tree* element : t->getChildrens())
		{
			postorder(element, nodes);
		}
	}
	nodes.push_back(t);
}

std::vector<Tree*> Tree::getDescendants()
{
	std::vector<Tree*> descendants = this->preorder(this);
	std::vector<Tree*>::iterator it = descendants.begin();
	descendants.erase(it);
	return descendants;
}

float Tree::dice(Tree* t1, Tree* t2, std::vector<std::pair<Tree*, Tree*>> M)
{
	std::vector<std::pair<Tree*, Tree*>>::iterator MIt;
	for (MIt = M.begin(); MIt != M.end(); ++MIt)
	{
		if ((*MIt).first == t1 && (*MIt).second == t2)
		{
			std::vector<Tree*> t1Desc = t1->getDescendants();
			std::vector<Tree*> t2Desc = t2->getDescendants();
			return (2 * (t1Desc.size())) / (t1Desc.size() + t2Desc.size());
		}
	}
	return 0;
}

bool Tree::existsIsomorphic(Tree* t1, Tree* t2)
{
	std::vector<Tree*> T = postorder(this);
	for (Tree* element : T)
	{
		return (t1->isomorphic(element) && element != t2);
	}
	return false;
}

std::vector<Tree*> Tree::candidate(Tree* t1, std::vector<std::pair<Tree*, Tree*>>& map, int minDescMatch) // A tester
{
	std::vector<Tree*> result;
	std::vector<Tree*> t2Nodes = this->preorder(this);
	std::vector<std::pair<Tree*, Tree*>>::iterator mapIt;

	if (TreePair::isMatched(t1, map))
	{
		for (Tree* t2 : t2Nodes)
		{
			if (t1->label() == t2->label() && !TreePair::isMatched(t2, map) && t2->hasSomeMatchingDesc(t1, minDescMatch, map))
			{
				result.push_back(t2);
			}
		}
	}
	return result;
}

bool Tree::hasSomeMatchingDesc(Tree* t,int minMatchDesc, std::vector<std::pair<Tree*, Tree*>> map)
{
	std::vector<std::pair<Tree*, Tree*>>::iterator mapIt;
	std::vector<Tree*> t1Descs = t->getDescendants();
	std::vector<Tree*> t2Descs = this->getDescendants();
	int matchingDesc = 0;

	for (Tree* t1Desc : t1Descs)
	{
		for (Tree* t2Desc : t2Descs)
		{
			if (TreePair::findPair(t1Desc, t2Desc, map))
			{
				matchingDesc++;
				if (matchingDesc == minMatchDesc)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void Tree::updateValue(Tree * n, std::string v)
{
	n->setValue(v);
}

//			t0	(CompilationUnit)
//							|
//			t1	(TypeDeclaration)
//				/			|		\
//(Modifier:public)	t2(SimpleName:test) (MethodDeclaration)


// add(t0, t2, 1, SimpleName, test)
void Tree::add(Tree * tp, Tree * t, int i, std::string l, std::string v)
{
	if (tp != nullptr)
	{
		int cnt = -1;
		std::stack<Tree*> tmp_s;
		while (cnt != i)
		{
			++cnt;
			tmp_s.push(m_childrens.front());
			m_childrens.pop_front();
		}
		m_childrens.push_front(t);
		while (cnt != -1)
		{
			--cnt;
			m_childrens.push_front(tmp_s.top());
			tmp_s.pop();
		}
	}
}

void Tree::deleteLeaf(Tree * t)
{
	if (!t->hasChildrens())
	{
		delete t;
		t = nullptr;
	}
}

void Tree::move(Tree * tp, Tree * t, int i)
{
	if (tp != nullptr)
	{
		if (i <= tp->nbChildrens())
		{
			int cnt = 0;
			std::stack<Tree*> tmp_s;

			for (Tree* tree : t->getParent()->getChildrens())
			{
				if (tree == t)
				{
					t->getParent()->popFrontChildrens();
					break;
				}
				tmp_s.push(t->getParent()->getChildrens().front());
				t->getParent()->popFrontChildrens();
			}

			while (!tmp_s.empty())
			{
				Tree* currentTree = tmp_s.top();
				if (currentTree != t)
				{
					t->getParent()->pushFrontChildrens(currentTree);
				}
				tmp_s.pop();
			}

			t->setParent(tp);

			while (cnt != i)
			{
				++cnt;
				tmp_s.push(m_childrens.front());
				m_childrens.pop_front();
			}
			m_childrens.push_front(t);
			while (cnt != 0)
			{
				--cnt;
				m_childrens.push_front(tmp_s.top());
				tmp_s.pop();
			}
		}
	}
}

void Tree::addChildren(Tree * c)
{
	m_childrens.push_front(c);
	c->setParent(this);
}

void Tree::printRoot()
{
	std::cout << "Label: " << label() << std::endl << "Value: " << value() << std::endl;
}

void Tree::print(Tree* t)
{
	if (t != nullptr)
	{
		std::cout << "(" << t->label() << ", " << t->value() << ")" << std::endl;
		if (!t->m_childrens.empty())
		{
			std::stack<Tree*> tmp_s;
			while (!t->m_childrens.empty())
			{
				Tree* first_tree = t->m_childrens.back();
				tmp_s.push(first_tree);
				t->removeFirstChildren();

				print(first_tree);
			}

			while (!tmp_s.empty())
			{
				t->m_childrens.push_back(tmp_s.top());
				tmp_s.pop();
			}
		}
		std::cout << "/" << std::endl;
	}
}

bool Tree::hasChildrens()
{
	return !m_childrens.empty();
}

void Tree::removeFirstChildren()
{
	m_childrens.pop_back();
}

int Tree::nbChildrens()
{
	return m_childrens.max_size();
}

Tree * Tree::getParent()
{
	return m_parent;
}

Tree* Tree::getChild(int i)
{
	if (i < m_childrens.size())
	{
		return m_childrens.at(i);
	}
	return nullptr;
}

std::deque<Tree*> Tree::getChildrens()
{
	return m_childrens;
}

void Tree::pushFrontChildrens(Tree * tree)
{
	m_childrens.push_front(tree);
}

void Tree::popFrontChildrens()
{
	m_childrens.pop_front();
}


void Tree::setParent(Tree * parent)
{
	m_parent = parent;
}
