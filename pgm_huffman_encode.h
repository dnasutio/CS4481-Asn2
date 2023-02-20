#include "libpnm.h"
// Functions for pgm_huffman_encode.c (Q8)

// Q1
long int *generate_pixel_frequency(struct PGM_Image *input_pgm_image, int
*number_of_non_zero_values_in_the_frequency_array);

// Q2
struct node *generate_huffman_nodes(long int *pixel_frequency, int max_gray_value, int
number_of_non_zero_values_in_the_frequency_array);

// Q3
unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, int
number_of_nodes, long int *length_of_encoded_image_array);

// Q4
void store_huffman_encoded_data(char *compressed_file_name_ptr, int image_width, int image_height, int
max_gray_value, int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned
char *encoded_image);
