#include "libpnm.h"

struct node {
  int first_value;
  int second_value;
};

void store_huffman_encoded_data(char *compressed_file_name_ptr, int image_width, int image_height, int
max_gray_value, int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned
char *encoded_image);