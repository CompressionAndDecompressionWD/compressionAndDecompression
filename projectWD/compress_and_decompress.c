#include "compress_and_decompress.h"
#include <string.h>
#include <math.h>
#include <time.h>
#define nullptr NULL
#define _CRT_SECURE_NO_WARNINGS
#define LOG_FILE "history.log"
FILE* compress(char* code_file)
{
	FILE* sourse_file = fopen(code_file, "r");
	if (sourse_file == NULL) {
		//to do ...
		exit(1);
	}
	int* freq_arr = freq_count(code_file);
	Min_heap* huffman_tree = build_huffman_tree(freq_arr);
	char** huffman_array = huffman_code(huffman_tree);
	char* file_name = NULL;
	_strdup(file_name, code_file);
	strcat(file_name, ".bin");
	FILE* compressed_file = fopen(file_name, "wb");
	if (compressed_file == NULL)
		exit(1);
	//todo...
	replace(sourse_file, compressed_file, huffman_array);
}

FILE* replace(FILE* sourse_file, FILE* compressed_file, int* huffman_array)
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
	int* arr_freq = NULL;
	arr_freq = (int*)calloc(255, sizeof(int));
	int ch = fgetc(code_file);
	while (ch != EOF)
	{
		ch = fgetc(code_file);
		arr_freq[ch]++;
	}
	return arr_freq;
}

Min_heap* build_huffman_tree(int* freq_arr)
{
	Min_heap* min_heap = build_min_heap(freq_arr);
	while (is_one_leaf(min_heap))
	{
		Min_heap_node* right = extractmin(min_heap);
		Min_heap_node* left = extractmin(min_heap);
		Min_heap_node* new_internal_node = create_new_node(right->freq + left->freq, '$');
		new_internal_node->right = right;
		new_internal_node->left = left;
		insert_min_heap(min_heap, new_internal_node);
	}
	return min_heap;
}

Min_heap_node* create_new_node(int freq, char c)
{
	Min_heap_node* node = NULL;
	node = (Min_heap_node*)malloc(sizeof(Min_heap_node));
	node->c = c;
	node->freq = freq;
	return node;
}

int is_one_leaf(Min_heap* heap)
{
	return heap->size > 1;
}
//
//void min_heapify(Min_heap* h, int index)
//{
//	int temp;
//	int parent_node = (index - 1) / 2;
//
//	if (h->arr[parent_node]->freq > h->arr[index]->freq) {
//		//swap and recursive call
//		temp = h->arr[parent_node];
//		h->arr[parent_node] = h->arr[index];
//		h->arr[index] = temp;
//		min_heapify(h, parent_node);
//	}
//}
void min_heapify(Min_heap* h, int index)
{
	int left_index = index * 2 + 1;
	int right_index = index * 2 + 2;
	int smallest = index;
	if (left_index < h->size && h->arr[left_index]->freq < h->arr[index]->freq)
		smallest = left_index;
	if (right_index < h->size && h->arr[right_index]->freq < h->arr[smallest]->freq)
		smallest = right_index;
	if (smallest != index)
	{
		swap(&h->arr[index], &h->arr[smallest]);
		min_heapify(h, smallest);
	}
}

void insert_min_heap(Min_heap* heap, Min_heap_node* node)
{
	//size++
}

Min_heap_node* extractmin(Min_heap* heap)
{
	//size--;
	return nullptr;
}

char** huffman_code(Min_heap* root)
{
	return nullptr;
}

Min_heap* build_min_heap(int* freq_arr)
{

	return nullptr;
}

void swap(Min_heap_node* a, Min_heap_node* b)
{
	Min_heap_node temp = *a;
	*a = *b;
	*b = temp;
}

void keep_history(char* function, char* data)
{
	FILE* log_file = fopen(LOG_FILE, "w");
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	//fputs( tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	
}
