#include <stdio.h>
#include <limits.h>
#include "generate_huffman_nodes.h"

struct node *generate_huffman_nodes(long int *pixel_frequency, int max_gray_value, int
number_of_non_zero_values_in_the_frequency_array) {
  printf("GENERATING HUFFMAN NODES...\n");
  
  // create ordered pair array and set unmarked nodes to number of non zero values in frequency array
  struct node *ordered_pairs;
  int num_ordered_pairs = number_of_non_zero_values_in_the_frequency_array - 1;
  ordered_pairs = malloc(sizeof(ordered_pairs) * (num_ordered_pairs));
  
  // test
  /* for (int i = 0; i < 256; i++) {
    printf("%d %ld\n", i, pixel_frequency[i]);
  } */

  // initialize ordered_pairs value
  for (int j = 0; j < number_of_non_zero_values_in_the_frequency_array - 1; j++) {
    ordered_pairs[j].first_value = -1;
    ordered_pairs[j].second_value = -1;
  }

  
  // get collect only the non-zero frequencies and store them in descending order
  int symbols[number_of_non_zero_values_in_the_frequency_array];
  long int frequencies[number_of_non_zero_values_in_the_frequency_array];
  int x = 0; // track which symbol needs to be added
  long int *temp = pixel_frequency;
  int largest_index = -1;
  long int largest_freq = 0;
  int k = 0; // track which non-zero frequencies were seen
  int i = 0; // track pixel_frequency index
  int count = number_of_non_zero_values_in_the_frequency_array; // used to track how many more values to look at in the copied frequency array
  int inner_count = number_of_non_zero_values_in_the_frequency_array; // track inner loop iterations (decrease by 1 each iteration)
  // when k = number_of_non_zero_values_in_the_frequency_array that means only zeroes remain which means we are done
  while (count != 0) {
    // search for the largest frequency
    while (k != inner_count) {
      if (temp[i] != 0) {
        if (temp[i] > largest_freq) {
          largest_freq = temp[i];
          largest_index = i;
          
        }
        k++;
      }
      i++;
    }

    // set to zero so we know we don't need to visit it anymore
    temp[largest_index] = 0;
    inner_count--;
    
    // set symbol and corresponding frequency
    symbols[x] = largest_index;
    frequencies[x] = largest_freq;
    x++;
    // reset for next search
    largest_index = -1;
    largest_freq = 0;
    k = 0;
    i = 0;
    
    count--;
  }

  /* for (int i = 0; i < number_of_non_zero_values_in_the_frequency_array; i++) {
    printf("%d: %d\n", symbols[i], frequencies[i]);
  } */
  

  //printf("Creating ordered pairs...\n");
  long int *temp_freq = frequencies; // copy the frequency array for manipulation
  int j = 0; // used to track which ordered pair is being worked on
  long int smallest_value = INT_MAX; // keeps track of smallest value
  int smallest_index = 0; // the index holding the smallest value in the copied frequency array
  int next_smallest_index = 0; // the index holding the second smallest value in the copied frequency array
  i = 0; // used to track which frequency in the frequency array is being worked on
  count = number_of_non_zero_values_in_the_frequency_array; // used to track how many more values to look at in the copied frequency array
  
  // iterate over the length of the ordered pairs array
  while(j < number_of_non_zero_values_in_the_frequency_array - 1) {
    // get the smallest value and store its index in ordered_pairs[j]
    //printf("Getting smallest...\n");
    while (count != 0) {
      // if temp_freq[i] != -1 that means there is nothing there and it shouldn't be considered
      if (temp_freq[i] != -1 && temp_freq[i] < smallest_value) {
        ordered_pairs[j].first_value = symbols[i];
        smallest_index = i;
        smallest_value = temp_freq[i];
        
      }
      count--;
      i++;
    }

    // get the next smallest value and store its index in ordered_pairs[j]
    //printf("Getting next smallest...\n");
    i = 0, count = number_of_non_zero_values_in_the_frequency_array, smallest_value = INT_MAX;
    
    while (count != 0) {
      if (i != smallest_index) {
        if (temp_freq[i] != -1 && temp_freq[i] < smallest_value) {
          ordered_pairs[j].second_value = symbols[i];
          next_smallest_index = i;
          smallest_value = temp_freq[i];
          
        }
        count--;
      }
      i++;
    }

    // swap the first and second value if first value > second value
    int hold = -1;
    if (smallest_index > next_smallest_index) {
      hold = ordered_pairs[j].second_value;
      ordered_pairs[j].second_value = ordered_pairs[j].first_value;
      ordered_pairs[j].first_value = hold;
    }

    /* printf("(%d, ", ordered_pairs[j].first_value);
    printf(" %d)\n", ordered_pairs[j].second_value); */

    // the sum of the smallest and next smallest must always propogate up to the index closer to 0
    if (smallest_index < next_smallest_index) {
      temp_freq[smallest_index] = temp_freq[smallest_index] + temp_freq[next_smallest_index];
      temp_freq[next_smallest_index] = -1;
    } else {
      // this is for the case where the smaller value is at the larger index
      temp_freq[next_smallest_index] = temp_freq[smallest_index] + temp_freq[next_smallest_index];
      temp_freq[smallest_index] = -1;
    }

    /* for (int j = 0; j < number_of_non_zero_values_in_the_frequency_array; j ++) {
      if (temp_freq[j] != 0)
        printf("%d %ld\n", j, temp_freq[j]); 
    } */

    count = number_of_non_zero_values_in_the_frequency_array;
    smallest_index = 0;
    next_smallest_index = 0;
    smallest_value = INT_MAX;
    i = 0;
    j++;
  }

  printf("Ordered pairs created!\n");

  /* for (int j = 0; j < 6; j ++)
    printf("%ld\n", temp_freq[j]);

  for (int j = 0; j < number_of_non_zero_values_in_the_frequency_array - 1; j++) {
    printf("(%d, ", ordered_pairs[j].first_value);
    printf(" %d)\n", ordered_pairs[j].second_value);
  } */


  printf("HUFFMAN NODES GENERATED!\n");
  return ordered_pairs;
}



// for testing only
int main2() {
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