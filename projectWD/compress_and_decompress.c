#include "compress_and_decompress.h"
#include <string.h>
#include <math.h>
#define nullptr NULL
#define _CRT_SECURE_NO_WARNINGS
FILE* compress(char* code_file)
{
	FILE* sourse_file = fopen(code_file, "r");
	if (sourse_file == NULL) {
		//to do ...
		exit(1);
	}
	int* freq_arr = freq_count(code_file);
	Min_heap_node** huffman_tree = build_huffman_tree(freq_arr);
	char** huffman_array = huffman_code(huffman_tree);
	char* file_name=NULL;
	_strdup(file_name, code_file);
	strcat(file_name, ".bin");
	FILE* compressed_file = fopen(file_name, "wb");
	if (compressed_file == NULL)
		exit(1);
	//todo...
	replace(sourse_file, compressed_file, huffman_array);
}

FILE* replace(FILE* sourse_file,FILE* compressed_file,int * huffman_array)
{

	int ch, temp, i = 0, index_code = 0;
	char char_code;
	char* code;
	ch = fgetc(sourse_file);
	do
	{
		code = huffman_array[ch];
		while (index_code < strlen(code) && i < 8)
		{
			temp += code[index_code] * pow(2, index_code % 8);
			i++;
			index_code++;
		}

		if (index_code <= strlen(code)) {
			//finish temp and not finish code
			char_code = temp;
			fwrite(&char_code, 1, 1, compressed_file);
			i = 0;
			temp = 0;
		}

		if (i <= 8) {
			//finish code
			ch = fgetc(sourse_file);
			index_code = 0;
		}
	} while (ch != EOF);

}

int* freq_count(FILE* code_file)
{
	return nullptr;
}

Min_heap_node** build_huffman_tree(int* freq_arr)
{
}

Min_heap_node* create_new_node(int freq, char c)
{
	return nullptr;
}

int is_one_leaf(Min_heap_node* heap)
{
	return 0;
}

void insert_min_heap(Min_heap_node** heap, Min_heap_node* node)
{
}

Min_heap_node* extractmin(Min_heap_node** heap)
{
	return nullptr;
}

char** huffman_code(Min_heap_node** root)
{
	return nullptr;
}

Min_heap_node** build_min_heap(int* freq_arr, char* char_arr)
{
	return nullptr;
}

void swap(Min_heap_node* a, Min_heap_node* b)
{
}
