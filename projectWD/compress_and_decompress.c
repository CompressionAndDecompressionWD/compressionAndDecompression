#include "compress_and_decompress.h"
#include <string.h>
#include <math.h>
#include <dos.h>
#define nullptr NULL
#define _CRT_SECURE_NO_WARNINGS
#define LOG_FILE "history.log"
#define CHAR_TO_TRUCK 'a'
//??? ?????? ?? ?????? ???????? ??????
S_int* stack_int_init(S_int* S)
{
	S = (S_int*)malloc(sizeof(S_int));
	S->arr = (int*)malloc(sizeof(int));
	S->size = 0;
	return S;
}
void stack_int_push(S_int** Stack, int num)
{
	S_int* S = *Stack;
	S->size++;
	S->arr = (int*)realloc(S->arr, sizeof(int) * S->size);
	S->arr[S->size - 1] = num;

}
int stack_int_pop(S_int* S) {
}
int stack_int_isEmpty(S_int* S) {
}
void stack_node_push(SNode** top_ref, Min_heap_node* t)
{
	SNode* new_node = NULL;
	new_node = (SNode*)malloc(sizeof(SNode));
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
FILE* compress_main(FILE* sourse_file)
{
	//FILE* sourse_file = fopen(code_file, "r");
	if (sourse_file == NULL) {
		//to do ...
		perror("demo");
		exit(1);
	}
	int* freq_arr = compress_build_freq_array(sourse_file);
	Min_heap* huffman_tree = compress_build_huffman_tree(freq_arr);
	Huffman_code** huffman_dictionary_char_codes =  compress_build_huffman_codes_dictionary(huffman_tree);
	char* file_name = NULL;
	_strdup(file_name, "demo");
	strcat(file_name, ".bin");
	FILE* compressed_file = fopen(file_name, "wb");
	if (compressed_file == NULL)
		exit(1);
	//todo...
	compress_replace_chars_to_huffman_codes_in_file(sourse_file, compressed_file, huffman_dictionary_char_codes);
	return compressed_file;
}
//FILE* compress_replace_chars_to_huffman_codes_in_file(FILE* sourse_file, FILE* compressed_file, Huffman_code* huffman_codes_dictionary)
//{
//	// code=int number
//	Huffman_code code;
//	int ch = NULL, temp=0,count = sizeof(int);
//	do
//	{
//		ch = fgetc(sourse_file);
//		code = huffman_codes_dictionary[ch];
//		// ????? ??? ??? ???? ????? ????? ???
//		//????? ?????? ????
//		// temp=0
//		//code= 7 -> .....00000111
//		//length=5
//		temp = code.code[0] << (sizeof(int) - code.length);
//		count -= code.length;//?
//		// count =32-5=27
//		// temp= 00111000000.....
//
//		// ????? ?????? ?????
//		//code =25-> ....0000000011001
//		//length=30
//		// 000000...->27 11001
//		// i want 000... ->25 11001
//		// code<<32-30
//		// x-> 00000code
//		// x= code>>sizeof(int)-count
//		// temp=temp||x
//		// temp= 0011100000000000000000000000011 ----- 001(00)
//		// count-=length
//		// count<=0? !
//		// put temp to the file
//		// temp =0
//		// length_new=count*(-1)
//		// length_new=3
//		// count*=-1
//		// code << length-length_new
//		// code =  0010000 .... 000
//		// temp=code = 001000.......
//		// ????? ????? ????
//		// count=3
//		// we have 29 bits
//		// we need 70 bits -> 3 numbers
//		// ????? ??? 3 ?????? ????? 
//		// temp 001......
//		// code[0]->32 bits ->19
//		// 19>>3
//		// 19||temp
//		//count-=length // 3-70=-67
//		// count<=0? !
//		// put temp to the file
//		// temp =0
//		// length_new=count*(-1)
//		// length_new=67
//		// count*=-1 // 67
//		// code<<length-length_new 67 =3
//		// (010)1111111111111111 1110000000111111111110 1011
//		// count-=length // 67-70
//		// temp= code>>count
//		// put temp
//		// temp=0
//		// count=35
//		//  ???? ????
//		// ???? ????
//		// ???? ????? ??????
//		
//		// count =32
//		// code-> code=3
//		//code->length=5
//		//int =3
//		// real -> 00011
//		// code->code= .... 00000000 00000011
//		// i want : 00011 ..........
//		// <<32-length
//		//count=32-5=27
//		//Q=11111111111111111100000000111111100000000011111111
//		//dic[Q].code[0]=(int)0000000110100111111100000000011111 (32 bit)
//		//dic[Q].code[1]=(int)0000001101001111111000000000111110 (32 bit)
//		//dic[Q].code[2]=(int)...........101101
//		//dic[Q].length=80
//		// last-> shift (sizeofint- length%sizeofint)
//		//?????????
//		
//	
//	} while (ch!=EOF);
//
//}
void compress_replace_chars_to_huffman_codes_in_file(FILE* sourse_file, FILE* compressed_file, Huffman_code** huffman_codes_dictionary)
{
	Huffman_code* current_code;
	unsigned int ch, i, temp = 0, index_temp = 0, next_int = 0, len = 0, len_of_int = sizeof(int) * 8;
	ch = fgetc(sourse_file);
	while (ch != EOF)
	{
		current_code = huffman_codes_dictionary[ch];
		for (i = 0; i < current_code->length / len_of_int; i++)
		{
			//insert into temp bits from the code as long as there is place
			temp = temp | current_code->code[i] >> index_temp;
			//keep in next_int the bits that not entered to temp
			if (len_of_int - index_temp < 32)
				next_int = ((current_code->code[i]) << (len_of_int - index_temp));
			//write temp to the file
			fwrite((const void*)&temp, sizeof(int), 1, compressed_file);
			temp = 0;
			//fill temp with the bits that not entered last time for the next write to the file
			temp = temp | next_int;
		}
		//len- num of bits for the last int of the current code
		len = current_code->length % len_of_int;
		if (len != 0) {
			//if temp won't be full after add this number
			if (index_temp + len < len_of_int) {
				//add the code to temp and push to avoid extra zeros
				temp = temp | current_code->code[i] << (len_of_int - len - index_temp);
				//now temp has more len bits
				index_temp += len;
			}
			//if temp will be exactly full after add this number
			else if (index_temp + len == len_of_int) {
				//add the code to temp - no need to push because it should start from the index_temp
				temp = temp | current_code->code[i];
				//write temp to the file
				fwrite((const void*)&temp, sizeof(int), 1, compressed_file);
				temp = 0;
				index_temp = 0;
			}
			//if temp will be full after add this number and there were bits that had no place
			else {
				temp = temp | current_code->code[i] >> index_temp;
				fwrite((const void*)&temp, sizeof(int), 1, compressed_file);
				temp = 0;
				//add the bits that not entered to the file and push to avoid extra zeros
				temp = temp | current_code->code[i] << len_of_int - len - index_temp;
				index_temp = len + index_temp - len_of_int;
			}
		}
		ch = fgetc(sourse_file);
	}
	if (temp != 0)
		fwrite((const void*)&temp, sizeof(int), 1, compressed_file);
}

int* compress_build_freq_array(FILE* code_file)
{
	int* arr_freq = NULL;
	arr_freq = (int*)calloc(255, sizeof(int));
	int ch=0;
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
Min_heap_node** compress_create_new_min_heap_node(int* freq, char c)
{
	Min_heap_node* node = NULL;
	node = (Min_heap_node*)malloc(sizeof(Min_heap_node));
	node->c = c;
	node->freq = *freq;
	return &node;
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
	heap->arr = (Min_heap_node**)realloc(heap->arr, sizeof(Min_heap_node*) * heap->size);
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
	heap->arr[0] = heap->arr[heap->size - 1];
	free(heap->arr[heap->size - 1]);
	compress_min_heapify(heap, 0);
	heap->size--;
	return node;
}
int* compress_build_code_from_stack(S_int* S)
{
	int* code=NULL, i = S->size-1,mul=1,count_digits=0,j=0;
	code = (int*)calloc(1,sizeof(int));
	while (i >=0)
	{
		code[j] += S->arr[i] * mul;
		mul *= 2;
		i--;
		count_digits++;
		if (count_digits == 32) {
			j++;
			code = (int*)realloc(code, sizeof(int) * j);
			code[j] = 0;
			count_digits = 0;
		}
	}
	return code;
}
//?????????
Huffman_code** compress_build_huffman_codes_dictionary(Min_heap* root)
{
	Huffman_code** huffman_codes = NULL;
	int size = 0;
	huffman_codes = (Huffman_code**)malloc(sizeof(Huffman_code*)*255);
	//if the tree has 1 node
	huffman_codes[0] = (Huffman_code*)malloc(sizeof(Huffman_code));
	huffman_codes[0]->code= 0;
	huffman_codes[0]->length= 1;
	Min_heap_node* current = root->arr[0];
	SNode* node_stack = NULL;
	S_int* code_stack = NULL;
	code_stack=stack_int_init(code_stack);
	int done = 0;
	while (!done)
	{
		if (current != NULL)
		{
			stack_node_push(&node_stack,current);
			stack_int_push(&code_stack, 0);
			if (!(current->left || current->right)) {
				// output the code stack to huffman array
				huffman_codes[current->c] = (Huffman_code*)malloc(sizeof(Huffman_code));
				huffman_codes[current->c]->code = compress_build_code_from_stack(code_stack);
				huffman_codes[current->c]->length = code_stack->size;
			}
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
	
	return huffman_codes;
}
Min_heap* compress_build_min_heap(int* freq_arr)
{
	Min_heap* min_heap = NULL;
	min_heap = compress_init_min_heap(min_heap);
	//create node for each charcter+freq
	
	for (int i = 0; i <255; i++)
	{
		if (freq_arr[i] != 0) {
			min_heap->arr = (Min_heap_node**)realloc(min_heap->arr, sizeof(Min_heap_node*) * ++min_heap->size);
			//min_heap->arr[min_heap->size] = (Min_heap_node*)malloc(sizeof(Min_heap_node));
			min_heap->arr[min_heap->size] = *(compress_create_new_min_heap_node(freq_arr+i, (char)i));
		}
	}
	//build the heap
	for (int i = min_heap->size; i > min_heap->size / 2; i++)
	{
		compress_min_heapify(min_heap, i);
	}
	return min_heap;
}
Min_heap* compress_init_min_heap(Min_heap* min_heap)
{
	min_heap = (Min_heap*)malloc(sizeof(Min_heap));
	min_heap->size = 0;
	min_heap->capacity = 255;
	min_heap->arr = (Min_heap_node**)calloc(1,sizeof(Min_heap_node*));
	return min_heap;
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
