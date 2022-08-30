#define _CRT_SECURE_NO_WARNINGS
#ifndef decompression
#define decompression
#include <stdio.h>
#include <stdlib.h>
typedef struct huffman_code {
	unsigned int* code;
	int length;
}Huffman_code;
FILE* decompress_main(FILE*,Huffman_code*);
Huffman_code* decompress_create_dicitionary(FILE*);

#endif