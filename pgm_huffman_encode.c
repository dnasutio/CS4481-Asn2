#include <stdio.h>
#include "pgm_huffman_encode.h";

int main() {
  struct PGM_Image img;
  int *number_of_non_zero_values_in_the_frequency_array;
  load_PGM_Image(&img, "rectangle_2.pgm");
  generate_pixel_frequency(&img, &number_of_non_zero_values_in_the_frequency_array);

  return 0;
}