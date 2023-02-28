#include <stdio.h>
#include "huffman_decode_image.h"

struct PGM_Image *huffman_decode_image( int image_width, int image_height, int max_gray_value, int
number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned char
*encoded_image) {
  struct Tree_Node *root;
  root = malloc(sizeof(struct Tree_Node));
  struct Tree_Node* node_list[(number_of_nodes * 2) + 1];

  node_list[0] = root;

  struct Tree_Node *left, *right;
  left = malloc(sizeof(struct Tree_Node));
  right = malloc(sizeof(struct Tree_Node));
  left->value = huffman_node[number_of_nodes - 1].first_value;
  right->value = huffman_node[number_of_nodes - 1].second_value;
  root->left = left;
  root->right = right;

  node_list[1] = left;
  node_list[2] = right;

  // this the nearest empty space in the node_list array
  int curr_end = 3;

  // iterate through huffman nodes
  for (int j = number_of_nodes - 1; j >= 0; j--) {
    printf("j %d\n", j);
    // iterate through tree node list
    for (int i = 0; i < (number_of_nodes * 2) + 1; i++) {
      printf("%d\n", i);
      // if the first value of the huffman node is found in the tree node list
      if (node_list[i]->value == huffman_node[j].first_value) {
        printf("Balls\n");
        // create left and right nodes with first and second values respectively
        struct Tree_Node *left, *right;
        left = malloc(sizeof(struct Tree_Node));
        right = malloc(sizeof(struct Tree_Node));
        left->value = huffman_node[j].first_value;
        right->value = huffman_node[j].second_value;
        printf("Balls1\n");

        // set them at their appropriate index in the tree node list
        node_list[curr_end] = left;
        node_list[curr_end + 1] = right;
        printf("Balls2\n");

        // replace the tree node at curr_end - 1 with an internal node
        struct Tree_Node *internal;
        internal = malloc(sizeof(struct Tree_Node));
        internal->value = -2;
        node_list[curr_end - 1] = internal;
        printf("Balls3\n");
        break;
      }
    }

    for (int i = 0; i < curr_end; i++) {
      printf("[%d | %d | %d]\n", node_list[i]->left->value, node_list[i]->value, node_list[i]->right->value);
    }

    // add 2 because two tree nodes were added to the node_list
    curr_end += 2;
  }

  

  for (int i = 0; i < (number_of_nodes * 2) + 1; i++) {
    printf("[%d | %d | %d]\n", node_list[i]->left->value, node_list[i]->value, node_list[i]->right->value);
  }
  
  
  return 0;
}

// For testing only
int main() {
  struct node huffman_node[5];
  huffman_node[0].first_value = 3;
  huffman_node[0].second_value = 5;

  huffman_node[1].first_value = 1;
  huffman_node[1].second_value = 3;

  huffman_node[2].first_value = 2;
  huffman_node[2].second_value = 4;

  huffman_node[3].first_value = 1;
  huffman_node[3].second_value = 2;

  huffman_node[4].first_value = 0;
  huffman_node[4].second_value = 1;

  huffman_decode_image(0, 0, 0, 6, &huffman_node[0], 0, 0);

  return 0;
}