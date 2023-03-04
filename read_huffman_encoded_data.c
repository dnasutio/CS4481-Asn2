#include <stdio.h>
#include "read_huffman_encoded_data.h"

unsigned char *read_huffman_encoded_data(char *compressed_file_name_ptr, int *image_width, int *image_height, int
*max_gray_value, int *number_of_nodes, struct node **huffman_node, long int *length_of_encoded_image_array) {
  FILE *fptr;

  fptr = fopen(compressed_file_name_ptr, "r");

  fscanf(fptr, "%d", image_width);
  fscanf(fptr, "%d", image_height);
  fscanf(fptr, "%d", max_gray_value);
  fscanf(fptr, "%d", number_of_nodes);

  for (int i = 0; i < number_of_nodes; i++) {
    fgetc(fptr); // skip (
    huffman_node[i]->first_value = fgetc(fptr);
    fgetc(fptr); // skip ,
    huffman_node[i]->second_value = fgetc(fptr);
    fgetc(fptr); // skip )
  }

  fscanf(fptr, "%d", length_of_encoded_image_array);

  int row, col;
  unsigned char *encoded_image = malloc(sizeof(encoded_image) * (*image_height) * (*image_width));

  for (row = 0; row < *image_height; row++) {
    for (col = 0; col < *image_width; col++) {
      encoded_image[(row * (*image_width)) + col] = fgetc(fptr);
      fscanf(fptr, "%d ", encoded_image[(row * (*image_width)) + col]);
    }
  }
  
  fclose(fptr);

  return encoded_image;
}