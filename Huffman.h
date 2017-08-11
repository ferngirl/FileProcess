
#include<stdio.h>
#include<iostream>
using namespace std;

#include"heap.h"//引用堆的创建文件

//huffman树节点的创建
template<class T>
struct Node
{
	Node(const T& weight, const T& data = T())
	:_pLeft(NULL)
	, _pRight(NULL)
	, _pParent(NULL)
	, _weight(weight)
	, _data(data)
	{}

	Node* _pLeft;//左孩子
	Node* _pRight;//右孩子
	Node* _pParent;//双亲节点
	T _data;//节点值
	T _weight;//节点对应权值
};

//仿函数
template<class T>
struct ComplareNode
{
	bool operator()(Node<T>* pLeft, Node<T>* pRight)
	{
		return pLeft->_weight<pRight->_weight;
	}
};

template<class T>
class HuffmanTree
{
public:
	HuffmanTree()
		:_pRoot(NULL)
	{}

	//构造huffman树
	HuffmanTree(const T array[], size_t size, T& invalid)
	{
		//首先，我们要将数组中所有权值的数转化为节点的森林
		//然后选择权值最小的两个节点做为左右子树组建成一棵树，根节点的权值为这两个节点的权值之和，将该树放入我们的森林里
		//再继续重复上一步骤，直到剩下最后一个节点，该节点就是一棵huffman树的根节点

		//针对于如何在森林中选取权值最小的两个节点，我们可以根据我们刚刚学的堆来处理，用森另中的所有节点建立一个小堆，每次选取堆顶的元素

		_CreateHuffmanTree(array, size, invalid);
	}

	Node<T>* GetRoot()const//因为pRoot是私有成员，外部函数不能访问
	{
		return _pRoot;
	}

private:
	void _CreateHuffmanTree(const T array[], size_t size,const T& invalid)
	{
		heap<Node<T>*, ComplareNode<T>> hp;//创建一个堆，用来存放森林

		for (size_t idx = 0; idx<size; ++idx)//将权值转化为节点存入堆中
		{
		//	if (array[idx]._appearCount != invalid._appearCount)
				hp.Insert(new Node<T>(array[idx]));

		}
		//存在问题！！！！我们前面实现的堆在调整时比较的是节点的data值
		//因为我们的vector里存放的是T类型，但是我们现在vector里存放的是Node<T>*,所以调整时不能再用 <和>直接比较
		//如果直接比较比较的将是两个地址，而我们要比较的则是节点的权值，但vector里又不能存放权值，如果存放的是权值，
		//新产生的树将会丢失，所以我们必须重新定义比较类

		while (hp.Size()>1)
		{
			Node<T>* pLeft = hp.Top();//在堆中选取两个最小权值的节点，作为左右孩子组建成新的树
			hp.Remove();
			Node<T>* pRight = hp.Top();
			hp.Remove();
			

			Node<T>* pParent = new Node<T>(pLeft->_weight + pRight->_weight);
			pParent->_pLeft = pLeft;
			pLeft->_pParent = pParent;
			pParent->_pRight = pRight;
			pRight->_pParent = pParent;

			hp.Insert(pParent);//将树放入森林
		}
		_pRoot = hp.Top();
	}
private:
	Node<T>* _pRoot;
};
