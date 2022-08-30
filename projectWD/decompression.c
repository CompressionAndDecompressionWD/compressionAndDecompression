#include "decompression.h"
#include <stdio.h>
#include <stdlib.h>
FILE* decompress_main(FILE*, Huffman_code** fil)
{
    return ;
}

Huffman_code** decompress_create_dicitionary(FILE* compressed_file)
{
    Huffman_code** huffman_dictionary,*huffman_code;
    huffman_dictionary = (Huffman_code**)malloc(sizeof(Huffman_code*) * 256);
    int count_codes = 0;
    char c;
    while (count_codes < 256) {
        fread(&c, sizeof(char)*2, 1, compressed_file);

    }
    return ;
}
