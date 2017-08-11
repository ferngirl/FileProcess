#if 0
#include"gtest/gtest.h"
#include"Huffman.h"
#include<stdio.h> 

//对huffman树的节点进行测试
TEST(huffmanCaseTest, NodeTest)
{
	typedef Node<int> Node;
	Node* pNode = new Node(1);
	ASSERT_EQ(pNode->_data, 0);
	ASSERT_EQ(pNode->_weight, 1);
	ASSERT_FALSE(pNode->_pLeft);
	ASSERT_FALSE(pNode->_pParent);
	ASSERT_FALSE(pNode->_pRight);
}

//对huffman树的构造进行测试
TEST(HuffmanCaseTest, ConstructChildTest)
{
	HuffmanTree<int> h1;//测试用例1
	ASSERT_FALSE(h1.GetRoot());

	int arr[] = { 6, 4, 8, 7, 2, 5 };
	HuffmanTree<int>h2(arr, sizeof(arr) / sizeof(arr[0]), 0);
	typedef Node<int> Node;
	Node* pRoot = h2.GetRoot();
	ASSERT_EQ(pRoot->_weight, 32);
	ASSERT_EQ(pRoot->_pLeft->_weight, 13);
	ASSERT_EQ(pRoot->_pRight->_weight, 19);

	Node* pLeft = pRoot->_pLeft;
	Node* pRight = pRoot->_pRight;
	ASSERT_EQ(pLeft->_pLeft->_weight, 6);
	ASSERT_EQ(pLeft->_pRight->_weight, 7);
	ASSERT_EQ(pRight->_pLeft->_weight, 8);
	ASSERT_EQ(pRight->_pRight->_weight,11);
	
	Node* pLLeft = pLeft->_pLeft;
	Node* pRRight = pRight->_pRight;
	ASSERT_EQ(pRRight->_pLeft->_weight, 5);
	ASSERT_EQ(pRRight->_pRight->_weight, 6);

	Node* Right = pRRight->_pRight;
	ASSERT_EQ(Right->_pLeft->_weight, 2);
	ASSERT_EQ(Right->_pRight->_weight, 4);
}

TEST(HuffmanCaseTest, ConstructParentTest)
{
	int arr[] = { 6, 4, 8, 7, 2, 5 };
	HuffmanTree<int>h(arr, sizeof(arr) / sizeof(arr[0]), 0);
	typedef Node<int> Node;

	Node* pRoot = h.GetRoot();
	ASSERT_FALSE(pRoot->_pParent);

	Node* pLeft = pRoot->_pLeft;
	ASSERT_EQ(pLeft->_pParent->_weight,32);
	Node* pRight = pRoot->_pRight;
	ASSERT_EQ(pRight->_pParent->_weight, 32);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	int a = RUN_ALL_TESTS();
	getchar();
	return a;
}
#endif
