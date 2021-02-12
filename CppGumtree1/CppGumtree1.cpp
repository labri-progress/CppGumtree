#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "Tree.h"
#if 0
TEST(TestTree, TestAdd1) {

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

#endif

int main(int argc, char* argv[])
{
#if 0
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

	t0->move(t0, t7, 1);
	t0->print(t0);
#endif

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
	int h = t0->height(t0);
	std::cout << "Height: " << h << std::endl;
	return 0;
}