#ifndef COMPRESS_H
#include"HuffTree.h"
typedef unsigned char BYTE;
Status Compression(HuffTable HT, int n, char *from, char *todat);
Status GetCode(HuffTable HT, int n, char &e, HuffTableNode &Node);
Status GetCode(HuffTable HT, int n, char &e, HuffTableNode &Node)
{
	int i;
	for (i = 1; i <= n; i++) {
		if (HT[i].value == e) {
			Node = HT[i];
			return OK;
		}//if
	}//for
	return ERROR;
}//GetCode
Status Compression(HuffTable HT, int n, char *from, char *todat)//压缩
{
	FILE *fpr = fopen(from, "r");
	if (fpr == NULL) exit(OVERFLOW);
	FILE *fpw = fopen(todat, "wb");
	if (fpw == NULL) exit(OVERFLOW);
	BYTE wf = 0x00; 
	int iw = 0;
	bool tag = 0;
	while (!feof(fpr)) {
		tag = 0;
		char exp; 
		BYTE temp;
		HuffTableNode tem; 
		unsigned int j = 0;
		exp = fgetc(fpr);
		GetCode(HT, n, exp, tem);
		while (j < tem.length) {
			if (tem.Huffcode[j] == '1') {
				temp = 0x01;
				temp <<= 7 - iw;//左移
				wf |= temp;//或操作
			}//if
			j++;
			if (iw == 7) {
				fwrite(&wf, sizeof(BYTE), 1, fpw);
				wf = 0x00; 
				iw = 0;
				tag = 1;
			}//if
			else
				iw++;
		}//while
	}//while
	if (tag == 0) {
		fwrite(&wf, sizeof(BYTE), 1, fpw);//写入文件
	}//if
	fclose(fpr); fclose(fpw);
	return OK;
}//Compression
#endif // !COMPRESS_H
#pragma once
