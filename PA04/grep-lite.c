#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char ** argv)
{
  int i;
  int matchfound = 0;
  int linenumber = 1;
  int lineswitch = 0;
  int quietswitch = 0;
  int invertswitch = 0;
 

  //Check for arguments
  for(i = 1; i < argc; i++)
    {
      if(!strcmp(argv[i],"--help"))
	{
	  fprintf(stdout,"Usage: grep-lite [OPTION]... PATTERN\n");
	  fprintf(stdout,"Search for PATTERN in standard input. PATTERN is a\n");
	  fprintf(stdout,"string. grep-lite will search standard input line by\n");
	  fprintf(stdout,"line, and (by default) print out those lines which\n");
	  fprintf(stdout,"contain pattern as a substring.\n\n");
	  fprintf(stdout,"  -v, --invert-match     print non-matching lines\n");
	  fprintf(stdout,"  -n, --line-number      print line number with output\n");
	  fprintf(stdout,"  -q, --quiet            suppress all output\n\n");
	  fprintf(stdout,"Exit status is 0 if any line is selected, 1 otherwise;\n");
	  fprintf(stdout,"if any error occurs, then the exit status is 2.\n\n");
	  return 0;
	}
      if(!strcmp(argv[i],"-q") || !strcmp(argv[i], "--quiet"))
	{
	  quietswitch = 1;
	}
      else if(!strcmp(argv[i],"-v") || !strcmp(argv[i], "--invert-match"))
	{
	  invertswitch = 1;
	}
      else if(!strcmp(argv[i],"-n") || !strcmp(argv[i], "--line-number"))
	{
	  lineswitch = 1;
	}
      else if(argv[i][0] == '-')
	{
	  fprintf(stderr, "Invalid argument %s\n", argv[i]);
	  return 2;
	}
    }


  //Figure if PATTERN IS VALID
  if(argv[argc-1][0] == '-' || argc == 1)
    {
      fprintf(stderr, "Invalid or missing PATTERN\n");
      return 2;
    }

  char * str = malloc(2000*sizeof(char));
  //Find PATTERN
  if(!invertswitch && !quietswitch && !lineswitch)
    {
      
      while(fgets(str, 2000, stdin)){
      if(str != NULL && strstr(str,argv[argc-1]))
	{
	  fprintf(stdout,"%s", str);
	  matchfound = 1;
	}
      }
    }
  else if(quietswitch && !invertswitch)
    {
      
      while(fgets(str,2000,stdin)){
      if(str != NULL && strstr(str,argv[argc-1]))
	{
	  matchfound = 1;
	}
      }
    }
  else if(quietswitch && invertswitch)
    {
      
      while(fgets(str,2000,stdin)){
      if(str != NULL && !strstr(str,argv[argc-1]))
      {
	matchfound = 1;
      }
      }
    }
  else if(invertswitch && !lineswitch)
    {
      while(fgets(str,2000,stdin)){
      if(str != NULL && !strstr(str,argv[argc-1]))
	{
	  fprintf(stdout,"%s", str);
	  matchfound = 1;
	}
      }
    }
  else if(invertswitch && lineswitch)
    {
      
      while(fgets(str, 2000, stdin)){
      if(str != NULL && !strstr(str,argv[argc-1]))
	{
	  fprintf(stdout,"%d: %s",linenumber,str);
	  matchfound = 1;
	}
      linenumber++;
      }
    }
  else if(lineswitch)
    {
     
      while(fgets(str, 2000, stdin))
	{
	  if(strstr(str, argv[argc-1]))
	    {
	  fprintf(stdout,"%d: %s",linenumber, str);
	  matchfound = 1;
	    }
      linenumber++;
	}
    }
  
  free(str);
  if(matchfound)
    {
      return 0;
    }
  return 1;
}


