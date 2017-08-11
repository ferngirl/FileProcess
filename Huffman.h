
#include<stdio.h>
#include<iostream>
using namespace std;

#include"heap.h"//���öѵĴ����ļ�

//huffman���ڵ�Ĵ���
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

	Node* _pLeft;//����
	Node* _pRight;//�Һ���
	Node* _pParent;//˫�׽ڵ�
	T _data;//�ڵ�ֵ
	T _weight;//�ڵ��ӦȨֵ
};

//�º���
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

	//����huffman��
	HuffmanTree(const T array[], size_t size, T& invalid)
	{
		//���ȣ�����Ҫ������������Ȩֵ����ת��Ϊ�ڵ��ɭ��
		//Ȼ��ѡ��Ȩֵ��С�������ڵ���Ϊ���������齨��һ���������ڵ��ȨֵΪ�������ڵ��Ȩֵ֮�ͣ��������������ǵ�ɭ����
		//�ټ����ظ���һ���裬ֱ��ʣ�����һ���ڵ㣬�ýڵ����һ��huffman���ĸ��ڵ�

		//����������ɭ����ѡȡȨֵ��С�������ڵ㣬���ǿ��Ը������Ǹո�ѧ�Ķ���������ɭ���е����нڵ㽨��һ��С�ѣ�ÿ��ѡȡ�Ѷ���Ԫ��

		_CreateHuffmanTree(array, size, invalid);
	}

	Node<T>* GetRoot()const//��ΪpRoot��˽�г�Ա���ⲿ�������ܷ���
	{
		return _pRoot;
	}

private:
	void _CreateHuffmanTree(const T array[], size_t size,const T& invalid)
	{
		heap<Node<T>*, ComplareNode<T>> hp;//����һ���ѣ��������ɭ��

		for (size_t idx = 0; idx<size; ++idx)//��Ȩֵת��Ϊ�ڵ�������
		{
		//	if (array[idx]._appearCount != invalid._appearCount)
				hp.Insert(new Node<T>(array[idx]));

		}
		//�������⣡����������ǰ��ʵ�ֵĶ��ڵ���ʱ�Ƚϵ��ǽڵ��dataֵ
		//��Ϊ���ǵ�vector���ŵ���T���ͣ�������������vector���ŵ���Node<T>*,���Ե���ʱ�������� <��>ֱ�ӱȽ�
		//���ֱ�ӱȽϱȽϵĽ���������ַ��������Ҫ�Ƚϵ����ǽڵ��Ȩֵ����vector���ֲ��ܴ��Ȩֵ�������ŵ���Ȩֵ��
		//�²����������ᶪʧ���������Ǳ������¶���Ƚ���

		while (hp.Size()>1)
		{
			Node<T>* pLeft = hp.Top();//�ڶ���ѡȡ������СȨֵ�Ľڵ㣬��Ϊ���Һ����齨���µ���
			hp.Remove();
			Node<T>* pRight = hp.Top();
			hp.Remove();
			

			Node<T>* pParent = new Node<T>(pLeft->_weight + pRight->_weight);
			pParent->_pLeft = pLeft;
			pLeft->_pParent = pParent;
			pParent->_pRight = pRight;
			pRight->_pParent = pParent;

			hp.Insert(pParent);//��������ɭ��
		}
		_pRoot = hp.Top();
	}
private:
	Node<T>* _pRoot;
};
