#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_encode_image.h"

struct pair {
  int symbol;
  int code[20];
};

unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, 
int number_of_nodes, long int *length_of_encoded_image_array) {
  printf("ENCODING IMAGE...\n");
  printf("%d\n",number_of_nodes);

  // get all the symbols
  int symbols[(number_of_nodes) * 2];
  int incr = 0;
  for (int i = 0; i < number_of_nodes; i++) {
    symbols[incr] = huffman_node[i].first_value;
    symbols[incr+1] = huffman_node[i].second_value;
    incr += 2;
  }

  printf("Symbols\n");
  for (int i = 0; i < number_of_nodes * 2; i++) {
    printf("%d: %d\n", i, symbols[i]);
  }

  // remove duplicates
  int count = number_of_nodes * 2;
  for (int i = 0; i < count; i++) {
    for (int j = i+1; j < count; j++) {
      if (symbols[i] == symbols[j]) {
        for (int k = j; k < count; k++) {
          symbols[k] = symbols[k+1];
        }
        j--;
        count--;
      }
    }
  }

  printf("Unique symbols\n");
  for (int i = 0; i < number_of_nodes + 1; i++) {
    printf("%d: %d\n", i, symbols[i]);
  }

  struct pair huffman_codes[number_of_nodes + 1];
  int code_sizes[number_of_nodes + 1];
  for (int i = 0; i < number_of_nodes + 1; i++) {
    huffman_codes[i].symbol = symbols[i];
    huffman_codes[i].code[0] = -1;
    code_sizes[i] = 0;
  }

  


  printf("Getting codes\n");
  
  for (int i = number_of_nodes - 1; i >= 0; i--) {
    for (int j = 0; j < number_of_nodes + 1; j++) {
      // if the first value of the node is the symbol
      if (huffman_node[i].first_value == huffman_codes[j].symbol) {
        // set to 0 if not set yet
        if (huffman_codes[j].code[0] == -1) {
          huffman_codes[j].code[0] = 1;
          code_sizes[j]++;
        } else {
          // copy the bits from first value 
          for (int k = 0; k < number_of_nodes + 1; k++) {
            if (huffman_node[i].second_value == huffman_codes[k].symbol && huffman_codes[k].code[0] == -1) {
              // copy bits one by one
              for (int h = 0; h < code_sizes[j]; h++) {
                huffman_codes[k].code[code_sizes[k]] = huffman_codes[j].code[h];
                code_sizes[k]++;
              }
            }
          }

          // append 0 if already set
          huffman_codes[j].code[code_sizes[j]] = 1;
          code_sizes[j]++;
        }
      }

      if (huffman_node[i].second_value == huffman_codes[j].symbol) {
        if (huffman_codes[j].code[0] == -1) {
          huffman_codes[j].code[0] = 0;
          code_sizes[j]++;
        } else {
          huffman_codes[j].code[code_sizes[j]] = 0;
          code_sizes[j]++;
        }
      }
    }

    /* printf("--------------%d-----------\n", i);
      for (int i = 0; i < number_of_nodes + 1; i++) {
            printf("%d: ", huffman_codes[i].symbol);
            for (int j = 0; j < code_sizes[i]; j++) {
              printf("%d", huffman_codes[i].code[j]);
            }
            printf("\n");
          } */
  }

  printf("Codes\n");
  for (int i = 0; i < number_of_nodes + 1; i++) {
    printf("%d: ", huffman_codes[i].symbol);
    for (int j = 0; j < code_sizes[i]; j++) {
      printf("%d", huffman_codes[i].code[j]);
    }
    printf("\n");
  }  

  int cat_codes[number_of_nodes + 1];
  for (int i = 0; i < number_of_nodes + 1; i++) {
    cat_codes[i] = 0;
    for (int j = 0; j < code_sizes[i]; j++) {
      cat_codes[i] = cat_codes[i] * 10 + huffman_codes[i].code[j];
    }
  }

  for (int i = 0; i < number_of_nodes + 1; i++) {
    printf("cat %d: %d\n", i, cat_codes[i]);
  }


  unsigned char *encoded_img = malloc(sizeof(encoded_img) * input_pgm_image->height * input_pgm_image->width);

  int row, col;
  for (row = 0; row < input_pgm_image->height; row++) {
    for (col = 0; col < input_pgm_image->width; col++) {
      for (int i = 0; i < number_of_nodes + 1; i++) {
        if (input_pgm_image->image[row][col] == huffman_codes[i].symbol) {
            input_pgm_image->image[row][col] = cat_codes[i];
            encoded_img[row*col + col] = cat_codes[i];
        }
      }
    }
  }

  *length_of_encoded_image_array = sizeof(encoded_img);

  printf("IMAGE ENCODED!\n");
  return encoded_img;
}

// for testing only
int main3() {
  struct node huffman_node[5];
  huffman_node[0].first_value = 3;
  huffman_node[0].second_value = 5;

  huffman_node[1].first_value = 1;
  huffman_node[1].second_value = 3;

  huffman_node[2].first_value = 2;
  huffman_node[2].second_value = 4;

  huffman_node[3].first_value = 1;
  huffman_node[3].second_value = 2;

  huffman_node[4].first_value = 0;
  huffman_node[4].second_value = 1;

  int number_of_nodes = 5;

  long int *length_of_encoded_image_array;

  struct PGM_Image img;
  load_PGM_Image(&img, "test_square.raw.pgm");

  huffman_encode_image(&img, &huffman_node[0], number_of_nodes, length_of_encoded_image_array);

  return 0;
}