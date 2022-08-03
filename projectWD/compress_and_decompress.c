#include "compress_and_decompress.h"
#include <string.h>
#include <math.h>
#include <dos.h>
#define nullptr NULL
#define _CRT_SECURE_NO_WARNINGS
#define LOG_FILE "history.log"

#define CHAR_TO_TRUCK 'a'
//איך כותבים את השמירת היסטוריה הזאת??
void stack_int_init(S_int* S)
{
	S->arr = (int*)malloc(sizeof(int));
	S->size = 0;
}
void stack_int_push(S_int*S, int num)
{
	
	S->size ++;
	S->arr = (int*)realloc(S->arr,sizeof(int)*S->size);
	S->arr[S->size - 1] = num;
	
}
int stack_int_pop(S_int* S) {

}
int stack_int_isEmpty(S_int* S) {

}
void stack_node_push(SNode** top_ref, Min_heap_node* t)
{

	 SNode* new_node =
		( SNode*)malloc(sizeof( SNode));

	if (new_node == NULL)
	{
		printf("Stack Overflow \n");
		getchar();
		exit(0);
	}

	/* put in the data  */
	new_node->t = t;

	/* link the old list off the new tNode */
	new_node->next = (*top_ref);

	/* move the head to point to the new tNode */
	(*top_ref) = new_node;
}
Min_heap_node* pop(SNode** top_ref)
{
	struct Min_heap_node* res;
	struct SNode* top;

	/*If sNode is empty then error */
	if (stack_node_is_empty(*top_ref))
	{
		printf("Stack Underflow \n");
		getchar();
		exit(0);
	}
	else
	{
		top = *top_ref;
		res = top->t;
		*top_ref = top->next;
		free(top);
		return res;
	}
}
int stack_node_is_empty(SNode* top)
{
	return (top == NULL) ? 1 : 0;

}
FILE* compress_main(char* code_file)
{
	FILE* sourse_file = fopen(code_file, "r");
	if (sourse_file == NULL) {
		//to do ...
		exit(1);
	}
	int* freq_arr = compress_build_freq_array(code_file);

	Min_heap* huffman_tree = build_huffman_tree(freq_arr);

	char** huffman_array = huffman_code(huffman_tree);

	int* freq_arr = compress_build_freq_array(sourse_file);
	Min_heap* huffman_tree = compress_build_huffman_tree(freq_arr);
	int*huffman_dictionary_char_codes = compress_build_huffman_codes_dictionary(huffman_tree);

	char* file_name = NULL;
	_strdup(file_name, code_file);
	strcat(file_name, ".bin");
	FILE* compressed_file = fopen(file_name, "wb");
	if (compressed_file == NULL)
		exit(1);
	//todo...
	compress_replace_chars_to_huffman_codes_in_file(sourse_file, compressed_file, huffman_array);
	return compressed_file;
}

FILE* compress_replace_chars_to_huffman_codes_in_file(FILE* sourse_file, FILE* compressed_file, int* huffman_array)
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

int* compress_build_freq_array(FILE* code_file)
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

Min_heap* compress_build_huffman_tree(int* freq_arr)
{
	Min_heap* min_heap = compress_build_min_heap(freq_arr);
	while (compress_heap_is_one_leaf(min_heap))
	{
		Min_heap_node* right = compress_min_heap_extractmin(min_heap);
		Min_heap_node* left = compress_min_heap_extractmin(min_heap);
		Min_heap_node* new_internal_node = compress_create_new_min_heap_node(right->freq + left->freq, '$');
		new_internal_node->right = right;
		new_internal_node->left = left;
		compress_min_heap_insert(min_heap, new_internal_node);
	}
	return min_heap;
}

Min_heap_node* compress_create_new_min_heap_node(int freq, char c)
{
	Min_heap_node* node = NULL;
	node = (Min_heap_node*)malloc(sizeof(Min_heap_node));
	node->c = c;
	node->freq = freq;
	return node;
}

int compress_heap_is_one_leaf(Min_heap* heap)
{
	return heap->size > 1;
}
void compress_min_heapify(Min_heap* h, int index)
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
		compress_heap_node_swap(&h->arr[index], &h->arr[smallest]);
		compress_min_heapify(h, smallest);
	}
}

void compress_min_heap_insert(Min_heap* heap, Min_heap_node* node)
{
	heap->size++;
	heap->arr = (Min_heap_node**)realloc(heap->arr, sizeof(Min_heap_node*)*heap->size);
	if (heap->arr == NULL) {
		exit(1);
		//to do
	}
	heap->arr[heap->size - 1] = node;
	compress_min_heapify(heap, 0);
}

Min_heap_node* compress_min_heap_extractmin(Min_heap* heap)
{
	Min_heap_node* node = heap->arr[0];
	heap->arr[0] = heap->arr[heap->size-1];
	free(heap->arr[heap->size-1]);
	compress_min_heapify(heap, 0);
	heap->size--;
	return node;
}

int* compress_build_huffman_codes_dictionary(Min_heap* root)
{
	char** huffman_codes = NULL;
	huffman_codes = (char**)malloc(sizeof(char*));
	//if the tree has 1 node
	huffman_codes[0] = "0";
	 Min_heap_node* current = root->arr[0];
	 SNode* node_stack = NULL; 
	 S_int* code_stack = NULL; 
	 stack_int_init(code_stack);
	int done = 0;
	Min_heap_node* current = root->arr[0];
	SNode* node_stack = NULL;
	S_int* code_stack = NULL;
	stack_int_init(code_stack);
	int done = 0;
	while (!done)
	{
		if (!current->left && !current->right) {
			// output the code stack to huffman array
		}
		if (current != NULL)
		{
			stack_node_push(&node_stack, current);
			stack_push_int(code_stack, 0);
			current = current->left;
		}
		else
		{
			if (!stack_node_is_empty(node_stack))
			{
				current = pop(&node_stack);
				stack_int_pop(code_stack);
				current = current->right;
			}
			else
			{
				done = 1;
			}
		}
	}

	while (!done)
	{
		if (!current->left && !current->right) {
			// output the code stack to huffman array
		}
		if (current != NULL)
		{
			stack_node_push(&node_stack, current);
			stack_push_int(code_stack, 0);
			current = current->left;
		}
		else
		{
			if (!stack_node_is_empty(node_stack))
			{
				current = pop(&node_stack);
				stack_int_pop(code_stack);
				current = current->right;
			}
			else
			{
				done = 1;
			}
		}
	} 
}

Min_heap* compress_build_min_heap(int* freq_arr)

{
	Min_heap* min_heap;
	compress_init_min_heap(min_heap);
	//create node for each charcter+freq
	for (int i = 0; i < sizeof(freq_arr)/sizeof(int); i++)
	{
		if (freq_arr[i] != 0) {
			min_heap->arr = (Min_heap_node**)realloc(min_heap->arr, sizeof(Min_heap_node*) * min_heap->size);
			min_heap->arr[min_heap->size++]= compress_create_new_min_heap_node(freq_arr[i], (char)i);
		}
	}
	//build the heap
	for (int i = min_heap->size; i > min_heap->size/2; i++)
	{
		compress_min_heapify(min_heap, i);
	}
	return min_heap;
}

void compress_init_min_heap(Min_heap* min_heap)
{
	min_heap->size = 0;
	min_heap->capacity = 255;
    min_heap->arr = (Min_heap_node**)malloc(sizeof(Min_heap_node*));
}

void compress_heap_node_swap(Min_heap_node* a, Min_heap_node* b)
{
	Min_heap_node temp = *a;
	*a = *b;
	*b = temp;
}

//void keep_history(char* function, char* data)
//{
//	time_t t;   // not a primitive datatype
//	time(&t);
//	char* date_time = ctime(&t);
//	FILE* log_file = fopen(LOG_FILE, "w");
//	char* history = NULL;
//	history = _strdup(date_time);
//	history = (char*)realloc(history, sizeof(history) + sizeof(function) + sizeof(data) + 23);
//	strcat(history, " : ");
//	strcat(history, " function: ");
//	strcat(history, function);;
//	strcat(history, " state: ");
//	strcat(history, data);
//	strcat(history, "\0");
//	fputs( history, log_file);
//	fclose(log_file);
//}
