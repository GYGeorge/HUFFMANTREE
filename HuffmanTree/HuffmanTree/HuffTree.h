#ifndef HUFFTREE_H
#define HUFFTREE_H
#include<cstdio>
#include<cstdlib>
#include<string.h>
#include"STATUS.h"
#include"freq.h"
using namespace std;
typedef struct {//huffman��
	 char value;			//������ַ�
	 int weight;			//Ƶ��/Ȩ��
	 int parent, lchild, rchild;
}HTNode,*HuffTree;
typedef struct {//���������n+1��0�ŵ�Ԫδ��
	char		  value;		//������ַ�
	unsigned int  freq, length;	//�ַ����ֵ�Ƶ�ʣ�����ĳ���
	char		  *Huffcode;	//����
}HuffTableNode, *HuffTable;
Status Select(HuffTree &HT, int n, int &s);//��HT[1..i-1]����parentΪ0��weight��С���������s1,s2
Status CreatHuffTree(HuffTree &HT, PtrFreq Exq, int n);//������������
Status HuffCoding(HuffTree &HT, HuffTable &Table, int n);//���������������
Status ExportHuffTable(PtrFreq Exq, HuffTable &Table, int n);//���������,���������ĳ���



Status Select(HuffTree &HT, int n, int &s)
{
	HuffTree p = HT;
	int i, min = 0l;
	for (i = 1; i <= n; i++) {
		if (p[i].parent == 0) {
			min = i;
			break;
		}
	}//for
	if (i == n && min == 0) return ERROR;
	for (i = 1; i <= n; i++) {
		if (p[i].parent == 0) {
			if (p[i].weight < p[min].weight)
				min = i;
		}//if
	}//for
	s = min;
	return OK;
}//Select
Status CreatHuffTree(HuffTree &HT, PtrFreq Exq, int n)
{//�ַ�����n
	int i, AllNode, s1 = 0, s2 = 0;
	HuffTree p;
	if (n <= 1) return ERROR;
	AllNode = 2 * n - 1;//Ҷ�ӽڵ�+��Ҷ�ӽڵ�
	HT = (HuffTree)malloc((AllNode + 1) * sizeof(HTNode));//0�ŵ�Ԫδ��
	if (!HT) exit(OVERFLOW);
	p = HT;
	for (i = 1; i <= n; i++) {
		p[i].weight = Exq[i-1].freq; p[i].parent = 0; p[i].lchild = 0; p[i].rchild = 0;
		p[i].value = Exq[i - 1].value;
 	}//for
	for (; i <= AllNode; i++) {
		p[i].weight = 0; p[i].parent = 0; p[i].lchild = 0; p[i].rchild = 0;
		p[i].value = 0;
	}//for
	for (i = n + 1; i <= AllNode; i++) {
		Select(HT, i - 1, s1); HT[s1].parent = i;
		Select(HT, i - 1, s2); HT[s2].parent = i;
		HT[i].lchild = s1;     HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}//for
	return OK;
}//CreatHuffTree
Status HuffCoding(HuffTree &HT, HuffTable &Table, int n)
{
	Table = (HuffTable)malloc((n + 1) * sizeof(HuffTableNode));			//0�ŵ�Ԫδ��
	if (!Table)exit(OVERFLOW);
	int i, start, child, father;
	char *cd;															//�����ռ�
	cd = (char*)malloc(n * sizeof(char));
	if (!cd) exit(OVERFLOW);
	cd[n - 1] = 0;													//�������λ��
	for (i = 1; i <= n; i++) {
		start = n - 1;
		for (child = i, father = HT[i].parent; father != 0; child = father, father = HT[father].parent) {
																			//��Ҷ�ӽ�������ߵ�ͷ
			if (HT[father].lchild == child) cd[--start] = '0';				//�Ӻ���ǰ���룬��Ϊ0��Ϊ1
			else cd[--start] = '1';
		}//for
		Table[i].Huffcode = (char*)malloc((n - start) * sizeof(char));		//���ݱ��볤�ȷ���洢�ռ�
		strcpy(Table[i].Huffcode, &cd[start]);								//�����ռ��һ����ʼ�����ַ��ĵ�ַ
	}//for
	free(cd);
	return OK;
}//HuffCoding
Status ExportHuffTable(PtrFreq Exq, HuffTable &Table, int n)
{
	int i;
	for (i = 1; i <= n; i++) {
		Table[i].value = Exq[i - 1].value;
		Table[i].freq = Exq[i - 1].freq;
	}//for
	free(Exq);
	int cou = 0, j = 0;
	for (i = 1; i <= n; i++) {//������볤��
		while (Table[i].Huffcode[j] != '\0') {
			cou++; j++;
		}//while
		Table[i].length = cou;
		j = 0; cou = 0;
	}//for
	return OK;
}//ExportFreq

#endif // !HUFFTREE_H
