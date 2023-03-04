#include <stdio.h>
#include "mean_absolute_error.h"

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
    printf("Error: The first file should have extension pgm and the second file should have extension pgm.\n");
    return 0;
  }

  printf("Arguments validated.\n");

  mean_absolute_error(argv[1], argv[2]);
  return 0;
}