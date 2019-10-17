#ifndef DECOMPRESS_H
#include"HuffTree.h"
typedef unsigned char BYTE;
Status Decompress(HuffTree HT, int n, char *fromdat, char *tofile, int all_char)
{
	FILE *fpr = fopen(fromdat, "rb");
	if (fpr == NULL) exit(OVERFLOW);
	FILE *fpw = fopen(tofile, "w");
	if (fpw == NULL) exit(OVERFLOW);
	BYTE temp, jud = 0x7F, clear;
	int ind = 0;
	int m = 2 * n - 1;
	int all = 0;
	char wf = 0;
	while (!feof(fpr)) {
		fread(&temp, sizeof(BYTE), 1, fpr);
		ind = 0;
		while (ind <= 7) {
			jud = 0x7F;
			jud >>= ind;        //把要取的位的前面的位清0
			clear = jud;
			jud |= temp;
			jud >>= 7 - ind;
			temp &= clear;      //把取下来过的位清0
			if (jud == 0x01) 
				m = HT[m].rchild;
			else if(jud == 0x00)
				m = HT[m].lchild;
			else return ERROR;
			if (HT[m].lchild == 0 && HT[m].rchild == 0) {
				wf = HT[m].value;
				fputc(wf, fpw);
				if (++all >= all_char) return OK;
				wf = 0;
				m = 2 * n - 1;
			}//if
			ind++;
		}//while
	}//while
	fclose(fpw);
	fclose(fpr);
	return OK;
}//Decompress
#endif // !DECOMPRESS_H
#pragma once
