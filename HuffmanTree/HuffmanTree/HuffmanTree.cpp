// HuffmanTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
	CountCharacter(filename, n);//所有字符种类
	CountFrequency(filename, q, all_ch);//所有字符频率
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

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
