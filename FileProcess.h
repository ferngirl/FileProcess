//�ļ�ѹ��
//���ȴ���һ�����飬��СΪ256������ΪFileInfo,Ȼ���ʼ����������е���Ϣ����ʼ���ַ���Ϣ��ASCII��
//���ļ��е����ݶ�ȡһ���Զ��������У����ø�����ͳ���ļ��������ַ����ֵĴ�����

#include<stdio.h>
#include<string>
#include <algorithm>
#include"Huffman.h"
#include<iostream>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
struct FileInfo
{
	FileInfo(long long appearCount = 0)
	:_appearCount(appearCount)
	{}

	char _ch;//�ַ�
	long long _appearCount;//�ַ����ֵĴ���
	string _strCode;//�ַ���Ӧ���ַ�����
};

bool operator<(const FileInfo& pLeft, const FileInfo& pRight)
{
	return pLeft._appearCount < pRight._appearCount;
}

FileInfo operator+(const FileInfo& pLeft, const FileInfo& pRight)
{
	FileInfo temp;
	temp._appearCount = pLeft._appearCount + pRight._appearCount;//
	return temp;
}

class FileProcess
{
public:
	//���캯��
	FileProcess()
	{
		for (size_t idx = 0; idx< 256; ++idx)//��ʼ���ַ���Ϣ
			_fileInfo[idx]._ch = idx;//��idx��Ϊ�ַ���ASCII����_ch�У���ʾ�ļ���(��������)���ܳ��ֵ�256���ַ�,
	}                                //����ASCIIֵֻ��126��������126~156��δ֪�ַ���_ch��δ֪��

	void CreateFileProcess(string strPathName)//�ļ�ѹ��
	{
		size_t strcount = 0;

		char filebuff[1024];//?????
		FILE *fIn;
		fopen_s(&fIn, strPathName.c_str(), "rb");
		if (fIn == NULL)
		{
			cout << "�ļ���ʧ��" << endl;
			return;
		}
		//���ļ��ж�ȡ�ַ���ͳ��ÿ���ַ����ֵĴ��������������_fileInfo��
		while (1)//
		{
			strcount = fread(filebuff, 1, 1024, fIn);//���ļ��ж�ȡ�ַ���������filebuff��
			if (strcount == 0)
				break;;//û�д��ļ��ж����ַ�
			//��������filebuff�е��ַ�����ʼ��_fileInfo[256]�е�_appearCount(�ַ����ִ���)����Ϣ
			for (size_t idx = 0; idx<strcount; ++idx)
				_fileInfo[filebuff[idx]]._appearCount++;
		}

		//�����ַ����ֵĴ�������huffman��
		HuffmanTree<FileInfo> ht(_fileInfo, 256, FileInfo(0));//????

		//����huffman���õ�huffman����
		GetHuffmanCode(ht.GetRoot());

		//�������滻�ַ�
		char readBuff[1024];
		char writeBuff[1024];
		size_t writesize = 0;
		char value = 0;
		int pos = 0;

		//memset(writeBuff,0,1024);
		fseek(fIn, 0, SEEK_SET);//int fseek ( FILE * stream, long int offset, int origin );�����ļ�ָ��fInָ����ʼ��λ��
		FILE* fOut;
		fopen_s(&fOut, "1.hzp", "wb");
		if (fOut == NULL)
			cout << "�ļ���ʧ��" << endl;


		size_t linecount = 0;
		string strCode;
		char szAppearCount[32];//�����ֵĴ�������ת�ַ��ͺ�洢��������

		string FileHead = GetFilePostFix(strPathName);//��ȡ�ļ���׺".txt"

		for (size_t idx = 0; idx<256; ++idx)//����ѹ����Ϣ�����ַ������ִ�������Ϣ
		{
			if (_fileInfo[idx]._appearCount != 0)
			{
				strCode += _fileInfo[idx]._ch;
				strCode += ',';
				_itoa_s(_fileInfo[idx]._appearCount, szAppearCount, 10);//char *  itoa ( int value, char * str, int base )����ת�ַ���,base��ʾ10����
				strCode += szAppearCount;
				strCode += '\n';
				linecount++;
			}
		}

		FileHead += '\n';//�ȱ����׺��Ϣ
		_itoa_s(linecount, szAppearCount, 10);//����Ϣ�ĸ�����������ת��Ϊ�ַ�������
		FileHead += szAppearCount;
		FileHead += '\n';
		FileHead += strCode;//����ѹ����Ҷ�ӽڵ����Ϣ

		fwrite(FileHead.c_str(), 1, FileHead.length(), fOut);//�����е���Ϣ(string����)ת��Ϊchar* ���ͱ���д��ѹ���ļ���ȥ

		//��ѹ����ı���д���ļ���ȥ
		while (true)
		{
			size_t readsize = fread(readBuff, 1, 1024, fIn);//????
			if (readsize == 0)
				break;
			for (size_t idx = 0; idx<readsize; ++idx)
			{
				string& strCode = _fileInfo[readBuff[idx]]._strCode;
				for (size_t i = 0; i<strCode.length(); ++i)
				{
					value = value << 1;
					if (strCode[i] == '1')//��value�Ķ���������ʾ���ǽ�Ҫ�滻�ı���
						value |= 1;
					pos++;
					if (pos == 8)//��־λ����8λ������֮�����ǽ�value��ֵд�����ǵ�1.hzp�ļ���
					{
						writeBuff[writesize++] = value;
						if (writesize == 1024)
						{
							fwrite(writeBuff, 1, 1024, fOut);
							writesize = 0;
						}
						pos = 0;
						value = 0;
					}
				}
			}
		}

		if (pos)
		{
			value << (8 - pos);
			writeBuff[writesize++] = value;
			//fwrite(writeBuff,1,1024,fOut);
		}

		if (writesize)
		{
			fwrite(writeBuff, 1, writesize, fOut);///????�ܽ���ֵ�����
		}

		fclose(fIn);
		fclose(fOut);
	}


	void unProcessFile(string strPathName)//�ļ���ѹ��
	{
		//��ȡѹ���ļ������ݣ���ԭhuffman��
		//�Ӹ��ڵ㿪ʼ���ң�����ѹ���ı��룬����Ϊ1�������������ң�����Ϊ0�������������ң�ֱ���ҵ�Ҷ�ӽڵ㣬Ҷ�ӽڵ��Ӧ�ַ���Ϊ��ѹ���ַ�

		FILE* fIn;
		fopen_s(&fIn, strPathName.c_str(), "rb");
		if (fIn == NULL)
			cout << "�ļ���ʧ��" << endl;

		string FilePosix;//�ļ���׺

		ReadLine(fIn, FilePosix);//��ȡѹ���ļ�һ�е���Ϣ,�����Ѿ���ȡ���ļ��ĺ�׺��Ϣ

		string strLineCount;//Ҷ�ӽڵ���Ϣ������

		ReadLine(fIn, strLineCount);//�����Ѿ���ȡ������������Ϣ
		size_t LineCount = atoi(strLineCount.c_str());//���ַ�ת��Ϊ����

		string strCode;

		for (size_t idx = 0; idx<LineCount; ++idx)//��ԭ_fileInfo[]����
		{
			ReadLine(fIn, strCode);
			_fileInfo[strCode[0]]._appearCount = atoi(strCode.substr(2).c_str());
			strCode = "";
		}
		//����ѹ���ļ�����Ϣ����ԭ������//?????
		HuffmanTree<FileInfo> ht(_fileInfo, sizeof(_fileInfo) / sizeof(_fileInfo[0]), FileInfo(0));

		//���ݻ�ԭ�Ķ��������Լ�ѹ�����룬���ǿ����ҵ���Ӧ���ַ���Ϣ
		Node<FileInfo>* pRoot = ht.GetRoot();
		Node<FileInfo>* pCur = ht.GetRoot();//���ڵ�
		string PathAndName;
		char pWriteBuff[1024];
		char pReadBuff[1024];
		size_t readsize = 0;
		size_t writesize = 0;
		int pos = 7;
		size_t filesize = pCur->_weight._appearCount;//ѹ���ļ��Ĵ�С���Ǹ��ڵ��Ȩֵ

		//��ȡ��ѹ�ļ���·�������֣���ѹ�ļ��ĺ�׺Ӧ����fIn�ļ��ĵ�һ����Ϣ�����ļ���·���ַ�Ϊ����·�������·��
		//�����ɸ�����strPathName��ѹ���ļ������ݾ�����
		size_t last = strPathName.find_last_of('.');
		PathAndName += strPathName.substr(0, last);
		PathAndName += FilePosix;

		FILE* fOut;
		fopen_s(&fOut, PathAndName.c_str(), "wb");//��ȡ·��������

		while (true)
		{
			readsize = fread(pReadBuff, 1, 1024, fIn);//��ȡѹ��
			if (readsize == 0)
				break;
			//cout<<readsize<<endl;
			for (size_t idx = 0; idx<readsize;)
			{

				if (pReadBuff[idx] & (1 << pos))//��һ���ֽڵĶ��������λ��1�������Һ���
					pCur = pCur->_pRight;
				else
					pCur = pCur->_pLeft;//������0����������

				if (pCur&&pCur->_pLeft == NULL && pCur->_pRight == NULL)
				{

					pWriteBuff[writesize++] = pCur->_weight._ch;
					if (writesize == 1024)
					{
						fwrite(pWriteBuff, 1, 1024, fOut);
						writesize = 0;
					}
					filesize--;
					if (filesize == 0)//ѹ���ļ��������ַ����ѽ�ѹ��
						break;

					pCur = pRoot;//pcur���˵����ڵ��λ�ã���ʼ������һ���ַ�
				}
				pos--;//���Ҵθ߱���λ
				if (pos < 0)//һ���ֽ��Ѿ���ѹ��
				{
					idx++;
					pos = 7;
				}
			}
		}

		if (writesize)
		{
			fwrite(pWriteBuff, 1, writesize, fOut);
		}
		fclose(fIn);
		fclose(fOut);
	}
	FileInfo* member()
	{
		return _fileInfo;
	}

//private:
public:
	void GetHuffmanCode(Node<FileInfo>* pRoot)// �õ������huffman���벢��ת
	{
		if (pRoot == NULL)
			return;
		string& strCode = _fileInfo[pRoot->_weight._ch]._strCode;//???
		Node<FileInfo>* pCur = pRoot;
		Node<FileInfo>* pParent = pRoot;

		if (pCur->_pLeft == NULL && pCur->_pRight == NULL)//·��ֻ��ʾ��һ����֧
		{
			pParent = pCur->_pParent;
			while (pParent)//û�л��˵����ڵ�
			{
				if (pParent->_pLeft == pCur)
					strCode += '0';
				else
					strCode += '1';
				pCur = pParent;
				pParent = pCur->_pParent;
			}
		}
		if (pParent == NULL)//�жϸ�Ҷ�ӽڵ�ı����Ƿ���꣨�����������pParentΪNULL�����Կ�ʼ��ʱ���pParent��ֵΪpRoot��������NULL��Ϊ���õ�һ�β���ȥ������û�У����ܷ�ת����ı���
			reverse(strCode.begin(), strCode.end());//�������huffman����ת��Ϊ����

		GetHuffmanCode(pRoot->_pLeft);
		GetHuffmanCode(pRoot->_pRight);
	}

	//��ȡ�ļ���׺
	string GetFilePostFix(const string& strPathName)
	{
		size_t pos = strPathName.find_last_of('.');
		return strPathName.substr(pos, strPathName.length() - pos);//string substr ( size_t pos = 0, size_t n = npos ) const;
	}

	//ÿ�δ�ѹ���ļ��ж�ȡһ�е���Ϣ
	void ReadLine(FILE*& fIn, string& strCode)
	{
		if (feof(fIn))//�ж��ļ��Ƿ񵽴��β���������ļ���β���򷵻ط�0
			return;
		char ch = getc(fIn);
		while (ch != '\n')
		{
			strCode += ch;
			if (feof(fIn))
				return;
			ch = getc(fIn);
		}
	}


private:
	FileInfo _fileInfo[256];//��Ϊ�ַ�charΪһ���ֽڣ�8������λ��2^8=256�����Կ��ܳ��ֵ��ַ���256��
};
