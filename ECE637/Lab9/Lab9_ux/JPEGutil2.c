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
	int idx = 1;
	int zerocnt = 0;
	int bitsize;
	while (idx < 64) {
		if (zigzag[idx] == 0) {
			zerocnt++;
		}else {
			for (; zerocnt > 15; zerocnt -= 16) {
				strcat(block_code, acHuffman.code[15][0]);
			}
			bitsize = BitSize(zigzag[idx]);
			strcat(block_code, acHuffman.code[zerocnt][bitsize]);
			VLI_encode(bitsize, zigzag[idx], block_code);
			zerocnt = 0;
		}
		idx++;
	}
	if (zerocnt) {
		strcat(block_code, acHuffman.code[0][0]);
	}
}



void Block_encode(int prev_value, int *zigzag, char *block_code) {
	
	DC_encode(zigzag[0], prev_value, block_code);
	AC_encode(zigzag, block_code);
	printf("DC_AC_code: %s\n", block_code);
	
}

int Convert_encode(char *block_code, unsigned char *byte_code) {
	
	int len = strlen(block_code);
	int bytes = len / 8;
	
	int idx;
	int i, j;
	idx = 0;
	for (i = 0; i < bytes; i++) {
			for (j = 0; j < 8; j++) {
				byte_code[idx] <<= 1;

				if (block_code[8 * i + j] == '1') {
					byte_code[idx] ++;
				}
			}

			if (byte_code[idx] == 0xff) {
				idx++; 
				byte_code[idx] = 0x00;
				bytes++;
			}
			idx++;

	}
	strcpy(block_code, block_code + (len / 8) * 8);

	return bytes;

}

unsigned char Zero_pad(char *block_code) {
	int len = strlen(block_code);
	unsigned char value = 0;
	for (int i = 0; i < len; i++) {
		value <<= 1;
		if (block_code[i] = '1') {
			value ++;
		}
	}
	value <<= (8 - len);

	return value;
}