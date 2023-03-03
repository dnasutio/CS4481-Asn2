#include "libpnm.h"
#include "generate_huffman_nodes.h"

#ifndef HUFF_ENCODE_IMG_H
#define HUFF_ENCODE_IMG_H


unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, 
int number_of_nodes, long int *length_of_encoded_image_array);

#endif