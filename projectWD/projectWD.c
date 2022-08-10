#define _CRT_SECURE_NO_WARNINGS

#define LOG_FILE "history.log"
#include <stdio.h>
#include <stdlib.h>
#include "compress_and_decompress.h"
void main()
{
	FILE* s = fopen("demo", "w");
	fputs("abcabc", s);
	fclose(s);
	s = fopen("demo", "r");
	compress_main(s);
}