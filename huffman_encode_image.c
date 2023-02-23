#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_encode_image.h"

unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, int
number_of_nodes, long int *length_of_encoded_image_array) {
  unsigned char *huffman_codes[number_of_nodes + 1]; // the number of huffman codes is 1 more than the number of nodes
  
  for (int i = 0; i < number_of_nodes + 1; i++) {
    huffman_codes[i] = (unsigned char *) malloc(sizeof (unsigned char)); // allocate for one unsigned char
    huffman_codes[i][0] = '\0'; // manually set the null terminator
  }

  // used for concatenating
  unsigned char zero = '0';
  unsigned char one = '1';

  // used to track which code needs more space (everything starts at 2 because its the first character of the code + the null terminator)
  int buffers[number_of_nodes + 1];
  for (int i = 0; i < number_of_nodes + 1; i++) {
    buffers[i] = 2;
  }
  

  // iterate through huffman nodes backwards
  for (int i = number_of_nodes - 1; i >= 0; i-- ) {
    // allocate {buffer} space for the huffman code with index {second value}
    huffman_codes[huffman_node[i].second_value] = realloc(huffman_codes[huffman_node[i].second_value], buffers[huffman_node[i].second_value] * (sizeof (unsigned char)));

    // if the huffman code at index {first value} is not null, then concatenate it to the huffman code at index {second value}
    if (huffman_codes[huffman_node[i].first_value]) {
      strcat(huffman_codes[huffman_node[i].second_value], huffman_codes[huffman_node[i].first_value]);
    }

    // allocate {buffer} space for the huffman code with index {first value}
    huffman_codes[huffman_node[i].first_value] = realloc(huffman_codes[huffman_node[i].first_value], buffers[huffman_node[i].first_value] * (sizeof (unsigned char)));

    // concatenate zero huffman code with index {first value} and one to huffman code with index {second value} 
    strncat(huffman_codes[huffman_node[i].first_value], &zero, 1);
    strncat(huffman_codes[huffman_node[i].second_value], &one, 1);

    // prepare buffer for this particular code
    buffers[huffman_node[i].second_value]++;
    buffers[huffman_node[i].first_value]++;
  }

  for (int i = 0; i < number_of_nodes + 1; i++) {
    printf("%s\n", huffman_codes[i]);
  }

  return 0;
}

// for testing only
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

  int number_of_nodes = 5;

  long int *length_of_encoded_image_array;

  struct PGM_Image img;
  load_PGM_Image(&img, "test_square.raw.pgm");

  huffman_encode_image(&img, &huffman_node[0], number_of_nodes, length_of_encoded_image_array);

  return 0;
}