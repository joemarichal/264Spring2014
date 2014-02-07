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
  if(*dest == NULL || (strlen(*dest)+strlen(src) > *n))
    {
      char * buff;
      buff = (char *)malloc(1 + 2 * (strlen(*dest) + strlen(src)));
      *n = (1 + 2 * (strlen(*dest) + strlen(src)));
      strcpy(buff,*dest);
      dest = &buff;
      free(buff);
    }
 
  printf("Running strcat_ex\n");
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
  int i;
  int n = 1;
  for(i = 0; i < *arrLen; i++)
    {
      if(strchr(delims,str[i]))
	{
	  n++;
	}
    }
  char * * strArr = malloc(n * sizeof(char *));

  int arrInd = 0;
  int last = 0;
  for(i = 0; i < *arrLen; i++)
    {
      if(strchr(delims,str[i]))
	{
	  strArr[arrInd] = malloc((i - last) * sizeof(char));
	  memcpy(strArr[arrInd], &str[last], (i - last) * sizeof(char));
 	  arrInd++;
	  last = i + 1;
 	}
    }
  strArr[arrInd] = malloc((i - last) * sizeof(char));
  memcpy(strArr[arrInd], &str[last], (i - last) * sizeof(char));
  return strArr;
}

/**
 * Takes an array of strings, and then concatenates them into a single string,
 * placing 'glue' between each.
 *
 * For example:
 * int len;
 * char * * strArr = explode("100 224 147 80", " ", &len);
 * char * str = implode(strArr, len, ", ");
 * printf("(%s)\n", str); // (100, 224, 147, 80)
 *
 * Hint: use strcat_ex in a for loop.
 */
char * implode(char * * strArr, int len, const char * glue)
{
  int i;
  char * str= "";
  int length = 0;
  for(i = 0; i < len;i++)
    {
      str = strcat_ex(&str, &length, strArr[i]);
      str = strcat_ex(&str, &length, glue);
    }
  return str;
}

/**
 * Takes an array of C-strings, and sorts them alphabetically, ascending.
 *
 * For example, 
 * int len;
 * char * * strArr = explode("lady beatle brew", " ", &len);
 * sortStringArray(strArr, len);
 * char * str = implode(strArr, len, " ");
 * printf("%s\n"); // beatle brew lady
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_ understand the typecasts.
 */
void sortStringArray(char * * arrString, int len)
{
  qsort(arrString, len, sizeof(char *), compare);
  return;
}

int compare(const void * a, const void * b)
{
  return(strcmp(*(char **) a, *(char **) b));
}

/**
 * Sorts the characters in a string.
 *
 * For example, 
 * char * s1 = strdup("How did it get so late so soon?");
 * sortStringCharacters(s1)
 * // s1 is now "       ?Haddeegiilnooooossstttw"
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_  understand the typecasts.
 */
void sortStringCharacters(char * str)
{
  qsort(str, strlen(str), sizeof(char), comparechar);
  return;
}

int comparechar(const void * a, const void * b)
{
  return(*(char*)a-*(char*)b);
}
/**
 * Safely frees all memory associated with strArr, and then strArr itself.
 * Passing NULL as the first parameter has no effect.
 *
 * int len;
 * const char * abe = "Give me six hours to chop down a tree and I will spend\n"
 *                    "the first four sharpening the axe.";
 * char * * strArr = explode(abe, "\n ");
 * destroyStringArray(strArr, len); // cleans memory -- no memory leaks
 * destroyStringArray(NULL, 0); // does nothing, does not crash.
 */
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


