
#include<stdio.h>
#include<vector>
#include<assert.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

//������ʵ�ֵ�С�ѣ�ͬʱ����ҲҪʵ�ִ��(ֻ�ǽ������Ƚϵ�С�ںŶ��ĳɴ��ں�)��Ϊ��ʵ�ִ���ĸ����ʣ����Ƕ����һ��ģ�����---�Ƚ���(����������)
//����������������ʵ�֣�ģ���ģ�������ģ�����


//�º���ʵ��operator()
template<class T>
struct Less//С��
{
	bool operator()(const T& left, const T& right)//����(),������ʵ�ֶ�<�ŵ�ʵ��
	{
		return left<right;
	}
};
template<class T>
struct Greater//���
{
	bool operator()(const T& left, const T& right)
	{
		return left>right;
	}
};

//ʵ�ֶ��㷨��Complare��Ϊģ�������ʵ����һ���Ƚ�����Ĭ����С��
template<class T, class Complare = Less<T> >
class heap
{
public:
	heap()
		:_heap(NULL)
	{}
	heap(const T array[], size_t size)
	{
		//�ҵ�������һ����Ҷ�ӽڵ㣬�����һ���ڵ�(�±�Ϊi)��˫�׽ڵ�(i-1)/2
		//�Ӹýڵ��λ�ÿ�ʼ�ж�����С�ӽڵ��Ƿ�С��˫�׽ڵ㣬�����µ����жϷ�
		//��С�ڣ��򽻻�λ�ã����������жϣ�����˫�׽ڵ�Ϊ�ӽڵ㣬�ظ�ִ������Ĵ���
		//�����ڣ��򲻽������ж���һ���ڵ㣨������������ڶ����ڵ㣩,�˳���ǰ�ڵ�ı���

		//��ʼ������
		_heap.resize(size);
		for (int idx = 0; idx<_heap.size(); ++idx)
			_heap[idx] = array[idx];
		//_heap.push_back(array[idx]);

		int parent = (size - 2) >> 1;
		for (; parent >= 0; --parent)
			AdjustDown(_heap, parent);
	}

	//�ѵĴ�С
	size_t Size()const
	{
		return _heap.size();
	}

	//���Ƿ�ΪNULL
	bool Empty()const
	{
		return _heap.empty();
	}

	//�Ѷ���Ԫ��
	const T& Top()const
	{
		return _heap[0];
	}

	//�ѵ��������
	void Insert(const T& value)
	{
		_heap.push_back(value);
		if (_heap.size()>1)
			AdjustUp();
	}

	//ɾ���Ѷ���Ԫ��
	void Remove()
	{
		//ɾ���Ѷ���Ԫ�أ����Ѷ���Ԫ�غ����һ���ڵ���н�����
		//push_back���һ��Ԫ�أ��������µ����ķ�������С��

		assert(!_heap.empty());
		int last = _heap.size() - 1;
		swap(_heap[0], _heap[last]);
		_heap.pop_back();

		//AdjustDown(_heap,0);//��Ϊ����ֻ�и��ڵ㷢���ı䣬������������������С�ѵ������ģ���������ֻҪ�������ڵ�ͺ�
		//�������µ����ķ�����ע����ͶѵĴ����ǲ�ͬ�ģ��ѵĴ����Ǵӵ�����һ����Ҷ�ӽڵ㿪ʼ������
		if (_heap.size() <= 1)//ֻʣ��һ���ڵ��û�нڵ�ʱ�������ٵ���
			return;
		int parent = (_heap.size() - 2) >> 1;
		for (; parent >= 0; --parent)
			AdjustDown(_heap, parent);
	}
private:
	//���µ���
	void AdjustDown(vector<T>& _heap, int parent)
	{
		Complare com;//�Ƚ��������Ƚ�����Less(Ĭ��)��С�ѣ����Ƚ�����Greater�Ǵ��
		int child = parent * 2 + 1;
		while (child<_heap.size())
		{
			if ((child + 1)<_heap.size() && com(_heap[child + 1], _heap[child]))//��_heap[child]>_heap[child+1]ʱ���Ž���ѭ�����������Ҳ���˳��
			{
				child = child + 1;
			}

			if (com(_heap[child], _heap[parent]))//��_heap[child]<_heap[parent]ʱ�������ж��ж���
			{
				swap(_heap[parent], _heap[child]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
			{
				return;
			}
		}
	}

	//���ϵ���
	void AdjustUp()
	{
		Complare com;
		size_t child = _heap.size() - 1;//����ڵ���±꣬Ҳ�Ƕ������һ���ڵ�
		size_t parent = (child - 1) >> 1;//������һ����Ҷ�ӽڵ�

		while (child != 0)
		{
			if (com(_heap[child], _heap[parent]))//����ڵ���ֵܽڵ�һ����˫�׽ڵ��С�ѣ�
			{
				swap(_heap[child], _heap[parent]);
				child = parent;
				parent = (child - 1) >> 1;
			}
			else
			{

				return;
			}
		}
	}
//private:
	public:
	vector<T> _heap;
};

//void AdjustDown(vector<T>& _heap,int parent)//���µ���
//{
//	int child = parent*2+1;
//	while(child<_heap.size())
//	{
//		if((child+1)<_heap.size() && _heap[child] > _heap[child+1])//С��
//		{
//			child = child+1;
//		}

//		if(_heap[parent] > _heap[child])
//		{
//			swap(_heap[parent],_heap[child]);
//			parent = child;
//			child = 2*parent+1;
//		}
//		else
//		{
//			return;
//		}
//	}
//}

//void AdjustUp(vector<T>& _heap,int parent)//���ϵ���
//{
//	int child = parent*2+1;
//	while(parent>=0)
//	{
//		if((child+1)<_heap.size() && _heap[child] > _heap[child+1])
//			child = child+1;
//		if(_heap[parent] > _heap[child])
//		{
//			swap(_heap[parent],_heap[child]);
//		}
//		child= parent;
//		parent = (child-1)>>1;
//	}
//}

//void AdjustUp()
//{
//	size_t child = _heap.size()-1;//����ڵ���±꣬Ҳ�Ƕ������һ���ڵ�
//	size_t parent = (child-1)>>1;//������һ����Ҷ�ӽڵ�

//	while(child != 0)
//	{
//		if(_heap[child] < _heap[parent])//����ڵ���ֵܽڵ�һ����˫�׽ڵ��С�ѣ�
//		{
//			swap(_heap[child],_heap[parent]);
//			child = parent;
//			parent = (child-1)>>1;
//		}
//	}
//}
//private:
//	vector<T> _heap;
//};


//void funtest1()
//{
//	int array[] = {53,17,78};
//	heap<int> h;
//	heap<int> h1(array,sizeof(array)/sizeof(array[0]));
//	size_t ret = h1.Size();
//	bool ret1 = h1.Empty();
//	h1.Insert(100);
//	h1.Remove();
//	h1.Remove();
//	h1.Remove();
//}

//void funtest2()//��ģ������Ĵ�С�Ѳ���
//{
//	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
//	heap<int> h1(array, sizeof(array) / sizeof(array[0]));//С��
//	heap<int, Greater<int> > h2(array, sizeof(array) / sizeof(array[0]));//���
//}
//int main()
//{
//	//funtest1();
//	funtest2();
//	getchar();
//	return 0;
//}


/*
template<class T>
struct Less//С��
{
bool operator()(const T& left,const T& right)//����(),������ʵ�ֶ�<�ŵ�ʵ��
{
return left<right;
}
};

template<class T>
struct Greater
{
bool operator()(const T& left,const T& right)
{
return left>right;
}
};


template<class T,template<class> class Complare =Less >//ģ���ģ�����ʵ�ֱȽ���,Complare��һ��ģ����
class heap
{
public:
heap()
:_heap(NULL)
{}
heap(const T array[],size_t size)
{
//�ҵ�������һ����Ҷ�ӽڵ㣬�����һ���ڵ�(�±�Ϊi)��˫�׽ڵ�(i-1)/2
//�Ӹýڵ��λ�ÿ�ʼ�ж�����С�ӽڵ��Ƿ�С��˫�׽ڵ㣬�����µ����жϷ�
//��С�ڣ��򽻻�λ�ã����������жϣ�����˫�׽ڵ�Ϊ�ӽڵ㣬�ظ�ִ������Ĵ���
//�����ڣ��򲻽������ж���һ���ڵ㣨������������ڶ����ڵ㣩,�˳���ǰ�ڵ�ı���

//Ϊʲô���������飿����

_heap.resize(size);
for(int idx=0; idx<_heap.size(); ++idx)//��ʼ������
_heap[idx] = array[idx];
//_heap.push_back(array[idx]);

int parent = (size-2)>>1;
for(; parent>=0; --parent)
{
AdjustDown(_heap,parent);
}
}

size_t Size()const
{
return _heap.size();
}

bool Empty()const
{
return _heap.empty();
}

const T& Top()const
{
return _heap[0];
}
void Insert(const T& value)//�ѵ��������
{
_heap.push_back(value);
int parent = (_heap.size()-2)>>1;
//AdjustUp(_heap,parent);
AdjustUp();
}

void Remove()//ɾ���Ѷ���Ԫ��
{
//ɾ���Ѷ���Ԫ�أ����Ѷ���Ԫ�غ����һ���ڵ���н�����Ȼ��push_back���һ��Ԫ�أ��������µ����ķ�������С��
int last = _heap.size()-1;
swap(_heap[0],_heap[last]);
_heap.pop_back();

AdjustDown(_heap,0);//��Ϊ����ֻ�и��ڵ㷢���ı䣬������������������С�ѵ������ģ���������ֻҪ�������ڵ�ͺ�
//�������µ����ķ�����ע����ͶѵĴ����ǲ�ͬ�ģ��ѵĴ����Ǵӵ�����һ����Ҷ�ӽڵ㿪ʼ������
//int parent = (_heap.size()-2)>>1;
//for(; parent>=0; --parent)
//{
//	AdjustDown(_heap,parent);
//}
}
private:
void AdjustDown(vector<T>& _heap,int parent)//���µ���
{
int child = parent*2+1;
while(child<_heap.size())
{//����һ����ģ��������������()���غ���
if((child+1)<_heap.size() && Complare<T>()(_heap[child+1],_heap[child]))//��_heap[child]>_heap[child+1]ʱ���Ž���ѭ�����������Ҳ���˳��
{
child = child+1;
}

if(Complare<T>()(_heap[child],_heap[parent]))//��_heap[child]<_heap[parent]ʱ�������ж��ж���
{
swap(_heap[parent],_heap[child]);
parent = child;
child = 2*parent+1;
}
else
{
return;
}
}
}

void AdjustUp()
{
size_t child = _heap.size()-1;//����ڵ���±꣬Ҳ�Ƕ������һ���ڵ�
size_t parent = (child-1)>>1;//������һ����Ҷ�ӽڵ�

while(child != 0)
{
if(Complare<T>()(_heap[child],_heap[parent]))//����ڵ���ֵܽڵ�һ����˫�׽ڵ��С�ѣ�
{
swap(_heap[child],_heap[parent]);
child = parent;
parent = (child-1)>>1;
}
}
}
private:
vector<T> _heap;
};

//void funtest()
//{
//	int array[] = {53,17,78,9,45,65,87,23};
//	heap<int> h1(array,sizeof(array)/sizeof(array[0]));//С��
//	heap<int,Greater> h2(array,sizeof(array)/sizeof(array[0]));//���
//}
//int main()
//{
//	funtest();
//	getchar();
//	return 0;
//}


//�ѵ�Ӧ�ã�������������
//�����򣿣���������

//����������С��k����
//������С---����
//��������---���
//int Complare(const void* pLeft,const void* pRight)
//{
//	return *(int*)pLeft-*(int*)pRight;
//}
//�Լ�ʵ�ֿ�������
//��������������������ѡ��һ����������������е����ַ�Ϊ�����֣���ѡ�������С�������Ƶ�������ߣ���ѡ�����ִ�ķ��������ұ�
//int RandomInRange(size_t size)
//{
//	return rand()%size;
//}
//void MyQsort(int array[],size_t size��int start,int end)
//{
//	if(array == NULL || size<=0 || start<0 || end<0 ||end>size)//�жϲ��Ϸ����
//		return;
//	size_t index = RandomInRange();//����������
//	for(size_t idx=start; idx<end; ++idx)
//	{
//		if(array[idx] > array[index])
//			swap(array[idx],array[end]);
//	}
//}
//
//void GetLeastNumber(int array[],size_t size,size_t k)
//{
//	//������������������ѡȡ��ǰk��ֵ,����
////	qsort(array,size,sizeof(int),Complare);//c�����ṩ�Ŀ��ź���(�˽���ײ�ʵ��)
//	MyQsort(array,size);
//	for(size_t idx=0; idx<k; ++idx)
//	{
//		cout<<array[idx]<<" ";
//	}
//}
//void funtest()
//{
//	int array[] = {4,2,7,5,1,8,9};
//	GetLeastNumber(array,7,3);
//}
//int main()
//{
//	funtest();
//	getchar();
//	return 0;
//}
*/
