
#include"heap.h"
#include"gtest/gtest.h"

//测试小堆的构造函数
TEST(HeapTestCase, SmallHeapConstruct)
{
	int arr1[] = { 12, 6, 8, 3, 9, 15 };//测试用例1
	int arr2[] = {0 ,0, 0, 0, 0, 0};//测试用例2
	int arr3[3] = {};//测试用例3
	int smallHeap[] = { 3, 6, 8, 12, 9, 15 };//小堆测试结果---测试用例1
	
	heap<int> h1(arr1, sizeof(arr1) / sizeof(arr1[0]));
	for (size_t index = 0; index < sizeof(arr1) / sizeof(arr1[0]); ++index)
	{
		int a = h1._heap[index];
		int b = smallHeap[index];
		ASSERT_EQ(a, b);
	}
	
	heap<int> h2(arr2, sizeof(arr2) / sizeof(arr2[0]));
	for (size_t index = 0; index < sizeof(arr2) / sizeof(arr2[0]); ++index)
	{
		ASSERT_EQ(h2._heap[index], 0);
	}
	
	heap<int> h3(arr3, sizeof(arr3) / sizeof(arr3[0]));
	for (size_t index = 0; index <sizeof(arr3) / sizeof(arr3[0]); ++index)
	{
		ASSERT_EQ(h3._heap[index], 0);
	}
}
//测试大堆的构造函数
TEST(HeapTestCase, GreaterHeapConstruct)
{
	int arr1[] = { 12, 6, 8, 3, 9, 15 };//测试用例1
	int arr2[] = { 0, 0, 0, 0, 0, 0 };//测试用例2
	int arr3[3] = {};//测试用例3
	int greaterHeap[] = { 15, 9, 12, 3, 6, 8};//大堆测试结果---测试用例1

	heap<int,Greater<int>> h1(arr1, sizeof(arr1) / sizeof(arr1[0]));
	for (size_t index = 0; index < sizeof(arr1) / sizeof(arr1[0]); ++index)
	{
		int a = h1._heap[index];
		int b = greaterHeap[index];
		ASSERT_EQ(a, b);
	}
	
	heap<int> h2(arr2, sizeof(arr2) / sizeof(arr2[0]));
	for (size_t index = 0; index < sizeof(arr2) / sizeof(arr2[0]); ++index)
	{
		ASSERT_EQ(h2._heap[index], 0);
	}

	heap<int> h3(arr3, sizeof(arr3) / sizeof(arr3[0]));
	for (size_t index = 0; index <sizeof(arr3) / sizeof(arr3[0]); ++index)
	{
		ASSERT_EQ(h3._heap[index], 0);
	}
}
//测试Size函数
TEST(HeapTestCase, SizeTest)
{
	int arr1[] = { 12, 6, 8, 3, 9, 15 };//测试用例1
	int arr2[] = { 1 };//测试用例2

	//小堆
	heap<int> h1(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int> h2(arr2, sizeof(arr2) / sizeof(arr2));
	heap<int> h3;//测试用例3

	EXPECT_EQ(h1.Size(), 6);
	EXPECT_EQ(h2.Size(), 1);
	EXPECT_EQ(h3.Size(), 0);

	//大堆
	heap<int,Greater<int>> h4(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int,Greater<int>> h5(arr2, sizeof(arr2) / sizeof(arr2));
	heap<int,Greater<int>> h6;//测试用例3

	EXPECT_EQ(h4.Size(), 6);
	EXPECT_EQ(h5.Size(), 1);
	EXPECT_EQ(h6.Size(), 0);
}
//测试empty函数
TEST(HeapTestCase, EmptyTest)
{
	int arr1[] = { 12, 6, 8, 3, 9, 15 };//测试用例1

	//小堆
	heap<int> h1(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int> h2;//测试用例2

	EXPECT_FALSE(h1.Empty());
	EXPECT_TRUE(h2.Empty());

	//大堆
	heap<int,Greater<int>> h3(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int,Greater<int>> h4;//测试用例

	EXPECT_FALSE(h3.Empty());
	EXPECT_TRUE(h4.Empty());
}
//测试Top函数
TEST(HeapTestCase, TopCase)
{
	int arr1[] = { 12, 6, 8, 3, 9, 15 };//测试用例1
	heap<int> h1(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int> h2;//测试用例2

	EXPECT_EQ(h1.Top(), 3);
	EXPECT_EQ(h2.Top(), NULL);

	heap<int,Greater<int>> h3(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int,Greater<int>> h4;//测试用例2

	EXPECT_EQ(h3.Top(), 15);
	EXPECT_EQ(h4.Top(), NULL);
}
//测试Insert函数
TEST(HeapTestCase, InsertCase)
{
	int arr[] = { 12, 6, 8, 3, 9, 15 };
	int insert1 = 16;
	int insert2 = 1;
	int smallRes1[] = { 3, 6, 8, 12, 9, 15, 16 };
	int smallRes2[] = { 1, 6, 3, 12, 9, 15, 8 };
	int greaterRes1[] = { 15, 9, 12, 3, 6, 8, 1 };
	int greaterRes2[] = { 16, 9, 15, 3, 6, 8, 12 };


	//小堆
	heap<int> h1(arr, sizeof(arr) / sizeof(arr));
	h1.Insert(insert1);
	for (size_t index = 0; index < sizeof(arr) / sizeof(arr[0]); ++index)
	{
		ASSERT_EQ(h1._heap[index], smallRes1[index]);
	}
	heap<int> h2(arr, sizeof(arr) / sizeof(arr));
	h2.Insert(insert2);
	for (size_t index = 0; index < sizeof(arr) / sizeof(arr[0]); ++index)
	{
		ASSERT_EQ(h2._heap[index], smallRes2[index]);
	}

	//大堆
	heap<int, Greater<int> >h3(arr, sizeof(arr) / sizeof(arr[0]));
	h3.Insert(insert1);
	for (size_t index = 0; index < sizeof(arr) / sizeof(arr[0]); ++index)
	{
		ASSERT_EQ(h1._heap[index], greaterRes2[index]);
	}
	heap<int> h4(arr, sizeof(arr) / sizeof(arr));
	h2.Insert(insert2);
	for (size_t index = 0; index < sizeof(arr) / sizeof(arr[0]); ++index)
	{
		ASSERT_EQ(h2._heap[index], greaterRes1[index]);
	}

}
//Remove测试
TEST(HeapTestCase, RemoveCase)
{
	int arr[] = { 12, 6, 8, 3, 9, 15 };//测试用例1
	int smallRes[] = { 6, 9, 8, 12, 15 };
	int greaterRes[] = { 12, 9, 8, 3, 6 };
	heap<int>h1(arr, sizeof(arr) / sizeof(arr[0]));
	h1.Remove();
	for (size_t index = 0; index < sizeof(arr) / sizeof(arr[0]); ++index)
	{
		ASSERT_EQ(h1._heap[index], smallRes[index]);
	}
	heap<int,Greater<int> >h2(arr, sizeof(arr) / sizeof(arr[0]));
	h1.Remove();
	for (size_t index = 0; index < sizeof(arr) / sizeof(arr[0]); ++index)
	{
		ASSERT_EQ(h2._heap[index], greaterRes[index]);
	}

	heap<int>h3();//测试用例2
	
	ASSERT_DEATH(h1.Remove(),"");//死亡测试？？
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	int a = RUN_ALL_TESTS();
	getchar();
	return  a;
}


/*
void funtest2()//带模板参数的大小堆测试
{
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
	heap<int> h1(array, sizeof(array) / sizeof(array[0]));//小堆
	heap<int, Greater<int> > h2(array, sizeof(array) / sizeof(array[0]));//大堆
}
int main()
{
	//funtest1();
	funtest2();
	getchar();
	return 0;
}*/


