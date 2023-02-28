#include "libpnm.h"

struct node {
  int first_value;
  int second_value;
};

struct Tree_Node {
  int value;
  struct Tree_Node *left;
  struct Tree_Node *right;
} Tree_Node_Default = {-1, NULL, NULL};

struct PGM_Image *huffman_decode_image( int image_width, int image_height, int max_gray_value, int
number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned char
*encoded_image);