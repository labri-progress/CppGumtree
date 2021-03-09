#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "Tree.h"
#include "HIPList.h"
#include "Algorithm1.h"
#include "TreePair.h"

int main(int argc, char* argv[])
{
// Test5 Height-indexed priority list
#if 0
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
#endif
	/*
	Tree* t11 = new Tree("CompilationUnit", "");
	Tree* t12 = new Tree("TypeDeclaration", "");
	Tree* t13 = new Tree("Modifier", "public");
	Tree* t14 = new Tree("SimpleName", "Test");
	Tree* t15 = new Tree("MethodDeclaration", "");
	Tree* t16 = new Tree("Modifier", "private");
	Tree* t17 = new Tree("SimpleType", "String");
	Tree* t18 = new Tree("SimpleName", "foo");
	Tree* t19 = new Tree("SimpleVariableDeclaration", "");
	Tree* t191 = new Tree("Block", "");
	Tree* t192 = new Tree("SimpleName", "String");
	Tree* t193 = new Tree("PrimitiveType", "int");
	Tree* t194 = new Tree("SimpleName", "i");
	Tree* t195 = new Tree("IfStatement", "");
	Tree* t196 = new Tree("InfixExpression", "==");
	Tree* t197 = new Tree("ReturnStatement", "");
	Tree* t198 = new Tree("IfStatement", "");
	Tree* t1981 = new Tree("SimpleName", "i");
	Tree* t1982 = new Tree("NumberLiteral", "0");
	Tree* t1983 = new Tree("StringLiteral", "Bar");
	Tree* t1984 = new Tree("InfixExpression", "==");
	Tree* t1985 = new Tree("ReturnStatement", "");
	Tree* t1986 = new Tree("SimpleName", "i");
	Tree* t1987 = new Tree("PrefixExpression", "-");
	Tree* t1988 = new Tree("StringLiteral", "Foo!");
	Tree* t1989 = new Tree("NumberLiteral", "1");
	t11->addChildren(t12);
	t12->addChildren(t13);
	t12->addChildren(t14);
	t12->addChildren(t15);
	t15->addChildren(t16);
	t15->addChildren(t17);
	t15->addChildren(t18);
	t15->addChildren(t19);
	t15->addChildren(t191);
	t17->addChildren(t192);
	t19->addChildren(t193);
	t19->addChildren(t194);
	t191->addChildren(t195);
	t195->addChildren(t196);
	t195->addChildren(t197);
	t195->addChildren(t198);
	t196->addChildren(t1981);
	t196->addChildren(t1982);
	t197->addChildren(t1983);
	t198->addChildren(t1984);
	t198->addChildren(t1985);
	t1984->addChildren(t1986);
	t1984->addChildren(t1987);
	t1985->addChildren(t1988);
	t1987->addChildren(t1989);

	Tree* t21 = new Tree("CompilationUnit", "");
	Tree* t22 = new Tree("TypeDeclaration", "");
	Tree* t23 = new Tree("Modifier", "public");
	Tree* t24 = new Tree("SimpleName", "Test");
	Tree* t25 = new Tree("MethodDeclaration", "");
	Tree* t26 = new Tree("Modifier", "public");
	Tree* t27 = new Tree("SimpleType", "String");
	Tree* t28 = new Tree("SimpleName", "foo");
	Tree* t29 = new Tree("SingleVariableDeclaration", "");
	Tree* t291 = new Tree("Block", "");
	Tree* t292 = new Tree("SimpleName", "String");
	Tree* t293 = new Tree("PrimitiveType", "int");
	Tree* t294 = new Tree("SimpleName", "i");
	Tree* t295 = new Tree("IfStatement", "");
	Tree* t296 = new Tree("InfixExpression", "==");
	Tree* t297 = new Tree("ReturnStatement", "");
	Tree* t298 = new Tree("SimpleName", "i");
	Tree* t299 = new Tree("NumberLiteral", "0");
	Tree* t2991 = new Tree("StringLiteral", "Foo!");
	t21->addChildren(t22);
	t22->addChildren(t23);
	t22->addChildren(t24);
	t22->addChildren(t25);
	t25->addChildren(t26);
	t25->addChildren(t27);
	t25->addChildren(t28);
	t25->addChildren(t29);
	t25->addChildren(t291);
	t27->addChildren(t292);
	t29->addChildren(t293);
	t29->addChildren(t294);
	t291->addChildren(t295);
	t295->addChildren(t296);
	t295->addChildren(t297);
	t296->addChildren(t298);
	t296->addChildren(t299);
	t297->addChildren(t2991);
		HIPList L1;
		HIPList L2;
		int minHeight =2;
		std::vector<std::pair<Tree*, Tree*>> candidateMappings;
		std::vector<std::pair<Tree*, Tree*>> resultMappings;
		Algorithm1 algo;
		algo.compute(t11, t21, minHeight, L1, L2, candidateMappings, resultMappings);

		std::vector<std::pair<Tree*, Tree*>>::iterator mapIt;
		for (mapIt = resultMappings.begin(); mapIt != resultMappings.end(); ++mapIt)
		{
			std::cout << "((" << (*mapIt).first->label() << ", " << (*mapIt).first->value() << ") (" << (*mapIt).second->label() << ", " << (*mapIt).second->value() << "))" << std::endl;
		}
		std::cout << "candidates: " << std::endl;
		for (mapIt = candidateMappings.begin(); mapIt != candidateMappings.end(); ++mapIt)
		{
			std::cout << "((" << (*mapIt).first->label() << ", " << (*mapIt).first->value() << ") (" << (*mapIt).second->label() << ", " << (*mapIt).second->value() << "))" << std::endl;
		}*/
		/*
//	t11	(A, A)						t21(F, F)
//		|								|		\
//	t12	(B, B)						t22	(G, G)	t23(A, A)
//		|		\						|			|
//	t13	(C, C)	t14(D, D)			t24(H, H)	t25(B, B)
//					|								|		\
//				t15(E, E)						t26(C, C)	t27(D, D)
//																|
//															t28(E, E)
	Tree* t11 = new Tree("A", "A");
	Tree* t12 = new Tree("B", "B");
	Tree* t13 = new Tree("C", "C");
	Tree* t14 = new Tree("D", "D");
	Tree* t15 = new Tree("E", "E");
	t11->addChildren(t12);
	t12->addChildren(t13);
	t12->addChildren(t14);
	t14->addChildren(t15);

	Tree* t21 = new Tree("F", "F");
	Tree* t22 = new Tree("G", "G");
	Tree* t23 = new Tree("A", "A");
	Tree* t24 = new Tree("H", "H");
	Tree* t25 = new Tree("B", "B");
	Tree* t26 = new Tree("C", "C");
	Tree* t27 = new Tree("D", "D");
	Tree* t28 = new Tree("E", "E");
	t21->addChildren(t22);
	t21->addChildren(t23);
	t22->addChildren(t24);
	t23->addChildren(t25);
	t25->addChildren(t26);
	t25->addChildren(t27);
	t27->addChildren(t28);

	HIPList L1;
	HIPList L2;
	int minHeight = 3;
	std::vector<std::pair<Tree*, Tree*>> candidateMappings;
	std::vector<std::pair<Tree*, Tree*>> resultMappings;
	Algorithm1 algo;
	algo.compute(t11, t23, minHeight, L1, L2, candidateMappings, resultMappings);
	std::vector<std::pair<Tree*, Tree*>>::iterator mapIt;
	for (mapIt = resultMappings.begin(); mapIt != resultMappings.end(); ++mapIt)
	{
		std::cout << "((" << (*mapIt).first->label() << ", " << (*mapIt).first->value() << ") (" << (*mapIt).second->label() << ", " << (*mapIt).second->value() << "))" << std::endl;
	}*/
/*
	Tree* t1 = new Tree ("CompilationUnit", "");
	Tree* t2 = new Tree("TypeDeclaration", "");
	t1->addChildren(t2);
	Tree* t3 = new Tree("Modifier", "public");
	Tree* t4 = new Tree("SimpleName", "Test");
	Tree* t5 = new Tree("MethodDeclaration", "");
	t2->addChildren(t3);
	t2->addChildren(t4);
	t2->addChildren(t5);
	Tree* t6 = new Tree("Modifier", "private");
	Tree* t7 = new Tree("SimpleType", "String");
	Tree* t8 = new Tree("SimpleName", "foo");
	Tree* t9 = new Tree("SingleVariableDeclaration", "");
	Tree* t10 = new Tree("Block", "");
	t5->addChildren(t6);
	t5->addChildren(t7);
	t5->addChildren(t8);
	t5->addChildren(t9);
	t5->addChildren(t10);
	Tree* t11 = new Tree("SimpleName", "String");
	t7->addChildren(t11);
	Tree* t12 = new Tree("PrimitiveType", "int");
	Tree* t13 = new Tree("SimpleName", "i");
	Tree* t14 = new Tree("IfStatement", "");
	t10->addChildren(t12);
	t10->addChildren(t13);
	t10->addChildren(t14);
	Tree* t15 = new Tree("InfixExpression", "==");
	Tree* t16 = new Tree("ReturnStatement", "");
	Tree* t17 = new Tree("IfStatement", "");
	t14->addChildren(t15);
	t14->addChildren(t16);
	t14->addChildren(t17);
	Tree* t18 = new Tree("SimpleName", "i");
	Tree* t19 = new Tree("NumberLiteral", "0");
	t15->addChildren(t18);
	t15->addChildren(t19);
	Tree* t20 = new Tree("StringLiteral", "Bar");
	t16->addChildren(t20);
	Tree* t21 = new Tree("InfixExpression", "==");
	Tree* t22 = new Tree("ReturnStatement", "");
	t17->addChildren(t21);
	t17->addChildren(t22);
	Tree* t23 = new Tree("SimpleName", "i");
	Tree* t24 = new Tree("PrefixExpression", "-");
	t21->addChildren(t23);
	t21->addChildren(t24);
	Tree* t25 = new Tree( "StringLiteral", "Foo!");
	t22->addChildren(t25);
	Tree* t26 = new Tree("NumberLiteral", "1");
	t24->addChildren(t26);

	Tree* tDst1 = new Tree("CompilationUnit", "");
	Tree* tDst2 = new Tree("TypeDeclaration", "");
	tDst1->addChildren(tDst2);
	Tree* tDst3 = new Tree("Modifier", "public");
	Tree* tDst4 = new Tree("SimpleName", "Test");
	Tree* tDst5 = new Tree("MethodDeclaration", "");
	tDst2->addChildren(tDst3);
	tDst2->addChildren(tDst4);
	tDst2->addChildren(tDst5);
	Tree* tDst6 = new Tree("Modifier", "public");
	Tree* tDst7 = new Tree("SimpleType", "String");
	Tree* tDst8 = new Tree("SimpleName", "foo");
	Tree* tDst9 = new Tree("SingleVariableDeclaration", "");
	Tree* tDst10 = new Tree("Block", "");
	tDst5->addChildren(tDst6);
	tDst5->addChildren(tDst7);
	tDst5->addChildren(tDst8);
	tDst5->addChildren(tDst9);
	tDst5->addChildren(tDst10);
	Tree* tDst11 = new Tree("SimpleName", "String");
	tDst7->addChildren(tDst11);
	Tree* tDst12 = new Tree("PrimitiveType", "int");
	Tree* tDst13 = new Tree("SimpleName", "i");
	tDst9->addChildren(tDst12);
	tDst9->addChildren(tDst13);
	Tree* tDst14 = new Tree("IfStatement", "");
	tDst10->addChildren(tDst14);
	Tree* tDst15 = new Tree("InfixExpression", "==");
	Tree* tDst16 = new Tree("ReturnStatement", "");
	tDst14->addChildren(tDst15);
	tDst14->addChildren(tDst16);
	Tree* tDst17 = new Tree("SimpleName", "i");
	Tree* tDst18 = new Tree("NumberLiteral", "0");
	tDst15->addChildren(tDst17);
	tDst15->addChildren(tDst18);
	Tree* tDst19 = new Tree("StringLiteral", "Foo!");
	tDst16->addChildren(tDst19);

	Algorithm1 algo;
	int minHeight = 2;
	HIPList L1;
	HIPList L2;
	std::vector < std::pair<Tree*, Tree*> > candidatesMappings;
	std::vector < std::pair<Tree*, Tree*> > resultMappings;
	std::vector < std::pair<Tree*, Tree*> >::iterator mapIt;
	algo.compute(t1, tDst1, minHeight, L1, L2, candidatesMappings, resultMappings);
	for (mapIt = resultMappings.begin(); mapIt != resultMappings.end(); ++mapIt)
	{
		std::cout << "((" << (*mapIt).first->label() << ", " << (*mapIt).first->value() << ") (" << (*mapIt).second->label() << ", " << (*mapIt).second->value() << "))" << std::endl;
	}*/

	//	t11	(A, A)						t21(F, F)
	//		|								|		\
	//	t12	(B, B)						t22	(G, G)	t23(A, A)
	//		|		\						|			|
	//	t13	(C, C)	t14(D, D)			t24(H, H)	t25(B, B)
	//					|								|		\
	//				t15(E, E)						t26(C, C)	t27(D, D)
	//																|
	//															t28(E, E)
	Tree* t11 = new Tree("A", "A");
	Tree* t12 = new Tree("B", "B");
	Tree* t13 = new Tree("C", "C");
	Tree* t14 = new Tree("D", "D");
	Tree* t15 = new Tree("E", "E");
	t11->addChildren(t12);
	t12->addChildren(t13);
	t12->addChildren(t14);
	t14->addChildren(t15);
	t12->setParent(t11);
	t13->setParent(t12);
	t14->setParent(t12);
	t15->setParent(t14);
	Tree* t21 = new Tree("F", "F");
	Tree* t22 = new Tree("G", "G");
	Tree* t23 = new Tree("A", "A");
	Tree* t24 = new Tree("H", "H");
	Tree* t25 = new Tree("B", "b");
	Tree* t26 = new Tree("C", "C");
	Tree* t27 = new Tree("D", "D");
	Tree* t28 = new Tree("E", "E");
	t21->addChildren(t22);
	t21->addChildren(t23);
	t22->addChildren(t24);
	t23->addChildren(t25);
	t25->addChildren(t26);
	t25->addChildren(t27);
	t27->addChildren(t28);
	t22->setParent(t21);
	t23->setParent(t21);
	t24->setParent(t22);
	t25->setParent(t23);
	t26->setParent(t25);
	t27->setParent(t25);
	t28->setParent(t27);
	std::vector <std::pair<Tree*, Tree*>> map;
	map.push_back(std::pair<Tree*, Tree*>(t11, t23));
	map.push_back(std::pair<Tree*, Tree*>(t12, t24));
	map.push_back(std::pair<Tree*, Tree*>(t13, t26));
	map.push_back(std::pair<Tree*, Tree*>(t14, t27));
	map.push_back(std::pair<Tree*, Tree*>(t15, t28));
	Tree* t1 = t12;
	Tree* t2 = t25;
	std::vector<Tree*> t2Candidates = t21->candidate(t1, map, 3);
	bool _isMatched = TreePair::isMatched(t2, map); //should be false
	bool _hasSomeMatchingDesc = t2->hasSomeMatchingDesc(t1, 3, map);
	std::cout << "isMatched " << _isMatched << std::endl;
	std::cout << "hasSomeMatchingDesc " << _hasSomeMatchingDesc << std::endl;
	return 0;
}