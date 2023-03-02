#include "libpnm.h"

struct node {
  int first_value;
  int second_value;
};

// Node value -1 is root, if a node has values left and right as -1 then they are a leaf
struct Tree_Node {
  int value;
  int left;
  int right;
};

struct PGM_Image *huffman_decode_image( int image_width, int image_height, int max_gray_value, int
number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned char
*encoded_image);