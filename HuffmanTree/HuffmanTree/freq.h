#ifndef FREQ_H
#define FREQ_H
#include<cstdio>
#include<cstdlib>
#include"STATUS.h"
using namespace std;
#define NUMLETTER 128
typedef struct {
	char value;			//字符
	unsigned int freq;	//频率
}CharFreq, *PtrFreq;
Status InitFreq(PtrFreq &q, int n);//初始化创建q，并将成员freq置为0
Status CountFrequency(char *filename, PtrFreq &q, int &ch_num);//统计字符的频率，ch_num是文件中字符的总数
Status ExportFreq(PtrFreq &q, PtrFreq &Exq, int n);//导出有效的字符-权重（）
Status CountCharacter(char *filename, int &n);//计算文档中所有字符种类



Status InitFreq(PtrFreq &q, int n)
{
	q = (PtrFreq)malloc(n * sizeof(CharFreq));
	if (!q) exit(OVERFLOW);
	int ind;
	for (ind = 0; ind < n; ind++) {
		q[ind].freq = 0;
	}//for
	return OK;
}//InitFreq
Status CountFrequency(char *filename, PtrFreq &q, int &ch_num)
{
	FILE *fptr = fopen(filename, "r");
	if (fptr == NULL) exit(OVERFLOW);
	InitFreq(q, NUMLETTER);
	int cou = 0;
	while (!feof(fptr)) {
		int onechar = fgetc(fptr);
		if (onechar != EOF) {
			if (onechar > NUMLETTER) exit(OVERFLOW);
			cou++;
			q[onechar].value = (char)onechar; 
			q[onechar].freq++;
		}//if
	}//while
	fclose(fptr);
	ch_num = cou;
	return OK;
}//CountFrequency
Status ExportFreq(PtrFreq &q, PtrFreq &Exq, int n)
{
	int i, j = 0;
	InitFreq(Exq, n);
	for (i = 0; i < NUMLETTER && j < n; i++) {
		if (q[i].freq != 0) {
			Exq[j].freq = q[i].freq;
			Exq[j].value = q[i].value;
			j++;
		}//if
	}//for
	free(q);
	return OK;
}//ExportFreq
Status CountCharacter(char *filename, int &n)
{
	int i, one, cou = 0;
	FILE *fptr = fopen(filename, "r");
	if (fptr == NULL) exit(OVERFLOW);
	bool ch[NUMLETTER];
	for (i = 0; i < NUMLETTER; i++) ch[i] = 0;
	while (!feof(fptr)) {
		one = fgetc(fptr);
		if (one != EOF)
			ch[one] = 1;
	}//while
	fclose(fptr);
	for (i = 0; i < NUMLETTER; i++) {
		if (ch[i] == 1)
			cou++;
	}//for
	n = cou;
	return OK;
}//CountCharacter
#endif // FREQ_H

