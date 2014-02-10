#include <stdio.h>
#include <string.h>
#define EXIT_SUCCESS 0

int main(int argc, char ** argv)
{
  int i;
  int matchfound = 0;
  int linenumber = 1;
  int lineswitch = 0;
  int quietswitch = 0;
  int invertswitch = 0;

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
      if(!strcmp(argv[i],"-q"))
	{
	  quietswitch = 1;
	}
      else if(!strcmp(argv[i],"-v"))
	{
	  invertswitch = 1;
	}
      else if(!strcmp(argv[i],"-n"))
	{
	  lineswitch = 1;
	}
      else if(argv[i][0] == '-')
	{
	  fprintf(stderr, "Invalid argument %s\n", argv[i]);
	  return 2;
	}
    }
  if(argv[argc-1][0] == '-' || argc == 1)
    {
      fprintf(stderr, "Invalid or missing PATTERN\n");
      return 2;
    }
       
  return EXIT_SUCCESS;
}


