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
typedef struct min_heap {
	unsigned int size;
	unsigned int capacity;
	Min_heap_node** arr;
}Min_heap;
// stack node
typedef struct SNode
{
	Min_heap_node* t;
	struct SNode* next;
}SNode;
void stack_node_push(SNode**, Min_heap_node*);
Min_heap_node* pop(SNode**);
int stack_node_is_empty(SNode*);
//stack int
typedef struct s_int
{
	int* arr;
	int size;
}S_int;
typedef struct huffman_code {
	int* code;// array to keep int of code
	// maximum 192/sizeof(int)+sizeof(int)192%sizeof(int)
	//for ex:
	// 192/64->2+1->3 numbers to keep code of length 192
	int length;
}Huffman_code;
void stack_int_init(S_int*);
void stack_int_push(S_int*,int num);
int stack_int_pop(S_int*);
int stack_int_isEmpty(S_int*);
//compression
FILE* compress_main(FILE*);
void compress_replace_chars_to_huffman_codes_in_file(FILE*, FILE*, Huffman_code**);
int* compress_build_freq_array(FILE*);
Min_heap* compress_build_huffman_tree(int*);
Min_heap_node* compress_create_new_min_heap_node(int, char);
int compress_heap_is_one_leaf(Min_heap*);
void compress_min_heapify(Min_heap*);
void compress_min_heap_insert(Min_heap*, Min_heap_node*);
Min_heap_node* compress_min_heap_extractmin(Min_heap*);
int* compress_build_huffman_codes_dictionary(Min_heap*);
int compress_build_code_from_stack(S_int*);
Min_heap* compress_build_min_heap(int*);
Min_heap* compress_init_min_heap(Min_heap*);
void compress_heap_node_swap(Min_heap_node*, Min_heap_node*);
//void keep_history(char* function,char* data);
#endif

