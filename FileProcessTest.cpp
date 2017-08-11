#include"gtest/gtest.h"
#include"FileProcess.h"
#include<stdio.h>

TEST(FileProcessTestCase, ConstructTest)
{
	FileProcess fp;
	for (int idx = 0; idx < 256; ++idx)
	{
		FileInfo* _f = fp.member();
		ASSERT_EQ(_f[idx]._ch, (char)idx);
	}
}

TEST(FileProcessTestCase, FileProcessTest)
{
	FileProcess fp;
	string PathName = "1.txt";//ABBBCCCCCDDDDDDDD
	fp.CreateFileProcess(PathName);
	//压缩文件1.hzp ".txt\n4\n  A,1\n  B,3\n C,5\n  D,7\n   ox96 DF 3F 00 "
	FILE* fOut;
	fopen_s(&fOut, "1.hzp", "rb");
	string PosixName;
	fp.ReadLine(fOut,PosixName);
	ASSERT_STREQ(PosixName.c_str(), ".txt");

	string strLineCount;//叶子节点信息的行数
	fp.ReadLine(fOut, strLineCount);//现在已经获取到了行数的信息
	size_t LineCount = atoi(strLineCount.c_str());//将字符转化为整数
	ASSERT_EQ(LineCount, 4);

	string strCode;
	fp.ReadLine(fOut, strCode);
	ASSERT_EQ(strCode, "A,1");
	strCode = "";
	fp.ReadLine(fOut, strCode);
	ASSERT_EQ(strCode, "B,3");
	strCode = "";
	fp.ReadLine(fOut, strCode);
	ASSERT_EQ(strCode, "C,5");
	strCode = "";
	fp.ReadLine(fOut, strCode);
	ASSERT_EQ(strCode, "D,7");
	strCode = "";

	 //10010110110111111111110000000
	fp.ReadLine(fOut, strCode);
	ASSERT_EQ(strCode, "10010110110111111111110000000");//测试方法不正确 ，但显示的结果是正确的
}

int  main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	int a = RUN_ALL_TESTS();
	getchar();
	return a;
}

