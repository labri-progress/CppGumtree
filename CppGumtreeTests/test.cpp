#include "pch.h"
#include "Tree.h"
#include "HIPList.h"
#include "Algorithm1.h"
#include "TreePair.h"

#include <algorithm>
TEST(TestTree, TestAdd1) 
{

	//Test 1
//		t0	(CompilationUnit)
//							|
//			t1	(TypeDeclaration)
//				/			:		\
//			   /			:		 \
//t2(Modifier:public)	t3(SimpleName:test) t4(MethodDeclaration)


// add(t1, t3, 1, SimpleName, test)

	Tree* t0 = new Tree("CompilationUnit", "");
	Tree* t1 = new Tree("TypeDeclaration", "");
	Tree* t2 = new Tree("Modifier", "public");
	Tree* t3 = new Tree("SimpleName", "test");
	Tree* t4 = new Tree("MethodDeclaration", "");

	t1->addChildren(t2);
	t1->addChildren(t4);
	t0->addChildren(t1);
	t0->print(t0);

	t1->add(t1, t3, 1, "SimpleName", "test");
	t0->print(t0);

	EXPECT_TRUE(t1->isChild(t3));
}

TEST(TestTree, TestAdd2)
{
	//Test 2
//					t0	(CompilationUnit)
//							|
//					t1	(TypeDeclaration)
//				/			   :	       \
//			   /			   :		    \
//t2(Modifier:public)	t3(SimpleName:test)	  t4(MethodDeclaration)
//					   /	|	   |	   \
//					  /		|	   |		\
//t5(Modifier:private) t6(SimpleType:string) t7(SimpleName:foo) t8(Block)


// add(t3, t7, 2, SimpleType, String)
	Tree* t0 = new Tree("CompilationUnit", "");
	Tree* t1 = new Tree("TypeDeclaration", "");
	Tree* t2 = new Tree("Modifier", "public");
	Tree* t3 = new Tree("SimpleName", "test");
	Tree* t4 = new Tree("MethodDeclaration", "");
	Tree* t5 = new Tree("Modifier", "private");
	Tree* t6 = new Tree("SimpleType", "string");
	Tree* t7 = new Tree("SimpleName", "foo");
	Tree* t8 = new Tree("Block", "");

	t0->addChildren(t1);
	t1->addChildren(t2);
	t1->addChildren(t3);
	t1->addChildren(t4);
	t3->addChildren(t5);
	t3->addChildren(t6);
	t3->addChildren(t8);
	t0->print(t0);
	t3->add(t3, t7, 2, "SimpleType", "String");
	t0->print(t0);

	EXPECT_TRUE(t3->isChild(t7));
}

TEST(TestTree, TestMove1)
{
	//Test 3
//					t0	(CompilationUnit)
//							|
//					t1	(TypeDeclaration)
//				/			   :	       \
//			   /			   :		    \
//t2(Modifier:public)	t3(SimpleName:test)	  t4(MethodDeclaration)
//					   /	|	   |	   \
//					  /		|	   |		\
//t5(Modifier:private) t6(SimpleType:string) t7(SimpleName:foo) t8(Block)


// move(t0, t7, 1)

	Tree* t0 = new Tree("CompilationUnit", "");
	Tree* t1 = new Tree("TypeDeclaration", "");
	Tree* t2 = new Tree("Modifier", "public");
	Tree* t3 = new Tree("SimpleName", "test");
	Tree* t4 = new Tree("MethodDeclaration", "");
	Tree* t5 = new Tree("Modifier", "private");
	Tree* t6 = new Tree("SimpleType", "string");
	Tree* t7 = new Tree("SimpleName", "foo");
	Tree* t8 = new Tree("Block", "");

	t0->addChildren(t1);
	t1->addChildren(t2);
	t1->addChildren(t3);
	t1->addChildren(t4);
	t1->setParent(t0);
	t3->addChildren(t5);
	t3->addChildren(t6);
	t3->addChildren(t7);
	t3->addChildren(t8);
	t2->setParent(t1);
	t3->setParent(t1);
	t4->setParent(t1);
	t5->setParent(t3);
	t6->setParent(t3);
	t7->setParent(t3);
	t8->setParent(t3);
	t0->print(t0);
	EXPECT_TRUE(t3->isChild(t7));
	t0->move(t0, t7, 1);
	t0->print(t0);
	EXPECT_TRUE(t0->isChild(t7));
	EXPECT_FALSE(t3->isChild(t7));
}

TEST(TestTree, TestHeight)
{
	//Test 4
//					t0	(CompilationUnit)
//							|
//					t1	(TypeDeclaration)
//				/			   :	       \
//			   /			   :		    \
//t2(Modifier:public)	t3(SimpleName:test)	  t4(MethodDeclaration)
//					   /	|	   |	   \
//					  /		|	   |		\
//t5(Modifier:private) t6(SimpleType:string) t7(SimpleName:foo) t8(Block)
//																	|
//																	|
//																t9(Test)

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
	t0->print(t0);
	EXPECT_EQ(t0->height(t0), 5);
}

TEST(TestTree, TestIsomorphic1)
{
//	t11	(A, A)						t21(F, F)
//		|								|		\
//	t12	(B, B)						t22	(G, G)	t23(A, A)
//		|		\						|			|
//	t13	(C, C)	t14(D, D)			t24(H, H)	t25(B, B)
//					|								|		\
//				t15(E, E)						t26(C, C)	t27(D, D)
//																|
//															t28(E, E)
// t11.isomorphic(t21) -> false
// t11.isomorphic(t23) -> true
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
	EXPECT_TRUE(t11->isomorphic(t23));
	EXPECT_FALSE(t11->isomorphic(t21));
	EXPECT_FALSE(t11->isomorphic(t25));
}

TEST(TestTree, TestPreorder)
{
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
	std::vector<Tree*> preorderNodes = t11->preorder(t11);
	std::vector<Tree*> preorderNodesCompare;
	preorderNodesCompare.push_back(t11);
	preorderNodesCompare.push_back(t12);
	preorderNodesCompare.push_back(t14);
	preorderNodesCompare.push_back(t15);
	preorderNodesCompare.push_back(t13);
	EXPECT_EQ(preorderNodes.size(), 5);
	EXPECT_EQ(preorderNodes.size(), preorderNodesCompare.size());
	for (int i = 0; i < preorderNodes.size(); ++i)
	{
		EXPECT_EQ(preorderNodes.at(i), preorderNodesCompare.at(i));
	}
}

TEST(TestTree, TestPostorder)
{
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
	std::vector<Tree*> postorderNodes = t11->postorder(t11);
	std::vector<Tree*> postorderNodesCompare;
	postorderNodesCompare.push_back(t15);
	postorderNodesCompare.push_back(t14);
	postorderNodesCompare.push_back(t13);
	postorderNodesCompare.push_back(t12);
	postorderNodesCompare.push_back(t11);
	EXPECT_EQ(postorderNodes.size(), 5);
	EXPECT_EQ(postorderNodes.size(), postorderNodesCompare.size());
	for (int i = 0; i < postorderNodes.size(); ++i)
	{
		EXPECT_EQ(postorderNodes.at(i), postorderNodesCompare.at(i));
	}
}

TEST(TestTree, TestDescendants)
{
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
	std::vector<Tree*> descendants = t11->getDescendants();
	std::vector<Tree*> descendantsCompare;
	descendantsCompare.push_back(t12);
	descendantsCompare.push_back(t14);
	descendantsCompare.push_back(t15);
	descendantsCompare.push_back(t13);
	EXPECT_EQ(descendants.size(), 4);
	EXPECT_EQ(descendants.size(), descendantsCompare.size());
	for (int i = 0; i < descendants.size(); ++i)
	{
		EXPECT_EQ(descendants.at(i), descendantsCompare.at(i));
	}
}

TEST(TestHIPList, TestPeekMax)
{
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
	EXPECT_EQ(hipList.peekMax(), 5);
}

TEST(TestHIPList, TestPop)
{
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

	int oldSize = hipList.size();
	std::vector<Tree*> vec = hipList.pop();
	std::vector<Tree*>::iterator vecIt;
	EXPECT_EQ(vec.size(), 1);
	EXPECT_EQ(vec.at(0), t0);
	EXPECT_EQ(hipList.size(), oldSize - 1);
}

TEST(TestHIPList, TestOpen)
{
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

	Tree* t10 = new Tree("A", "B");
	Tree* t11 = new Tree("B", "C");
	Tree* t12 = new Tree("C", "D");
	t10->addChildren(t11);
	t10->addChildren(t12);
	t11->setParent(t10);
	t12->setParent(t10);
	hipList.open(t10);
	EXPECT_TRUE(hipList.contains(t11));
	EXPECT_TRUE(hipList.contains(t12));
}

TEST(TestAlgorithm1, TestCompute1)
{
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
	t22->setParent(t21);
	t23->setParent(t21);
	t24->setParent(t22);
	t25->setParent(t23);
	t26->setParent(t25);
	t27->setParent(t25);
	t28->setParent(t27);
	HIPList L1;
	HIPList L2;
	int minHeight = 3;
	std::vector<std::pair<Tree*, Tree*>> candidateMappings;
	std::vector<std::pair<Tree*, Tree*>> resultMappings;
	Algorithm1 algo;
	algo.compute(t11, t23, minHeight, L1, L2, candidateMappings, resultMappings);
	std::vector<std::pair<Tree*, Tree*>> testResultMap;
	std::vector<std::pair<Tree*, Tree*>> mapIt;
	testResultMap.push_back(std::pair<Tree*, Tree*>(t12, t25));
	testResultMap.push_back(std::pair<Tree*, Tree*>(t14, t27));
	testResultMap.push_back(std::pair<Tree*, Tree*>(t15, t28));
	testResultMap.push_back(std::pair<Tree*, Tree*>(t13, t26));
	EXPECT_EQ(testResultMap.size(), resultMappings.size());
	EXPECT_EQ(testResultMap.size(), 4);

	for (int i = 0; i < testResultMap.size(); ++i)
	{
		EXPECT_EQ(testResultMap.at(i), resultMappings.at(i));
	}
}

TEST(TestAlgorithm1, TestCompute2)
{
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
	Tree* t26 = new Tree("Modifier", "Public");
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
}

TEST(TestTreePair, TestFindPair)
{
	Tree* t1 = new Tree("A", "A");
	Tree* t2 = new Tree("B", "B");
	Tree* t3 = new Tree("C", "C");
	Tree* t4 = new Tree("D", "D");
	Tree* t5 = new Tree("E", "E");
	Tree* t6 = new Tree("F", "F");
	Tree* t7 = new Tree("G", "G");
	Tree* t8 = new Tree("H", "H");

	std::vector<std::pair<Tree*, Tree*>> map;
	map.push_back(std::pair<Tree*, Tree*>(t1, t2));
	map.push_back(std::pair<Tree*, Tree*>(t3, t4));
	map.push_back(std::pair<Tree*, Tree*>(t5, t6));
	map.push_back(std::pair<Tree*, Tree*>(t7, t8));
	EXPECT_TRUE(TreePair::findPair(t1, t2, map));
	EXPECT_TRUE(TreePair::findPair(t3, t4, map));
	EXPECT_TRUE(TreePair::findPair(t5, t6, map));
	EXPECT_TRUE(TreePair::findPair(t7, t8, map));
	EXPECT_FALSE(TreePair::findPair(t2, t3, map));
	EXPECT_FALSE(TreePair::findPair(t4, t5, map));
	EXPECT_FALSE(TreePair::findPair(t6, t7, map));
	EXPECT_FALSE(TreePair::findPair(t1, t4, map));
	EXPECT_FALSE(TreePair::findPair(t3, t6, map));
	EXPECT_FALSE(TreePair::findPair(t5, t8, map));
	EXPECT_FALSE(TreePair::findPair(t3, t2, map));
	EXPECT_FALSE(TreePair::findPair(t7, t6, map));
	EXPECT_FALSE(TreePair::findPair(t5, t4, map));
}

TEST(TestTreePair, TestIsMatched)
{
	Tree* t1 = new Tree("A", "A");
	Tree* t2 = new Tree("B", "B");
	Tree* t3 = new Tree("C", "C");
	Tree* t4 = new Tree("D", "D");
	Tree* t5 = new Tree("E", "E");
	Tree* t6 = new Tree("F", "F");
	Tree* t7 = new Tree("G", "G");
	Tree* t8 = new Tree("H", "H");
	Tree* t9 = new Tree("I", "I");
	Tree* t10 = new Tree("J", "J");
	Tree* t11 = new Tree("K", "K");
	std::vector<std::pair<Tree*, Tree*>> map;
	map.push_back(std::pair<Tree*, Tree*>(t1, t2));
	map.push_back(std::pair<Tree*, Tree*>(t3, t4));
	map.push_back(std::pair<Tree*, Tree*>(t5, t6));
	map.push_back(std::pair<Tree*, Tree*>(t7, t8));
	EXPECT_TRUE(TreePair::isMatched(t1, map));
	EXPECT_TRUE(TreePair::isMatched(t2, map));
	EXPECT_TRUE(TreePair::isMatched(t3, map));
	EXPECT_TRUE(TreePair::isMatched(t4, map));
	EXPECT_TRUE(TreePair::isMatched(t5, map));
	EXPECT_TRUE(TreePair::isMatched(t6, map));
	EXPECT_TRUE(TreePair::isMatched(t7, map));
	EXPECT_TRUE(TreePair::isMatched(t8, map));
	EXPECT_FALSE(TreePair::isMatched(t9, map));
	EXPECT_FALSE(TreePair::isMatched(t10, map));
	EXPECT_FALSE(TreePair::isMatched(t11, map));
}

TEST(TestTreePair, TestHasMatchedChild)
{
	Tree* t0 = new Tree("0", "0");
	Tree* t1 = new Tree("A", "A");
	Tree* t2 = new Tree("B", "B");
	Tree* t3 = new Tree("C", "C");
	Tree* t4 = new Tree("D", "D");
	Tree* t5 = new Tree("E", "E");
	Tree* t6 = new Tree("F", "F");
	Tree* t7 = new Tree("G", "G");
	Tree* t8 = new Tree("H", "H");
	std::vector<std::pair<Tree*, Tree*>> map;
	map.push_back(std::pair<Tree*, Tree*>(t1, t2));
	map.push_back(std::pair<Tree*, Tree*>(t3, t4));
	map.push_back(std::pair<Tree*, Tree*>(t5, t6));
	map.push_back(std::pair<Tree*, Tree*>(t7, t8));
	t0->addChildren(t1);
	t0->addChildren(t2);
	t0->addChildren(t3);
	t0->addChildren(t4);
	t5->addChildren(t6);
	EXPECT_TRUE(TreePair::hasMatchedChild(t0, map));
	EXPECT_FALSE(TreePair::hasMatchedChild(t1, map));
	EXPECT_FALSE(TreePair::hasMatchedChild(t2, map));
	EXPECT_FALSE(TreePair::hasMatchedChild(t3, map));
	EXPECT_FALSE(TreePair::hasMatchedChild(t4, map));
	EXPECT_TRUE(TreePair::hasMatchedChild(t5, map));
}

TEST(TestTree, TestHasSomeMatchingDesc)
{
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
	t22->setParent(t21);
	t23->setParent(t21);
	t24->setParent(t22);
	t25->setParent(t23);
	t26->setParent(t25);
	t27->setParent(t25);
	t28->setParent(t27);
	std::vector <std::pair<Tree*, Tree*>> map;
	map.push_back(std::pair<Tree*, Tree*>(t12, t25));
	map.push_back(std::pair<Tree*, Tree*>(t13, t26));
	map.push_back(std::pair<Tree*, Tree*>(t14, t27));
	map.push_back(std::pair<Tree*, Tree*>(t15, t28));
	EXPECT_TRUE(t11->hasSomeMatchingDesc(t11, 3, map));
	EXPECT_TRUE(t21->hasSomeMatchingDesc(t21, 3, map));
	EXPECT_TRUE(t12->hasSomeMatchingDesc(t12, 3, map));
	EXPECT_TRUE(t23->hasSomeMatchingDesc(t23, 3, map));
	EXPECT_TRUE(t25->hasSomeMatchingDesc(t25, 3, map));
	EXPECT_FALSE(t26->hasSomeMatchingDesc(t26, 3, map));
	EXPECT_FALSE(t27->hasSomeMatchingDesc(t27, 3, map));
	EXPECT_FALSE(t28->hasSomeMatchingDesc(t28, 3, map));
	EXPECT_FALSE(t15->hasSomeMatchingDesc(t15, 3, map));
	EXPECT_FALSE(t14->hasSomeMatchingDesc(t14, 3, map));
	EXPECT_FALSE(t13->hasSomeMatchingDesc(t13, 3, map));
}

TEST(TestTree, TestCandidate)
{
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
	EXPECT_EQ(t2Candidates.size(), 1);
}

