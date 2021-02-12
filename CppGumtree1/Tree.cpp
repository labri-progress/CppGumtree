#include "pch.h"
#include "Tree.h"

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
