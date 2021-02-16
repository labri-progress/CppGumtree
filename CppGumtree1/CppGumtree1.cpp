#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "Tree.h"
#include "HIPList.h"

int main(int argc, char* argv[])
{
// Test5 Height-indexed priority list

	HIPList hipList;
	Tree* t0 = new Tree("CompilationUnit", "");
	Tree* t1 = new Tree("TypeDeclaration", "");
	Tree* t2 = new Tree("Modifier", "public");
	Tree* t3 = new Tree("SimpleName", "test");
	Tree* t4 = new Tree("MethodDeclaration", "");
	Tree* t5 = new Tree("Modifier", "private");
	Tree* t6 = new Tree("SimpleType", "string");
	Tree* t7 = new Tree("SimpleName", "foo");
	Tree* t8 = new Tree("Block", "");
	Tree* t9 = new Tree("Test", "");
	t0->addChildren(t1);
	t1->addChildren(t2);
	t1->addChildren(t3);
	t1->addChildren(t4);
	t1->setParent(t0);
	t3->addChildren(t5);
	t3->addChildren(t6);
	t3->addChildren(t7);
	t3->addChildren(t8);
	t8->addChildren(t9);
	t2->setParent(t1);
	t3->setParent(t1);
	t4->setParent(t1);
	t5->setParent(t3);
	t6->setParent(t3);
	t7->setParent(t3);
	t8->setParent(t3);
	t9->setParent(t8);
	hipList.push(t0->height(t0), t0);
	hipList.push(t1->height(t1), t1);
	hipList.push(t2->height(t2), t2);
	hipList.push(t3->height(t3), t3);
	hipList.push(t4->height(t4), t4);
	hipList.push(t5->height(t5), t5);
	hipList.push(t6->height(t6), t6);
	hipList.push(t7->height(t7), t7);
	hipList.push(t8->height(t8), t8);
	hipList.push(t9->height(t9), t9);
	hipList.print();

	//Test peekMax()
	std::cout << "PeekMax: " << hipList.peekMax() << std::endl;

	//Test pop()
#if 0
	std::multimap<int, Tree*> testMM;
	std::multimap<int, Tree*>::iterator it;
	testMM.insert(std::pair<int, Tree*>(t0->height(t0), t0));
	testMM.insert(std::pair<int, Tree*>(t1->height(t1), t1));
	testMM.insert(std::pair<int, Tree*>(t2->height(t2), t2));
	testMM.insert(std::pair<int, Tree*>(t7->height(t7), t7));
	testMM.insert(std::pair<int, Tree*>(t8->height(t8), t8));
	testMM.insert(std::pair<int, Tree*>(t9->height(t9), t9));
	for (it = testMM.begin(); it != testMM.end(); ++it)
	{
		std::cout << "(" << (*it).first << ", " << (*it).second->label() << ", " << (*it).second->value() << ")" << std::endl;	
	}

	for (it = testMM.begin(); it != testMM.end();)
	{
		if ((*it).first == 1)
		{
			it = testMM.erase(it);
		}
		else
		{
			++it;
		}
	}
	std::cout << "*****" << std::endl;
	for (it = testMM.begin(); it != testMM.end(); it++)
	{
		std::cout << "(" << (*it).first << ", " << (*it).second->label() << ", " << (*it).second->value() << ")" << std::endl;
	}
#endif 

	std::vector<Tree*> vec = hipList.pop();
	std::vector<Tree*>::iterator vecIt;
	for (vecIt = vec.begin(); vecIt != vec.end(); ++vecIt)
	{
		std::cout << "(" << (*vecIt)->label() << ", " << (*vecIt)->value() << ")" << std::endl;
	}
	hipList.print();

	//open(Tree* t)
	std::cout << "***********" << std::endl;
	Tree* t10 = new Tree("A", "B");
	Tree* t11 = new Tree("B", "C");
	Tree* t12 = new Tree("C", "D");
	t10->addChildren(t11);
	t10->addChildren(t12);
	t11->setParent(t10);
	t12->setParent(t10);
	hipList.open(t10);
	hipList.print();

	return 0;
}