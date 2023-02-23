#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void doThing(int number_of_nodes) {
  unsigned char *huffman_codes[number_of_nodes + 1];
  for (int i = 0; i < number_of_nodes + 1; i++) {
    huffman_codes[i] = (unsigned char *) malloc(sizeof (unsigned char));
  }

  unsigned char zero = '0';
  unsigned char one = '1';

  strncat(huffman_codes[0], &zero, 1);
  printf("%s\n", huffman_codes[0]);

  strncat(huffman_codes[0], &one, 1);
  printf("%s\n", huffman_codes[0]);

  strncat(huffman_codes[0], &one, 1);
  printf("%s\n", huffman_codes[0]);

  strncat(huffman_codes[1], &zero, 1);
  printf("%s\n", huffman_codes[1]);

  strncat(huffman_codes[1], &zero, 1);
  printf("%s\n", huffman_codes[1]);

  strncat(huffman_codes[1], &zero, 1);
  printf("%s\n", huffman_codes[1]);

  strncat(huffman_codes[1], &one, 1);
  printf("%s\n", huffman_codes[1]);

  strncat(huffman_codes[0], &zero, 1);
  printf("%s\n", huffman_codes[0]);

  

  printf("balls\n");

  

  for (int i = 0; i < 6; i++) {
    printf("%s\n", huffman_codes[i]);
  }
}

int main() {
  doThing(5);
  return 0;
}