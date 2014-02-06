#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "answer03.h"

int main(int argc, char ** argv)
{
  printf("Welcome to PA03!\n");
  char * buff;
  buff = (char *) malloc(10*sizeof(char));
  strcpy(buff, "This is the start");
  printf("buff = %s\n",buff); 
  char * er = ", and this is the end!";
  int size = 10;

  //Testing strcat_ex
  printf("buff = %s\n\n\n", strcat_ex(&buff, &size,er));




  printf("Freeing Memory...\n");
  free(buff);
  printf("Memory Free!\n");
  return 0;
}
