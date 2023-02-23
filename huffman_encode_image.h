#include "libpnm.h"

struct node {
  int first_value;
  int second_value;
};

unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, int
number_of_nodes, long int *length_of_encoded_image_array);