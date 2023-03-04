#include <stdio.h>
#include "read_huffman_encoded_data.h"
#include "huffman_decode_image.h"

int main(int argc, char *argv[]) {
  // Ensure exactly two arguments are received
  if (argc != 3) {
    printf("Error: There must be exactly two arguments: an input PGM file name and an output compressed file name.\n");
    return 0;
  }

  // Validate file extensions for both input and output file names
  char *extension_input_file = strrchr(argv[1], '.');
  char *extension_output_file = strrchr(argv[2], '.');
  
  if (!extension_input_file || !extension_output_file) {
    printf("Error: Both files must have an extension.\n");
    return 0;
  } 

  if (0 != strcasecmp(extension_input_file, ".comp") || 0 != strcasecmp(extension_output_file, ".pgm")) {
    printf("Error: The first file should have extension comp and the second file should have extension pgm.\n");
    return 0;
  }

  printf("Arguments validated.\n");

  unsigned char *encoded_image;
  int *image_width, *image_height, *max_gray_value;
  int *number_of_nodes;
  struct node **huffman_node;
  long int *length_of_encoded_image_array;
  encoded_image = read_huffman_encoded_data(argv[1], image_width, image_height, max_gray_value, number_of_nodes, huffman_node, length_of_encoded_image_array);

  struct PGM_Image *img;
  img = huffman_decode_image(*image_width, *image_height, *max_gray_value, *number_of_nodes, *huffman_node, *length_of_encoded_image_array, encoded_image);

  return 0;
}

