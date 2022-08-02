#define _CRT_SECURE_NO_WARNINGS

#ifndef compress_and_decompress
#define compress_and_decompress
#include <stdio.h>
#include <stdlib.h>
typedef struct min_heap_node {
	char c;
	int freq;
	struct min_heap_node* left;
	struct min_heap_node* right;
}Min_heap_node;
//compression
FILE* compress(char*);
FILE* replace(FILE*,FILE*,int*);
int* freq_count(FILE*);
Min_heap_node** build_huffman_tree(int*);
Min_heap_node* create_new_node(int, char);
int is_one_leaf(Min_heap_node*);
void min_heapify(Min_heap_node**);
void insert_min_heap(Min_heap_node**, Min_heap_node*);
Min_heap_node* extractmin(Min_heap_node**);
char** huffman_code(Min_heap_node**);
Min_heap_node** build_min_heap(int*, char*);
void swap(Min_heap_node*, Min_heap_node*);

#endif
