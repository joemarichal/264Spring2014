#include "answer05.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Image * Image_load(const char * filename)
{

  FILE * fp = fopen(filename, "r");
  ImageHeader header;
  int read;
  Image * im = NULL;
  Image * imNull = NULL;
  //Check if file is valid
  if(fp == NULL)
    {
      return im;
    }

  //Check for Validity of Magic Number
  read = fread(&header,sizeof(ImageHeader),1,fp);

  if(read == 0)
    {
      fclose(fp);
      return im;
    }
 
  

  if(header.magic_number != ECE264_IMAGE_MAGIC_NUMBER)
    {
      fclose(fp);
      return im;
    }


 
 
 
  if(header.width == 0 || header.height == 0)
  {
    fclose(fp);
    return im;
  }
 

 
 
  if(header.comment_len == 0)
    {
      fclose(fp);
      return im;
    }

  //Read Comment and Check
 
  char * comment = malloc(header.comment_len * sizeof(char));
  if(comment == NULL)
    {
      fclose(fp);
      return im;
    }

  fread(comment, header.comment_len, 1, fp);
  if(comment[header.comment_len - 1] != '\0')
    {
      fclose(fp);
      free(comment);
      return im;
    }

 
 //Read Image
  size_t num_bytes;
  num_bytes = sizeof(uint8_t) * header.width * header.height;
  im = malloc(sizeof(Image));
  im->height=header.height;
  im->width=header.width;
  im->comment = malloc(sizeof(char) * (strlen(comment) + 1));
  strcpy(im->comment,comment);
  im->data = malloc(num_bytes);

  if(im->data == NULL)
    {
      free(im->comment);
      free(im);
      free(comment);
      fclose(fp);
      return imNull;
    }
 

  read = fread(im->data, sizeof(uint8_t), num_bytes,fp);
 
 if(read != num_bytes)
    {
      free(im->data);
      free(im->comment);
      free(im);
      free(comment);
      fclose(fp);
      return imNull;
    }

 
  uint8_t byte;
 
  
  read = fread(&byte, sizeof(uint8_t), 1, fp);
 

  if(read != 0)
    {
      free(im->data);
      free(im->comment);
      free(im);
      free(comment);
      fclose(fp);
      return imNull;
    }


  free(comment);
  fclose(fp);
  return im;
}


void linearNormalization(int width, int height, uint8_t * intensity)
{
  int i;
  uint8_t min = intensity[0];
  uint8_t max = intensity[0];

  //Find Min and Max
  for(i = 1; i < width * height; i++)
    {
      if(intensity[i] < min)
	{
	  min = intensity[i];
	}
      if(intensity[i] > max)
	{
	  max = intensity[i];
	}
    }
 
  //Normalize
  for(i = 0; i < width * height; i++)
    {
      intensity[i] = (intensity[i] - min) * 255 / (max - min);
    }


  return;
}

void Image_free(Image * image)
{

  free(image->data);
  free(image->comment);
  free(image);

  return;
}

int Image_save(const char * filename, Image * image)
{
  FILE * fp = fopen(filename,"w");
  ImageHeader header;
  header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
  header.width = image->width;
  header.height = image->height;
  header.comment_len = strlen(image->comment) + 1;

  fwrite(&header, sizeof(ImageHeader),1,fp);
  fprintf(fp,"%s%c",image->comment,'\0');
  int i;

  for(i = 0; i < image->width * image->height; i++)
    {
      fprintf(fp,"%c",image->data[i]);
    }

  fclose(fp);
  return 1;
}


