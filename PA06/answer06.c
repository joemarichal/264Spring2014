#include "answer06.h"
#include <stdio.h>
#include <stdlib.h>

void partEO(int, int, int *, int);
void partall(int, int, int *, int);
void partdec(int, int, int *, int);
void partinc(int, int, int *, int);
void parteven(int, int, int *, int);
void partodd(int, int, int *, int);
void partPrime(int, int, int *, int);
void printresults(int *, int);
int prime(int);

int prime(int value)
{
  int prm = 1;
  int i = (value + 1) / 2;
  int ind = 2;
  while(ind <= i)
    {
      if(value % ind == 0)
	{
	  prm = 0;
	}
      ind++;
    }
  return prm;
}

void partitionPrime(int value)
{
  int * partition = malloc(MAXLENGTH * sizeof(int));

  partPrime(value, 2, partition, 0);

  free(partition);
  return;
}

void partPrime(int value, int n, int * partition, int count)
{
  while(n <= value)
    {
      if(n == value)
	{
	  partition[count] = n;
	  printresults(partition, count);
	}
      else
	{
	  partition[count] = n;
	  count++;
	  partPrime(value - n, 2, partition, count);
	}
      while(!prime(++n))
	{
	}
      count--;
    }
  return;
}

void partitionOddAndEven(int value)
{
  int * partition = malloc(MAXLENGTH * sizeof(int));

  partEO(value, 1, partition, 0);
  partEO(value, 2, partition, 0);

  free(partition); 
  return;
}

void partEO(int value, int n, int * partition, int count)
{
  while(n <= value)
    {
      if(n == value)
	{
	  partition[count] = n;
	  printresults(partition, count);
	}
      else
	{
	  partition[count] = n;
	  count++;
	  if(n % 2 == 0)
	    {
	      partEO(value - n, 1, partition, count);
	    }
	  if(n % 2 == 1)
	    {
	     partEO(value - n, 2, partition, count);
	    }
	}
      count--;
      n += 2;
    }
  return;
}

void partitionOdd(int value)
{
  int * partition = malloc(MAXLENGTH * sizeof(int));

  partodd(value, 1, partition, 0);

  free(partition);

  return;
}

void partodd(int value, int n, int * partition, int count)
{

  while(n <= value)
    {
      if(n == value)
	{
	  partition[count] = n;
	  printresults(partition, count);
	}
      else
	{
	  partition[count] = n;
	  count++;
	  partodd(value - n, 1, partition, count);
	}
      count--;
      n = n + 2;
    }
  return;
}

void partitionEven(int value)
{
  int * partition = malloc(MAXLENGTH * sizeof(int));
  if(value % 2 == 0)
    {
      parteven(value, 2, partition, 0);
    }
  free(partition);
  return;
}


void partitionAll(int value)
{
  int * partition = malloc(MAXLENGTH * sizeof(int));
 
  //Send to Recursive Partition Function
  partall(value,1,partition,0);

  free(partition);
  return;
}

void partitionIncreasing(int value)
{
  int * partition = malloc(MAXLENGTH * sizeof(int));
  partinc(value, 1, partition, 0);
  free(partition);
  return;
}

void partitionDecreasing(int value)
{
  int * partition = malloc(MAXLENGTH * sizeof(int));

  partdec(value, value, partition, 0);

  free(partition);
  return;
}


void parteven(int value, int n, int *partition, int count)
{
  while(n <= value)
    {
      if(value == n)
	{
	  partition[count] = n;
	  printresults(partition, count);
	}
      else if((value -  2) > 0)
	{
	  partition[count] = n;
	  count ++;
	  parteven(value - n, 2, partition, count);
	}
	count--;
	n += 2;
    }
  return;
}


void partdec(int value, int n, int * partition, int count)
{

  while(n > 0)
    {
     if((value - n) == 0)
	{
	  partition[count] = n;
	  printresults(partition, count);
	  count++;
	}
      else
	{
	  partition[count] = n;
	  count++;
	  partdec(value - n, n - 1, partition, count);
	}
     count--;
     n--;
    }
  return;
}

void partinc(int value, int n, int * partition, int count)
{
  while(n <= value)
    {
      if(value - (n + 1) >= 0)
      {
	partition[count] = n;
	count++;
	partinc(value - n, 1 + n, partition, count);
      }
      else if((value - n) == 0)
	{
	  partition[count] = n;
	  printresults(partition, count);
	}
      else
	{
	  while((value - n) > 0)
	    {
	      n++;
	    }
	  partition[count] = n;
	  printresults(partition, count);
	}
      count--;
      n++;
    }
  return;
}

void partall(int value, int n, int * partition, int count)
{

  while(n <= value)
    {
      partition[count] = n;

      //If partition value is not equal to value to be partioned, call again
      if(n != value)
	{
	  count += 1;
	  partall(value - n, 1, partition, count);
	}
      //Partition value is equal to value to be partitioned
      else
	{
	  printresults(partition, count);
	}
      n += 1;
      count -= 1;
    }
  return;
}

void printresults(int * partition, int count)
{
  int i = 0;
  while(i <= count)
    {
      if(i == 0 && i != count)
	{
	  printf("= %d + ", partition[i]);
	}
      else if(i != count)
	{
	  printf("%d + ", partition[i]);
	}
      else if(i == count)
	{
	  if(i == 0)
	    {
	      printf("= ");
	    }
	  printf("%d\n", partition[i]);
	}
      i++;
    }
  
  return;
}
