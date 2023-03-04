#include <stdio.h>
#include "generate_pixel_frequency.h"

long int *generate_pixel_frequency(struct PGM_Image *input_pgm_image, int
*number_of_non_zero_values_in_the_frequency_array) {
  printf("GENERATING PIXEL FREQUENCIES...\n");
  // Dynamically allocates a long int array of (max_gray_value + 1) elements
  long int *pixel_frequency;
  
  pixel_frequency = (long int *) malloc(sizeof(long int) * (input_pgm_image->maxGrayValue + 1));

  for (int i = 0; i < input_pgm_image->maxGrayValue + 1; i++) {
    pixel_frequency[i] = 0;
  }
  
  // Reads ALL pixels in the provided PGM image and record the frequency of occurrence of each pixel values in the allocated array
  int row, col;

  for (row = 0; row < input_pgm_image->height; row++) {
    for (col = 0; col < input_pgm_image->width; col++) {
      pixel_frequency[input_pgm_image->image[row][col]] += 1;
    }
  }

  // TEST: Print all color frequencies
  /* for (int i = 0; i < input_pgm_image->maxGrayValue; i++) {
    printf("%d %ld\n", i, pixel_frequency[i]);
  } */
  int count = 0;
  for (int i = 0; i < input_pgm_image->maxGrayValue + 1; i++) {
    if (pixel_frequency[i] != 0)
      count++;
  }
  
  *number_of_non_zero_values_in_the_frequency_array = count;
  

  printf("PIXEL FREQUENCIES GENERATED!\n");
  return pixel_frequency;
}

// TEST: call generate_pixel_frequency and print the color frequencies
int main1() {
  struct PGM_Image img;
  int x = 0;
  int *number_of_non_zero_values_in_the_frequency_array;
  number_of_non_zero_values_in_the_frequency_array = &x;

  load_PGM_Image(&img, "test_square.raw.pgm");

  // Without this there is Error -> malloc(): invalid size (unsorted) Aborted
  printf("Generating pixel frequency...\n");

  long int *pixel_frequency;
  pixel_frequency = generate_pixel_frequency(&img, number_of_non_zero_values_in_the_frequency_array);

  printf("returned\n");

  // TEST: Print all color frequencies
  /* for (int i = 0; i < input_pgm_image->maxGrayValue; i++) {
    printf("%d %ld\n", i, pixel_frequency[i]);
  } */

  return 0;
}