#include "libpnm.h"
#include "generate_huffman_nodes.h"

// Node value -1 is root, if a node has values left and right as -1 then they are a leaf
struct Tree_Node {
  int value;
  int left;
  int right;
};

struct PGM_Image *huffman_decode_image( int image_width, int image_height, int max_gray_value, int
number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned char
*encoded_image);