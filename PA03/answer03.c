 #include "answer03.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int compare(const void * a, const void * b);
int comparechar(const void * a, const void * b);
/**
 * Append the C-string 'src' to the end of the C-string '*dest'.
 *
 * strcat_ex(...) will append the C-string 'src' to the end of the string
 * at '*dest'. The parameter 'n' is the address of a int that specifies how
 * many characters can safely be stored in '*dest'. 
 *
 * If '*dest' is NULL, or if '*dest' is not large enough to contain the result,
 * then strcat_ex will:
 * (1) malloc a new buffer of size 1 + 2 * (strlen(*dest) + strlen(src))
 * (2) set '*n' to the size of the new buffer
 * (3) copy '*dest' into the beginning of the new buffer
 * (4) free the memory '*dest', and then set '*dest' to point to the new buffer
 * (5) concatenate 'src' onto the end of '*dest'.
 *
 * Always returns *dest.
 *
 * Why do we need to pass dest as char * *, and n as int *? 
 * Please see the FAQ for an answer.
 *
 * Hint: These <string.h> functions will help: strcat, strcpy, strlen.
 * Hint: Leak no memory.
 */
char * strcat_ex(char * * dest, int * n, const char * src)
{
  // if(*dest == NULL || (strlen(*dest)+strlen(src) > *n))
  size_t src_len = strlen(src);
  size_t dest_len = *dest == NULL ? 0 : strlen(*dest);
  if(*dest == NULL || (src_len + dest_len + 1) >= *n) 
    {
      char * buff;
      *n = 1 + 2 * (src_len + dest_len);
      buff = malloc(*n * sizeof(char));
      *buff = '\0';
      if (!(*dest == NULL))
	  {
	    strcpy(buff, *dest);
	  }
      free(*dest);
      *dest = buff;
    }
 
  
  strcat(*dest,src);
  
  return *dest;
}

/**
 * Takes a string and splits it into an array of strings according to delimiter.
 * The memory location '*arrLen' is initialized to the length of the returned
 * array.
 *
 * 'delims' is a string that contains a set of delimiter characters. 
 * explode(...) will split the string at any character that appears in 'delims'.
 *
 * For example, if delimiter is white space " \t\v\n\r\f", then,
 * int len;
 * char * * strArr = explode("The\nTuring test", " \t\v\n\r\f", &len);
 * // len = 3, strArr[0] is "The", strArr[1] is "Turing", strArr[2] is "test"
 *
 * Hint: you can use <string.h> functions "memcpy" and "strchr"
 *       "memcpy" copies blocks of memory.
 *       "strchr" can be used to tell if a specific character is in delims.
 * Hint: this question is hard; it will help to draw out your algorithm.
 * Hint: read the FAQ...
 */
char * * explode(const char * str, const char * delims, int * arrLen)
{
 
  //Calculate Number of strings
  *arrLen = 1;
  const char * pos = str;
  while(*pos != '\0')
    {
      if(strchr(delims,*pos))
	{
	  *arrLen = *arrLen + 1;
	}
      pos++;
    }


  //Allocate Memory
  char * * strArr = malloc(*arrLen * sizeof(char *));


  //Insert Strings
  int arrInd = 0;
  const char * start = str;
  pos = str;

  while(*pos != '\0')
    {
      if(strchr(delims,*pos))
	{
	  int len = pos - start;
	  strArr[arrInd] = malloc((len + 1) * sizeof(char));
	  memcpy(strArr[arrInd], start, (len) * sizeof(char));
	  strArr[arrInd][len] = '\0';
	  arrInd++;
	  start = pos + 1;
	}
      pos++;
    }

  int len = pos - start;
  strArr[arrInd] = malloc((len + 1) * sizeof(char));
  memcpy(strArr[arrInd], start, (len) * sizeof(char));
  strArr[arrInd][len] = '\0';
  return strArr;
}


char * implode(char * * strArr, int len, const char * glue)
{
  int i;
  char * str= malloc(1 * sizeof(char));
  strcpy(str, "");
  int length = 0;
  for(i = 0; i < len;i++)
    {
      str = strcat_ex(&str, &length, strArr[i]);
      if((i+1) != len)
	{
	  str = strcat_ex(&str, &length, glue);
	}
    }
  return str;
}


void sortStringArray(char * * arrString, int len)
{
  qsort(arrString, len, sizeof(char *), compare);
  return;
}

int compare(const void * a, const void * b)
{
  return(strcmp(*(char **) a, *(char **) b));
}



void sortStringCharacters(char * str)
{
  qsort(str, strlen(str), sizeof(char), comparechar);
  return;
}

int comparechar(const void * a, const void * b)
{
  return(*(char*)a-*(char*)b);
}



void destroyStringArray(char * * strArr, int len)
{
  int i;
  for(i = 0; i < len; i++)
    {
      free(strArr[i]);
    }
  free(strArr);
  return;
}


