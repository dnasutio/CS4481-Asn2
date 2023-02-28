#include <stdio.h>
#include <string.h>
#include "generate_pixel_frequency.h"
#include "generate_huffman_nodes.h"
#include "huffman_encode_image.h"

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

  if (0 != strcasecmp(extension_input_file, ".pgm") || 0 != strcasecmp(extension_output_file, ".pgm")) {
    printf("Error: The file extension .pgm should be used by both files.\n");
    return 0;
  }

  printf("Arguments validated.\n");

  // Load the input image
  struct PGM_Image img;
  load_PGM_Image(&img, argv[1]);

  // Generate the pixel frequencies of the input image and the number of non-zero values in the frequency array
  int *number_of_non_zero_values_in_the_frequency_array;
  long int *pixel_frequency;
  pixel_frequency = generate_pixel_frequency(&img, &number_of_non_zero_values_in_the_frequency_array);

  // Generate huffman nodes
  struct node *huffman_node;
  huffman_node = generate_huffman_nodes(&pixel_frequency, img.maxGrayValue, *number_of_non_zero_values_in_the_frequency_array);

  // Huffman encode the input image
  unsigned char *encoded_image;
  int number_of_nodes = number_of_non_zero_values_in_the_frequency_array - 1;
  long int *length_of_encoded_image_array;
  encoded_image = huffman_encode_image(&img, &huffman_node, number_of_nodes, &length_of_encoded_image_array);

  


  return 0;
}