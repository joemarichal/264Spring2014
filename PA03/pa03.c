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
  char * er = ", and this is the end!";
  int size = 10;

  //Testing strcat_ex

  printf("buff = %s\n\n\n", strcat_ex(&buff, &size,er));
 
  //Testing explode
  int length;
  const char * hi = "What in the Fuck?";
  length = strlen(hi);
  char * * strArr = explode(hi," ", &length);
  printf("strArr[1] = %s\n\n\n", strArr[1]);

  //Testing implode
  printf("Implosion: %s\n\n\n",implode(strArr,4," "));

  printf("Freeing Memory...\n");
  free(buff);
  free(strArr);
  printf("Memory Free!\n");
  return 0;
}
