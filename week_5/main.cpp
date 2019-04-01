#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned char BYTE;

BYTE ip[64] = { 0, };
BYTE IP[64] = { 58,50,42,34,26,18,10,2,
				60,52,44,36,28,20,12,4,
				62,54,46,38,30,22,14,6,
				64,56,48,40,32,24,16,8,
				57,49,41,33,25,17,9,1,
				59,51,43,35,27,19,11,3,
				61,53,45,37,29,21,13,5,
				63,55,47,39,31,23,15,7 };

BYTE IP_1[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
				39, 7, 47, 15, 55, 23, 63, 31,
				 38, 6, 46, 14, 54, 22, 62, 30,
				 37, 5, 45, 13, 53, 21, 61, 29,
				 36, 4, 44, 12, 52, 20, 60, 28,
				 35, 3, 43, 11, 51, 19, 59, 27,
				 34, 2, 42, 10, 50, 18, 58, 26,
				33, 1, 41, 9, 49, 17, 57, 25 };

BYTE pcStatic[56] = { 57,49,41,33,25,17,9,
				1,58,50,42,34,26,18,
				10,2,59,51,43,35,27,
				19,11,3,60,52,44,36,
				63,55,47,39,31,23,15,
				7,62,54,46,38,30,22,
				14,6,61,53,45,37,29,
				21,13,5,28,20,12,4 };

BYTE pc2Static[48] = { 14, 17, 11, 24, 1, 5,
						3, 28, 15, 6, 21, 10,
						23, 19, 12, 4, 26, 8,
						16, 7, 27, 20, 13, 2,
						41, 52, 31, 37, 47, 55,
						30, 40, 51, 45, 33, 48,
						44, 49, 39, 56, 34, 53,
						46, 42, 50, 36, 29, 32 };

BYTE mapExp[48] = { 32, 1, 2, 3, 4, 5,
						4, 5, 6, 7, 8, 9,
						8, 9, 10, 11, 12, 13,
						12, 13, 14, 15, 16, 17,
						16, 17, 18, 19, 20, 21,
						20, 21, 22, 23, 24, 25,
						24, 25, 26, 27, 28, 29,
						28, 29, 30, 31, 32, 1 };

int MAT_SBOX[8][4][16] = { 
			{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
			 {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
			 {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
			 {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 2, 14, 10, 0, 6, 13}},

			{{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
			 {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
			 {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
			 {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

			{{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
			 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
			 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
			 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

			{{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
			 {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
			 {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
			 {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},

			{{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
			 {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
			 {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
			 {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

			{{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
			 {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
			 {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
			 {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

			 {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
			 {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
			 {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
			 {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

			{{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
			 {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
			 {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
			 {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}} };

int MAT_PBOX[32] = { 16, 7, 20, 21, 29, 12, 28, 17,
		   1, 15, 23, 26, 5, 18, 31, 10,
		   2, 8, 24, 14, 32, 27, 3, 9,
		   19, 13, 30, 6, 22, 11, 4, 25 };

BYTE L[32] = { 0, };
BYTE R[32] = { 0, };
BYTE tempL[32] = { 0, };

BYTE result[64] = { 0, };
BYTE output[64] = { 0, };

BYTE extendR[48] = { 0, };
BYTE R_K_XOR[48] = { 0, };

BYTE pc1[56] = { 0, };
BYTE Ki[16][48] = { 0, };

BYTE sBoxResult[32] = {0, };
BYTE pBoxResult[32] = { 0, };

int keySchedule[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };


void reverse(BYTE *arr, int start, int end);
void shiftLeft(BYTE *arr, int d, int n);

void initialPermutation(BYTE *input, BYTE *output);

void twoByteChange(BYTE *input, BYTE *out);
void devideLR(BYTE *input, BYTE *L, BYTE *R);
void PC1(BYTE *key,BYTE *output);
void PC2(BYTE *input, BYTE *output);
void shiftAndGetAllKey(BYTE *key, BYTE (*output)[48]);

void extendArr(BYTE *arr, BYTE *exArr);
void XOR(BYTE *arr1, BYTE *arr2, BYTE *output);
void sBoxRotate(BYTE *arr, BYTE *output);
void pBox(BYTE *arr, BYTE * output);

void RtoL(BYTE *R, BYTE *tempL,BYTE *L);
void LPtoR(BYTE *L,BYTE *pBox, BYTE *R);



void printArr(BYTE *arr);
void printArr64_8(BYTE *arr);
void printArr_16(BYTE *arr);
void printArr_32(BYTE *arr);
void printArr48(BYTE *arr);
void printArr64(BYTE *arr);


void main() {
	BYTE input[16] = { 0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,0xF };
	BYTE key[16] = {0,0,0,9,4,8,4,7,3,5,2,2,5,5,0xC,0xC};
	int i;

	initialPermutation(input, ip);
	//printArr(ip);

	PC1(key, pc1);
	shiftAndGetAllKey(pc1, Ki);

	devideLR(ip, L, R);

	printf("L[0] :   ");
	printArr_16(L);
	printf("R[0] :   ");
	printArr_16(R);

	for (i = 0; i < 16; i++) {
		printf("\nRound %d\n",i+1); //수정

		extendArr(R, extendR);
		printf("E : ");
		printArr48(extendR);
		printf("KS : ");
		printArr48(Ki[i]); // for문으로 수정
		XOR(extendR, Ki[i], R_K_XOR); //수정
		printf("E xor KS : ");
		printArr48(R_K_XOR);

		sBoxRotate(R_K_XOR, sBoxResult);
		printf("Sbox : ");
		printArr_32(sBoxResult);

		pBox(sBoxResult, pBoxResult);
		printf("P : ");
		printArr_16(pBoxResult);

		RtoL(R, tempL, L);

		printf("L[%d] : ",i+1);
		printArr_16(L);
		printf("R[%d] : ",i+1);
		LPtoR(tempL, pBoxResult, R);
		printArr_16(R);
	}
	
	for (i = 0; i < 64; i++) {
		if (i < 32) result[i] = R[i];
		else result[i] = L[i - 32];
	}
	
	printf("LR[16] : ");
	printArr64_8(result);

	
	for (i = 0; i < 64; i++) {
		output[i] = result[IP_1[i]-1];
	}

	printf("output : ");
	printArr64_8(output);

	
	
}

void reverse(BYTE *arr, int start, int end) {
	BYTE temp;
	end = end - 1;
	while(start < end) {
		temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
		start++;
		end--;
	}
}
void shiftLeft(BYTE *arr, int d, int n) {
	reverse(arr, 0, d);
	reverse(arr, d, n);
	reverse(arr, 0, n);
}

void printArr(BYTE *arr) {
	int i, j;

	for (i = 0; i < 16; i++) {
		for (j = 0; j < 4; j++) {
			printf("%d", arr[i*4 + j]);
		}
		printf(" ");
	}
	printf("\n");
}
void printArr64_8(BYTE *arr) {
	int i, j;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			printf("%d", arr[i * 8 + j]);
		}
		printf(" ");
	}
	printf("\n");
}
void printArr_16(BYTE *arr) {
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 8 ; j++) {
			printf("%d", arr[i * 8 + j]);
		}
		printf(" ");
	}
	printf("\n");
}
void printArr_32(BYTE *arr) {
	int i, j;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 4; j++) {
			printf("%d", arr[i * 4 + j]);
		}
		printf(" ");
	}
	printf("\n");
}
void printArr48(BYTE *arr) {
	int i, j;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 6; j++) {
			printf("%d", arr[i * 6 + j]);
		}
		printf(" ");
	}
	printf("\n");
}
void printArr64(BYTE *arr) {
	int i, j;

	for (i = 0; i < 8; i++) {
		for (j = 0; j <7; j++) {
			printf("%d", arr[i * 7 + j]);
		}
		printf(" ");
	}
	printf("\n");
}
void initialPermutation(BYTE *input, BYTE *output) {
	int i;
	BYTE b[64] = { 0, };
	printf("Input bits : ");
	twoByteChange(input, b);
	
	for (i = 0; i < 64; i++) {
		output[i] = b[IP[i] - 1];
	}
}

void twoByteChange(BYTE *input ,BYTE *out) {
	int i, j, k, tmp;
	BYTE tmpArr[16][4] = { 0, };

	for (i = 0; i < 16; i++) {
		tmp = input[i];
		for (j = 3; j >= 0; j--) {
			tmpArr[i][j] = tmp % 2;
			tmp = tmp / 2;

		}

	}
	k = 0;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 4; j++) {
			out[k] = tmpArr[i][j];
			k++;
		}
	}
	printArr64_8(out);
}

void devideLR(BYTE *input, BYTE *L, BYTE *R) {
	int i;
	for (i = 0; i < 64; i++) {
		if (i < 32) L[i] = input[i];
		else R[i - 32] = input[i];
	}
}

/*Get Key*/
void PC1(BYTE *key, BYTE *output) {
	//페리티 키 제거
	int i,j;
	BYTE tmpS, tmpS2;
	BYTE L_key[28] = { 0, };
	BYTE R_key[28] = { 0, };
	BYTE b[64] = { 0, };
	printf("key bits : ");
	twoByteChange(key, b);
	
	//printArr(b);

	for (i = 0; i < 56; i++) {
		output[i] = b[pcStatic[i] - 1];
	}
	//printArr(output);

}
void PC2(BYTE *input, BYTE *output) {
	int i;
	for (i = 0; i < 48; i++) {
		output[i] = input[pc2Static[i] - 1];
	}
}
void shiftAndGetAllKey(BYTE *key, BYTE (*output)[48]) {
	int i, j;
	BYTE L_key[28] = { 0, };
	BYTE R_key[28] = { 0, };
	BYTE sumKey[56] = { 0, };
	
	printf("CD[0] : ");
	printArr64(key);

	for (i = 0; i < 56; i++) {
		if (i < 28) L_key[i] = key[i];
		else R_key[i - 28] = key[i];
	}

	for (i = 0; i < 16; i++) {
		shiftLeft(L_key, keySchedule[i], 28);
		shiftLeft(R_key, keySchedule[i], 28); // i = 0 일때 c1, d1 / i= 1일때 c2, d2 / i = 2일때 c3, d3
		
		for (j = 0; j < 56; j++) {
			if (j < 28) sumKey[j] = L_key[j];
			else sumKey[j] = R_key[j - 28];
		}
		printf("CD[%d] : ", i + 1);
		printArr64(sumKey);
		PC2(sumKey, output[i]);
		printf("KS[%d] : ", i + 1);
		printArr48(output[i]);

	
	}

}

void extendArr(BYTE *arr, BYTE *exArr) {
	int i;
	for (i = 0; i < 48; i++) {
		exArr[i] = arr[mapExp[i] - 1];
	}
}

void XOR(BYTE *arr1, BYTE *arr2, BYTE *output) {
	int i;
	for (i = 0; i < 48; i++) {
		output[i] = arr1[i] ^ arr2[i];
	}
}

void sBoxRotate(BYTE *arr, BYTE *output) {
	int i, j;
	int col, row; //행, 렬
	int endSBox;

	for (i = 0; i < 8; i++) {
		row = 0;
		col = arr[i * 6] * 2 + arr[i * 6 + 5]; //arr[0];
		//printf("col = %d ", col);
		
		for (j = 4; j >= 1; j--) {
			row += arr[i * 6 + abs(j-5)] * pow(2.0, j - 1);
		}
		//printf("\ncol = %d, row = %d \n",col, row);
		endSBox = MAT_SBOX[i][col][row];
		//printf("%d ", endSBox);
		for (j = 3; j >= 0; j--) {
			output[i * 4 + j] = endSBox % 2;
			endSBox = endSBox / 2;
		}
		
	}
}
void pBox(BYTE *arr, BYTE * output) {
	int i;
	for (i = 0; i < 32; i++) {
		output[i] = arr[MAT_PBOX[i] - 1];
	}
	
}

void RtoL(BYTE *R,BYTE *tempL, BYTE *L) {
	int i;
	for (i = 0; i < 32; i++) {
		tempL[i] = L[i];
		L[i] = R[i];
	}
}

void LPtoR(BYTE *L, BYTE *pBox, BYTE *R) {
	int i;
	for (i = 0; i < 32; i++) {
		R[i] = L[i] ^ pBox[i];
	}
}
