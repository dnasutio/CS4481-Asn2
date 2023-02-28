#include <stdio.h>
#include "store_huffman_encoded_data.h"

void store_huffman_encoded_data(char *compressed_file_name_ptr, int image_width, int image_height, int
max_gray_value, int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned
char *encoded_image) {
  // Maybe not this
  FILE *fptr;

  fptr = fopen(&compressed_file_name_ptr, "w");

  if(fptr == NULL) {
    printf("Error: Something wrong with file.");
    exit(1);    
  }

  fprintf(fptr, "%d %d %d %d", image_width, image_height, max_gray_value, number_of_nodes);
  for (int i = 0; i < number_of_nodes; i++)
    fprintf(fptr, "(%d, %d)\n", huffman_node->first_value, huffman_node->second_value);
  
  fprintf(fptr, "%d\n", length_of_encoded_image_array);


  // Maybe this?
  struct PGM_Image img;
  create_PGM_Image(&img, image_width, image_height, max_gray_value);

  // write to the file somehow 


  save_PGM_Image(&img, &compressed_file_name_ptr, 1);



  return 0;
}