#include "pch.h"
#include "Tree.h"
#include "HIPList.h"

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
