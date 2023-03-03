#include <stdio.h>
#include "huffman_decode_image.h"

// CONSIDER: Currently left and right reference nodes directly. Maybe it would be better to reference index instead (so store int).
// Using int removes need to mess with malloc.

struct PGM_Image *huffman_decode_image( int image_width, int image_height, int max_gray_value, int
number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned char
*encoded_image) {
  

  struct Tree_Node root = {-1, -1, -1};
  
  struct Tree_Node node_list[(number_of_nodes * 2) + 1];

  struct Tree_Node left, right;
  left.value = huffman_node[number_of_nodes - 1].first_value;
  left.left = -1;
  left.right = -1;
  right.value = huffman_node[number_of_nodes - 1].second_value;
  right.left = -1;
  right.right = -1;

  root.left = 1;
  root.right = 2;

  node_list[0] = root;
  node_list[1] = left;
  node_list[2] = right;

  // this the nearest empty space in the node_list array
  int curr_end = 3;

  // iterate through huffman nodes
  for (int j = number_of_nodes - 2; j >= 0; j--) {
    printf("j %d\n", j);
    // iterate through tree node list
    for (int i = 0; i < (number_of_nodes * 2) + 1; i++) {
      printf("%d\n", i);
      // if the first value of the huffman node is found in the tree node list
      if (node_list[i].value == huffman_node[j].first_value) {
        printf("Balls\n");
        // create left and right nodes with first and second values respectively
        struct Tree_Node left, right;
        
        left.value = huffman_node[j].first_value;
        left.left = -1;
        left.right = -1;
        right.value = huffman_node[j].second_value;
        right.left = -1;
        right.right = -1;
        printf("Balls1\n");

        // set them at their appropriate index in the tree node list
        node_list[curr_end] = left;
        node_list[curr_end + 1] = right;
        printf("Balls2\n");

        // replace the tree node at curr_end - 1 with an internal node
        struct Tree_Node internal;
        internal.value = -2;
        // set left and right of the internal node as the indexes of the left and right recently added to node_list
        internal.left = curr_end;
        internal.right = curr_end + 1;
        
        // set at appropriate index in node list

        node_list[i] = internal;

        printf("Balls3\n");

        for (int i = 0; i < curr_end + 2; i++) {
          printf("%d: [%d  |  %d  |  %d]\n", i, node_list[i].left, node_list[i].value, node_list[i].right);
        }

        break;
      }
    }

    // add 2 because two tree nodes were added to the node_list
    curr_end += 2;
  }

  printf("-----------------------------------------\n\n");

  for (int i = 0; i < (number_of_nodes * 2) + 1; i++) {
    printf("%d: [%d | %d | %d]\n", i, node_list[i].left, node_list[i].value, node_list[i].right);
  }
  

  // UNTESTED
  struct PGM_Image img;
  create_PGM_Image(&img, image_width, image_height, max_gray_value);
  int row = 0, col = 0;
  unsigned char *t;
  struct Tree_Node curr = node_list[0]; // root
  for (t = encoded_image; *t != '\0'; t++) {
    // while not at leaf (not at internal which has value -2)
    while (curr.value != -2) {
      if (*t == 0)
        curr = node_list[curr.left];
      else
        curr = node_list[curr.right];
    }
    

    // this is wrong because its just the index, not the actual value 
    img.image[row][col] = curr.value;

  }

  printf("\n%s\n", encoded_image);
  return 0;
}

// For testing only
int main1() {
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

  unsigned char encoded_image[] = "111001111001011110001010";

  huffman_decode_image(0, 0, 0, 5, &huffman_node[0], 0, &encoded_image[0]);

  return 0;
}