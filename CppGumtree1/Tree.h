#pragma once
#include <queue>
#include <deque>
#include <stack>
#include <iostream>
#include <string>

class Tree
{
public:
	Tree();
	Tree(std::string label, std::string val);
	~Tree();

	void updateValue(Tree* n, std::string v);
	void add(Tree* tp, Tree* t, int i, std::string l, std::string v);
	void deleteLeaf(Tree* t);
	void move(Tree* tp, Tree* t, int i);

	void addChildren(Tree* c);
	void printRoot();
	void print(Tree* t);
	bool hasChildrens();
	void removeFirstChildren();
	int nbChildrens();
	Tree* getParent();
	std::deque<Tree*> getChildrens();
	void pushFrontChildrens(Tree* tree);
	void popFrontChildrens();
	void setParent(Tree* parent);
	void setValue(std::string v);
	void setLabel(std::string l);
	std::string value();
	std::string label();
	bool isChild(Tree* Child);
	int height(Tree* node);

private:
	std::string m_value;
	std::string m_label;
	Tree* m_parent;
	std::deque<Tree*> m_childrens;
};

