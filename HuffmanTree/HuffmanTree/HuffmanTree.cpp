// HuffmanTree.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include "pch.h"
#include <iostream>
#include"freq.h"
#include"HuffTree.h"
#include"compress.h"
#include"decompress.h"
using namespace std;
int main()
{
	int i;
	HuffTree HT;
	PtrFreq q, Exq;
	HuffTable Table;
	int n, all_ch;
	char filename[] = "text.txt";
	CountCharacter(filename, n);//�����ַ�����
	CountFrequency(filename, q, all_ch);//�����ַ�Ƶ��
	ExportFreq(q, Exq, n);
	CreatHuffTree(HT, Exq, n);
	HuffCoding(HT, Table, n);
	ExportHuffTable(Exq, Table, n);

	char writefile[] = "table.txt";
	FILE *fptr = fopen(writefile, "w");
	for (i = 1; i <= n; i++)
	{
		fprintf(fptr, "%c - %d - ", Table[i].value, Table[i].freq);
		fprintf(fptr, "%s\n", Table[i].Huffcode);
	}//for
	cout << all_ch << endl;
	char filedat[] = "compress_text1.dat";
	Compression(Table, n, filename, filedat);
	char newfile[] = "newfile.txt";
	Decompress(HT, n, filedat, newfile, all_ch);
	fclose(fptr);
	free(HT);
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ������ʾ:
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
