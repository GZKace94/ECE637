#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Htables.h"
#include "JPEGdefs.h"


/***************************************************/
/*  Function declarations                          */
/***************************************************/


int BitSize(int value) {
	value = abs(value);
	int m = 0;
	while (value != 0) {
		value = value / 2;
		m = m + 1;
	}
	return m;
}

void VLI_encode(int bitsz, int value, char *block_code) {
	char bcode[13] = {'\0'};
	if (value < 0) {
		value = abs(value) ^ 2147483647;
	}
	for (int i = bitsz - 1; i >=0 ;  i--) {
		if (value % 2 == 1) {
			bcode[i] = '1';
		}
		else {
			bcode[i] = '0';
		}
		value = value >> 1;
	}
	printf("%s\n", bcode);
	strcat(block_code, bcode);
}

void ZigZag(int **img, int y, int x, int *zigline) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			zigline[Zig[i][j]] = img[y + i][x + j];
		}
}

void DC_encode(int dc_value, int prev_value, char *block_code) {
	int DIFF = dc_value - prev_value;
	int bitsz = BitSize(DIFF);
	strcat(block_code, dcHuffman.code[bitsz]);
	VLI_encode(bitsz, DIFF, block_code);
}

void AC_encode(int *zigzag, char *block_code) {

}

