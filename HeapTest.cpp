
#include"heap.h"
#include"gtest/gtest.h"

//����С�ѵĹ��캯��
TEST(HeapTestCase, SmallHeapConstruct)
{
	int arr1[] = { 12, 6, 8, 3, 9, 15 };//��������1
	int arr2[] = {0 ,0, 0, 0, 0, 0};//��������2
	int arr3[3] = {};//��������3
	int smallHeap[] = { 3, 6, 8, 12, 9, 15 };//С�Ѳ��Խ��---��������1
	
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
//���Դ�ѵĹ��캯��
TEST(HeapTestCase, GreaterHeapConstruct)
{
	int arr1[] = { 12, 6, 8, 3, 9, 15 };//��������1
	int arr2[] = { 0, 0, 0, 0, 0, 0 };//��������2
	int arr3[3] = {};//��������3
	int greaterHeap[] = { 15, 9, 12, 3, 6, 8};//��Ѳ��Խ��---��������1

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
//����Size����
TEST(HeapTestCase, SizeTest)
{
	int arr1[] = { 12, 6, 8, 3, 9, 15 };//��������1
	int arr2[] = { 1 };//��������2

	//С��
	heap<int> h1(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int> h2(arr2, sizeof(arr2) / sizeof(arr2));
	heap<int> h3;//��������3

	EXPECT_EQ(h1.Size(), 6);
	EXPECT_EQ(h2.Size(), 1);
	EXPECT_EQ(h3.Size(), 0);

	//���
	heap<int,Greater<int>> h4(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int,Greater<int>> h5(arr2, sizeof(arr2) / sizeof(arr2));
	heap<int,Greater<int>> h6;//��������3

	EXPECT_EQ(h4.Size(), 6);
	EXPECT_EQ(h5.Size(), 1);
	EXPECT_EQ(h6.Size(), 0);
}
//����empty����
TEST(HeapTestCase, EmptyTest)
{
	int arr1[] = { 12, 6, 8, 3, 9, 15 };//��������1

	//С��
	heap<int> h1(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int> h2;//��������2

	EXPECT_FALSE(h1.Empty());
	EXPECT_TRUE(h2.Empty());

	//���
	heap<int,Greater<int>> h3(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int,Greater<int>> h4;//��������

	EXPECT_FALSE(h3.Empty());
	EXPECT_TRUE(h4.Empty());
}
//����Top����
TEST(HeapTestCase, TopCase)
{
	int arr1[] = { 12, 6, 8, 3, 9, 15 };//��������1
	heap<int> h1(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int> h2;//��������2

	EXPECT_EQ(h1.Top(), 3);
	EXPECT_EQ(h2.Top(), NULL);

	heap<int,Greater<int>> h3(arr1, sizeof(arr1) / sizeof(arr1));
	heap<int,Greater<int>> h4;//��������2

	EXPECT_EQ(h3.Top(), 15);
	EXPECT_EQ(h4.Top(), NULL);
}
//����Insert����
TEST(HeapTestCase, InsertCase)
{
	int arr[] = { 12, 6, 8, 3, 9, 15 };
	int insert1 = 16;
	int insert2 = 1;
	int smallRes1[] = { 3, 6, 8, 12, 9, 15, 16 };
	int smallRes2[] = { 1, 6, 3, 12, 9, 15, 8 };
	int greaterRes1[] = { 15, 9, 12, 3, 6, 8, 1 };
	int greaterRes2[] = { 16, 9, 15, 3, 6, 8, 12 };


	//С��
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

	//���
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
//Remove����
TEST(HeapTestCase, RemoveCase)
{
	int arr[] = { 12, 6, 8, 3, 9, 15 };//��������1
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

	heap<int>h3();//��������2
	
	ASSERT_DEATH(h1.Remove(),"");//�������ԣ���
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	int a = RUN_ALL_TESTS();
	getchar();
	return  a;
}


/*
void funtest2()//��ģ������Ĵ�С�Ѳ���
{
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
	heap<int> h1(array, sizeof(array) / sizeof(array[0]));//С��
	heap<int, Greater<int> > h2(array, sizeof(array) / sizeof(array[0]));//���
}
int main()
{
	//funtest1();
	funtest2();
	getchar();
	return 0;
}*/


