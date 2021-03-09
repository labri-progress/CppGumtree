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
	Tree* getChild(int i);
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
	bool isomorphic(Tree* t);
	std::vector<Tree*> preorder(Tree* t);
	void preorder(Tree* t, std::vector<Tree*>& nodes);
	std::vector<Tree*> postorder(Tree* t);
	void postorder(Tree* t, std::vector<Tree*>& nodes);
	std::vector<Tree*> getDescendants();
	float dice(Tree* t1, Tree* t2, std::vector<std::pair<Tree*, Tree*>> M);
	bool existsIsomorphic(Tree* t1, Tree* t2);
	std::vector<Tree*> candidate(Tree* t1, std::vector<std::pair<Tree*, Tree*>>& map, int minDescMatch);
	bool hasSomeMatchingDesc(Tree* t,int minMatchDesc, std::vector<std::pair<Tree*, Tree*>> map);

private:
	std::string m_value;
	std::string m_label;
	Tree* m_parent;
	std::deque<Tree*> m_childrens;
};

