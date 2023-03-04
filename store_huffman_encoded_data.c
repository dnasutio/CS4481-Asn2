#include <stdio.h>
#include "store_huffman_encoded_data.h"

void store_huffman_encoded_data(char *compressed_file_name_ptr, int image_width, int image_height, 
int max_gray_value, int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, 
unsigned char *encoded_image) {

  FILE *fptr;

  fptr = fopen(compressed_file_name_ptr, "w");

  if(fptr == NULL) {
    printf("Error: Something wrong with file.");
    exit(1);    
  }

  fprintf(fptr, "%d\n%d\n%d\n%d\n", image_width, image_height, max_gray_value, number_of_nodes);
  for (int i = 0; i < number_of_nodes; i++)
    fprintf(fptr, "(%d, %d)\n", huffman_node[i].first_value, huffman_node[i].second_value);
  
  fprintf(fptr, "%ld\n", length_of_encoded_image_array);

  int row, col;
  for (row = 0; row < image_height; row++) {
    for (col = 0; col < image_width; col++) {
      fprintf(fptr, "%d ", encoded_image[row*image_width + col]);
    }
  }

  fclose(fptr);

  return 0;
}