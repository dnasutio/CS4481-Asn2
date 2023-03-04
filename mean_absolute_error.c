#include <stdio.h>
#include "mean_absolute_error.h"

float mean_absolute_error(char *file_name_1_ptr, char *file_name_2_ptr) {
  FILE *fptr1;

  fptr1 = fopen(file_name_1_ptr, "rb");
  
  

  fclose(fptr1);

  FILE *fptr2;
  fptr2 = fopen(file_name_2_ptr, "rb");

  fclose(fptr2);
  float mean_absolute_error;

  return mean_absolute_error;
}