
#include<stdio.h>
#include<vector>
#include<assert.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

//下面是实现的小堆，同时我们也要实现大堆(只是将交换比较的小于号都改成大于号)，为了实现代码的复用率，我们多添加一个模板参数---比较器(容器适配器)
//容器适配器的两种实现：模板的模板参数，模板参数


//仿函数实现operator()
template<class T>
struct Less//小堆
{
	bool operator()(const T& left, const T& right)//重载(),在里面实现对<号的实现
	{
		return left<right;
	}
};
template<class T>
struct Greater//大堆
{
	bool operator()(const T& left, const T& right)
	{
		return left>right;
	}
};

//实现堆算法，Complare做为模板参数，实现了一个比较器，默认是小堆
template<class T, class Complare = Less<T> >
class heap
{
public:
	heap()
		:_heap(NULL)
	{}
	heap(const T array[], size_t size)
	{
		//找到倒数第一个非叶子节点，即最后一个节点(下标为i)的双亲节点(i-1)/2
		//从该节点的位置开始判断其最小子节点是否小于双亲节点，即向下调整判断法
		//若小于，则交换位置，并且向下判断，更新双亲节点为子节点，重复执行上面的代码
		//若大于，则不交换，判断上一个节点（层序遍历倒数第二个节点）,退出当前节点的遍历

		//初始化容器
		_heap.resize(size);
		for (int idx = 0; idx<_heap.size(); ++idx)
			_heap[idx] = array[idx];
		//_heap.push_back(array[idx]);

		int parent = (size - 2) >> 1;
		for (; parent >= 0; --parent)
			AdjustDown(_heap, parent);
	}

	//堆的大小
	size_t Size()const
	{
		return _heap.size();
	}

	//堆是否为NULL
	bool Empty()const
	{
		return _heap.empty();
	}

	//堆顶的元素
	const T& Top()const
	{
		return _heap[0];
	}

	//堆的任意插入
	void Insert(const T& value)
	{
		_heap.push_back(value);
		if (_heap.size()>1)
			AdjustUp();
	}

	//删除堆顶的元素
	void Remove()
	{
		//删除堆顶的元素，将堆顶的元素和最后一个节点进行交换，
		//push_back最后一个元素，利用向下调整的方法调整小堆

		assert(!_heap.empty());
		int last = _heap.size() - 1;
		swap(_heap[0], _heap[last]);
		_heap.pop_back();

		//AdjustDown(_heap,0);//因为现在只有根节点发生改变，左右子树还是满足最小堆的条件的，所以我们只要调整根节点就好
		//利用向下调整的方法（注意这和堆的创建是不同的，堆的创建是从倒数第一个非叶子节点开始调整）
		if (_heap.size() <= 1)//只剩下一个节点或没有节点时，不用再调整
			return;
		int parent = (_heap.size() - 2) >> 1;
		for (; parent >= 0; --parent)
			AdjustDown(_heap, parent);
	}
private:
	//向下调整
	void AdjustDown(vector<T>& _heap, int parent)
	{
		Complare com;//比较器，当比较器是Less(默认)是小堆，当比较器是Greater是大堆
		int child = parent * 2 + 1;
		while (child<_heap.size())
		{
			if ((child + 1)<_heap.size() && com(_heap[child + 1], _heap[child]))//当_heap[child]>_heap[child+1]时，才进入循环，交换左右参数顺序
			{
				child = child + 1;
			}

			if (com(_heap[child], _heap[parent]))//当_heap[child]<_heap[parent]时，进入判断判断体
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

	//向上调整
	void AdjustUp()
	{
		Complare com;
		size_t child = _heap.size() - 1;//插入节点的下标，也是堆中最后一个节点
		size_t parent = (child - 1) >> 1;//倒数第一个非叶子节点

		while (child != 0)
		{
			if (com(_heap[child], _heap[parent]))//插入节点的兄弟节点一定比双亲节点大（小堆）
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

//void AdjustDown(vector<T>& _heap,int parent)//向下调整
//{
//	int child = parent*2+1;
//	while(child<_heap.size())
//	{
//		if((child+1)<_heap.size() && _heap[child] > _heap[child+1])//小堆
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

//void AdjustUp(vector<T>& _heap,int parent)//向上调整
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
//	size_t child = _heap.size()-1;//插入节点的下标，也是堆中最后一个节点
//	size_t parent = (child-1)>>1;//倒数第一个非叶子节点

//	while(child != 0)
//	{
//		if(_heap[child] < _heap[parent])//插入节点的兄弟节点一定比双亲节点大（小堆）
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

//void funtest2()//带模板参数的大小堆测试
//{
//	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
//	heap<int> h1(array, sizeof(array) / sizeof(array[0]));//小堆
//	heap<int, Greater<int> > h2(array, sizeof(array) / sizeof(array[0]));//大堆
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
struct Less//小堆
{
bool operator()(const T& left,const T& right)//重载(),在里面实现对<号的实现
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


template<class T,template<class> class Complare =Less >//模板的模板参数实现比较器,Complare是一个模板类
class heap
{
public:
heap()
:_heap(NULL)
{}
heap(const T array[],size_t size)
{
//找到倒数第一个非叶子节点，即最后一个节点(下标为i)的双亲节点(i-1)/2
//从该节点的位置开始判断其最小子节点是否小于双亲节点，即向下调整判断法
//若小于，则交换位置，并且向下判断，更新双亲节点为子节点，重复执行上面的代码
//若大于，则不交换，判断上一个节点（层序遍历倒数第二个节点）,退出当前节点的遍历

//为什么不能用数组？？？

_heap.resize(size);
for(int idx=0; idx<_heap.size(); ++idx)//初始化容器
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
void Insert(const T& value)//堆的任意插入
{
_heap.push_back(value);
int parent = (_heap.size()-2)>>1;
//AdjustUp(_heap,parent);
AdjustUp();
}

void Remove()//删除堆顶的元素
{
//删除堆顶的元素，将堆顶的元素和最后一个节点进行交换，然后push_back最后一个元素，利用向下调整的方法调整小堆
int last = _heap.size()-1;
swap(_heap[0],_heap[last]);
_heap.pop_back();

AdjustDown(_heap,0);//因为现在只有根节点发生改变，左右子树还是满足最小堆的条件的，所以我们只要调整根节点就好
//利用向下调整的方法（注意这和堆的创建是不同的，堆的创建是从倒数第一个非叶子节点开始调整）
//int parent = (_heap.size()-2)>>1;
//for(; parent>=0; --parent)
//{
//	AdjustDown(_heap,parent);
//}
}
private:
void AdjustDown(vector<T>& _heap,int parent)//向下调整
{
int child = parent*2+1;
while(child<_heap.size())
{//建立一个类模板的无名对象调用()重载函数
if((child+1)<_heap.size() && Complare<T>()(_heap[child+1],_heap[child]))//当_heap[child]>_heap[child+1]时，才进入循环，交换左右参数顺序
{
child = child+1;
}

if(Complare<T>()(_heap[child],_heap[parent]))//当_heap[child]<_heap[parent]时，进入判断判断体
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
size_t child = _heap.size()-1;//插入节点的下标，也是堆中最后一个节点
size_t parent = (child-1)>>1;//倒数第一个非叶子节点

while(child != 0)
{
if(Complare<T>()(_heap[child],_heap[parent]))//插入节点的兄弟节点一定比双亲节点大（小堆）
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
//	heap<int> h1(array,sizeof(array)/sizeof(array[0]));//小堆
//	heap<int,Greater> h2(array,sizeof(array)/sizeof(array[0]));//大堆
//}
//int main()
//{
//	funtest();
//	getchar();
//	return 0;
//}


//堆的应用？？？？？？？
//堆排序？？？？？？

//求数组中最小的k个数
//数据量小---排序
//海量数据---大堆
//int Complare(const void* pLeft,const void* pRight)
//{
//	return *(int*)pLeft-*(int*)pRight;
//}
//自己实现快速排序
//快速排序首先在数组中选择一个随机数，将数组中的数字分为两部分，比选择的数字小的数字移到数组左边，比选择数字大的放在数组右边
//int RandomInRange(size_t size)
//{
//	return rand()%size;
//}
//void MyQsort(int array[],size_t size，int start,int end)
//{
//	if(array == NULL || size<=0 || start<0 || end<0 ||end>size)//判断不合法情况
//		return;
//	size_t index = RandomInRange();//产生随意数
//	for(size_t idx=start; idx<end; ++idx)
//	{
//		if(array[idx] > array[index])
//			swap(array[idx],array[end]);
//	}
//}
//
//void GetLeastNumber(int array[],size_t size,size_t k)
//{
//	//将数组排序升序排序，选取其前k个值,快排
////	qsort(array,size,sizeof(int),Complare);//c库中提供的快排函数(了解其底层实现)
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
