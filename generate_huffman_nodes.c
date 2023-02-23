#include <stdio.h>
#include <limits.h>
#include "generate_huffman_nodes.h"

struct node {
  int first_value;
  int second_value;
};

struct node *generate_huffman_nodes(long int *pixel_frequency, int max_gray_value, int
number_of_non_zero_values_in_the_frequency_array) {
  // create ordered pair array and set unmarked nodes to number of non zero values in frequency array
  struct node *ordered_pairs;
  ordered_pairs = (struct node*) malloc(sizeof(struct node) * (number_of_non_zero_values_in_the_frequency_array - 1));

  // test
  for (int j = 0; j < 6; j ++)
    printf("%ld\n", pixel_frequency[j]);
 

  // initialize ordered_pairs value
  for (int j = 0; j < number_of_non_zero_values_in_the_frequency_array - 1; j++) {
    ordered_pairs[j].first_value = -1;
    ordered_pairs[j].second_value = -1;
  }
  
  printf("Creating ordered pairs...\n");
  long int *temp_freq = pixel_frequency; // copy the frequency array for manipulation
  int j = 0; // used to track which ordered pair is being worked on
  long int smallest_value = INT_MAX; // keeps track of smallest value
  int smallest_index = 0; // the index holding the smallest value in the copied frequency array
  int next_smallest_index = 0; // the index holding the second smallest value in the copied frequency array
  int i = 0; // used to track which frequency in the frequency array is being worked on
  int count = number_of_non_zero_values_in_the_frequency_array; // used to track how many more values to look at in the copied frequency array
  
  // iterate over the length of the ordered pairs array
  while(j < number_of_non_zero_values_in_the_frequency_array - 1) {
    // get the smallest value and store its index in ordered_pairs[j]
    printf("Getting smallest...\n");
    while (count != 0) {
      if (temp_freq[i] != 0) {
        // if temp_freq[i] != -1 that means there is nothing there and it shouldn't be considered
        if (temp_freq[i] != -1 && temp_freq[i] < smallest_value) {
          ordered_pairs[j].first_value = i;
          smallest_index = i;
          smallest_value = temp_freq[i];
          printf("%i %ld\n", i, smallest_value);
        }
        count--;
      }
      i++;
    }

    // get the next smallest value and store its index in ordered_pairs[j]
    printf("Getting next smallest...\n");
    i = 0, count = number_of_non_zero_values_in_the_frequency_array, smallest_value = INT_MAX;
    
    while (count != 0) {
      if (i != smallest_index && temp_freq[i] != 0) {
        if (temp_freq[i] != -1 && temp_freq[i] < smallest_value) {
          ordered_pairs[j].second_value = i;
          next_smallest_index = i;
          smallest_value = temp_freq[i];
          printf("%i %ld\n", i, smallest_value);
        }
        count--;
      }
      i++;
    }

    // swap the first and second value if first value > second value
    int hold = -1;
    if (ordered_pairs[j].first_value > ordered_pairs[j].second_value) {
      hold = ordered_pairs[j].second_value;
      ordered_pairs[j].second_value = ordered_pairs[j].first_value;
      ordered_pairs[j].first_value = hold;
    }

    printf("(%d, ", ordered_pairs[j].first_value);
    printf(" %d)\n", ordered_pairs[j].second_value);

    // the sum of the smallest and next smallest must always propogate up to the index closer to 0
    if (smallest_index < next_smallest_index) {
      temp_freq[smallest_index] = temp_freq[smallest_index] + temp_freq[next_smallest_index];
      temp_freq[next_smallest_index] = -1;
    } else {
      // this is for the case where the smaller value is at the larger index
      temp_freq[next_smallest_index] = temp_freq[smallest_index] + temp_freq[next_smallest_index];
      temp_freq[smallest_index] = -1;
    }

    for (int j = 0; j < 6; j ++)
      printf("%d %ld\n", j, temp_freq[j]); 

    count = number_of_non_zero_values_in_the_frequency_array;
    smallest_index = 0;
    next_smallest_index = 0;
    smallest_value = INT_MAX;
    i = 0;
    j++;
  }

  printf("Ordered pairs created!\n");

  for (int j = 0; j < 6; j ++)
    printf("%ld\n", temp_freq[j]);

  for (int j = 0; j < number_of_non_zero_values_in_the_frequency_array - 1; j++) {
    printf("(%d, ", ordered_pairs[j].first_value);
    printf(" %d)\n", ordered_pairs[j].second_value);
  }

  return ordered_pairs;
}



// for testing only
int main() {
  long int pixel_frequency[10];
  //pixel_frequency = (long int*) malloc(10);
  pixel_frequency[0] = 20; // 32
  pixel_frequency[1] = 0;
  pixel_frequency[2] = 3; // 5 -> 12 -> -1
  pixel_frequency[3] = 0;
  pixel_frequency[4] = 0;
  pixel_frequency[5] = 3; // 7 -> -1
  pixel_frequency[6] = 1; // 2 -> -1
  pixel_frequency[7] = 4; // -1
  pixel_frequency[8] = 0;
  pixel_frequency[9] = 1; // -1

  /* pixel_frequency[0] = 20;
  pixel_frequency[1] = 3;
  pixel_frequency[2] = 3;
  pixel_frequency[3] = 1;
  pixel_frequency[4] = 4;
  pixel_frequency[5] = 1; */

  // (6, 9) (2, 6) (5, 7) (2, 5) (0, 2)

  int max_gray_value = 255;
  int number_of_non_zero_values_in_the_frequency_array = 6;

  printf("Generating Huffman nodes...\n");
  generate_huffman_nodes(&pixel_frequency[0], max_gray_value, number_of_non_zero_values_in_the_frequency_array);
  printf("returned\n");

  return 0;
}