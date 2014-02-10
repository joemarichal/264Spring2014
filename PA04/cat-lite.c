#include <stdio.h>
#include <string.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(int argc, char ** argv)
{
  int i;
  int c;
  FILE *fp;

  //No input arguments - use stdin
  if(argc == 1)
    {
      do{
	c = fgetc(stdin);
	fputc(c, stdout);
      }while(c != '\n');
      
    }

  for(i = 1; i < argc; i++)
    {
      if(!strcmp(argv[i],"--help"))
	{
	  printf("<Usage: cat-lite [--help] [FILE]...\n");
	  printf("With no FILE, or when FILE is -, read standard input\n\n");
	  printf("Examples:\n");
	  printf("   cat-lite README   Print the file README to standard output.\n");
	  printf("   cat-lite f - g    Print f's contents, then standard input,\n");
	  printf("                     then g's contents.\n");
	  printf("   cat-lite          Copy standard input to standard output.\n");
	  return EXIT_SUCCESS;
	}
    }

  for(i = 1; i < argc; i++)
    {
      if(!strcmp(argv[i], "-"))
	{
	  do{
	    c = fgetc(stdin);
	    fputc(c, stdout);
	  }while(c != '\n');
	}
      else
	{
	  fp = fopen(argv[i],"r");
	  if(fp == NULL)
	    {
	      fprintf(stderr, "cat cannot open %s\n", argv[i]);
	      return EXIT_FAILURE;
	    }
	  do{
	    c = fgetc(fp);
	    if(c != EOF)
	      {
		fputc(c,stdout);
	      }
	  }while(c != EOF);

	  fclose(fp);
	}
    }
  return EXIT_SUCCESS;
}
