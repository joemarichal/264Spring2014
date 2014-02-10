#include <stdio.h>
#include <string.h>
#define EXIT_SUCCESS 0

int main(int argc, char ** argv)
{
  int i;

  for(i = 1; i < argc; i++)
    {
      if(!strcmp(argv[i],"--help"))
	{
	  printf("Usage: grep-lite [OPTION]... PATTERN\n");
	  printf("Search for PATTERN in standard input. PATTERN is a\n");
	  printf("string. grep-lite will search standard input line by\n");
	  printf("line, and (by default) print out those lines which\n");
	  printf("contain pattern as a substring\n\n");
	  printf("  -v, --invert-match     select non-matching lines\n");
	  printf("  -n, --line-number      print line numbers with output\n");
	  printf("  -q, --quiet            suppress all output\n\n");
	  printf("Exit status is 0 if any line is selected, 1 otherwise;\n");
	  printf("if any error occurs, then the exit status is 2.\n");
	  return EXIT_SUCCESS;
	}
    }       
  return EXIT_SUCCESS;
}
