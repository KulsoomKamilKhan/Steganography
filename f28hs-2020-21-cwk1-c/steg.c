#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
  Stores the RGB values of a pixel
*/

typedef struct Pixel
{
  int red;
  int green;
  int blue;
} Pixel;

typedef struct LL
{
  char *nodeVal;
  struct LL *next;
} LL;

/*
  Stores the contents of a PPM file
*/

typedef struct PPM
{
  int width, height, maxValue;
  struct Pixel *pixels;
  char buff[4];
  LL *comment;
} PPM;

/*
  Returns the PPM struct from the file fd
*/

PPM *getPPM(FILE *fd)
{
  PPM *ppm = (PPM *)malloc(sizeof(PPM));

  //checks if the file is in P3 format
  fscanf(fd, "%s", ppm->buff);
  if (strcmp(ppm->buff, "P3") != 0)
  {
    fprintf(stderr, "steg: Image is not in ppm format \n");
    exit(0);
  }

  char c = getc(fd);
  ppm->comment = (LL *)malloc(sizeof(LL));
  LL *tmp = ppm->comment;

  while ((c = getc(fd)) == '#')
  {
    fseek(fd, -1, SEEK_CUR);
    char txt[100];
    fgets(txt, 100, fd);
    tmp->nodeVal = malloc(strnlen(txt, 100)+1);  //more space for trailing NULL byte
    strcpy(tmp->nodeVal, txt);
    tmp->next = (LL *)malloc(sizeof(LL));
    tmp = tmp->next;
    tmp->next = NULL;
  }
  //prints width and height of ppm images
  fseek(fd, -1, SEEK_CUR);
  fscanf(fd,"%d", &ppm->width);
  fscanf(fd,"%d", &ppm->height);
  fscanf(fd,"%d", &ppm->maxValue);

  ppm->pixels = (Pixel *)malloc(ppm->height * ppm->width * sizeof(Pixel));

  int n = 0;
  int i = 0;
  //prints max rgb values
  while (i < ppm->height * ppm->width)
  {
    n = fscanf(fd, "%d", &ppm->pixels[i].red);
    n = fscanf(fd, "%d", &ppm->pixels[i].green);
    n = fscanf(fd, "%d", &ppm->pixels[i].blue);
    i += 1;
  }

  return ppm;
}

/*
  Prints a PPM struct in the format of a PPM file
*/

void showPPM(PPM *ppm)
{
  printf("%s\n", ppm->buff); //print P3 format

  //print comments
  LL *n = ppm->comment;

  while (n->next != NULL)
  {
    printf("%s\n", n->nodeVal);
    n = n->next;
  }

  //print width, height and maxValue
  printf("%d %d\n %d\n", ppm->width, ppm->height, ppm->maxValue);

  //print the array containing the pixels
  int j;
  for (j = 0; j < ppm->height * ppm->width; ++j)
  {
    printf("%d %d %d\n", ppm->pixels[j].red, ppm->pixels[j].green, ppm->pixels[j].blue);
  }
  return;
}

/*
  Loads a file and returns it
  Prints error message and returns NULL if file can't be found or isn't a valid PPM

*/

PPM *loadPPMFromFile(char *filename)
{
  FILE *file;
  file = fopen(filename, "r+");

  if (file != NULL)
  {
    PPM *ppm;
    ppm = getPPM(file);

    if (ppm == NULL)
    {
      fprintf(stderr, "steg: File not in ppm format: '%s'.\n", filename);
      return NULL;
    }

    fclose(file);
    return ppm;
  }
  else
  {
    fprintf(stderr, "steg: Unable to open input file: '%s'.\n", filename);
    return NULL;
  }
}

/*
  Encodes text into red field of PPM
  Returns the encoded PPM
*/

PPM *encode(char *text, PPM *i)
{
  int k, r;
  int length = strlen(text);    //size of message
  int psize = i->width * i->height;  //number of pixels

  if (length > psize)
  {
    fprintf(stderr, "Number of pixels is not enough to hold image \n");
    exit(0);
  }

  //calculate pixels by rows and columns
  int position = 0;
  for (k = 0; k < length; k++)
  {
    r = (rand() % (psize / length)) + 1;  //generate random no.s
    position += r;
    while (i->pixels[position].red == text[k])  //replace random no.s with ASCII chars 
    {   
      position++;
    }
    i->pixels[position].red = text[k];
  }
  return i;
}

/*
  Compares 2 PPM structs and decodes the message hidden within
  Returns the decoded message if the images have the same dimensions
  Returns NULL otherwise

*/

char *decode(PPM *i1, PPM *i2)
{
  char *decodedMsg;

  int pixelCount = i2->height * i2->width;
  int *temp = malloc(pixelCount * sizeof(int));  //allocate a temporary memeory space for decoding

  int j = 0;
  int txtlen = 0;

  while (j < pixelCount)  //loop until all messages are decoded from ascii value
  {
    if (i1->pixels[j].red != i2->pixels[j].red)   //if they are different, convert to character
    {
      temp[txtlen] = i2->pixels[j].red;
      txtlen++;
    }
    j++;
  }
  decodedMsg = malloc(txtlen * sizeof(char));
  
  j = 0;
  while (j < txtlen)
  {
    decodedMsg[j] = temp[j];    //store the decoded text in decodedMsg variable
    j++;
  }
  decodedMsg[j] = '\0';
  return decodedMsg;
}



int main(int argc, char *argv[])
{
  switch (argc)
  {
  case 2:
    fprintf(stderr, "Unrecognised or incomplete command line.\n");
    break;

  case 3:
    if (strcmp(argv[1], "e") == 0)
    {
      //Argument "e" - encode PPM
      PPM *ppm = loadPPMFromFile(argv[2]);
      /*Check that PPM is valid; continue if it is, exit otherwise */

      if (ppm != NULL)
      {
        PPM *encodedPPM;

        char *text;
        text = malloc(sizeof(char) * 254);

        fprintf(stderr, "Enter message to encode: ");
        fgets(text, 254, stdin);

        encodedPPM = encode(text, ppm); /* TODO: encode the ppm with the text and assign to encodedPPM */

        /*Check that no error occured*/

        if (encodedPPM == NULL)
        {
          return EXIT_FAILURE;
        }
        else
        {
          fprintf(stderr, "Successfully encoded image \n"); /* TODO: print a confirmation that encoding was successful */
          showPPM(encodedPPM);                              /* TODO: print the PPM to standard output with showPPM */
          return EXIT_SUCCESS;
        }
      }
      else
      {
        return EXIT_FAILURE;
      }
    }
    else
    {
      fprintf(stderr, "Unrecognised or incomplete command line.\n");
      return EXIT_FAILURE;
    }
    break;
  case 4:
    if (strcmp(argv[1], "d") == 0)
    { //Argument "d" - decode PPM
      PPM *comparisonPPM;
      PPM *encodedPPM;
      comparisonPPM = loadPPMFromFile(argv[2]); /* TODO: get comparison file filename from argv, load it with
         loadPPMFromFile then assign to comparisonPPM */

      encodedPPM = loadPPMFromFile(argv[3]); /* TODO: get encoded file filename from argv, load it with
         loadPPMFromFile then assign to encodedPPM */
      /*Check both PPMs are valid; continue if so, exit otherwise */

      if (comparisonPPM != NULL && encodedPPM != NULL)
      {
        char *decodedMsg;
        decodedMsg = decode(comparisonPPM, encodedPPM); /* TODO: decode the encodedPPM with the comparisonPPM and assign to decodedMsg */
        /*Check that the message has been decoded*/
        if (decodedMsg != NULL)
        {
          fprintf(stderr, "Successfully decoded image \n"); /* TODO: print a confirmation message that the message was decoded */
          fprintf(stderr, "Decoded message:\n");
          fprintf(stderr, "%s \n", decodedMsg); /* TODO: print the decoded message */

          return EXIT_SUCCESS;
        }
        else
        {
          return EXIT_FAILURE;
        }
      }
      else
      {
        return EXIT_FAILURE;
      }
    }
    else
    {
      fprintf(stderr, "Unrecognised or incomplete command line.\n\n");
      return EXIT_FAILURE;
    }
    break;

  default:
    fprintf(stderr, "Unrecognised or incomplete command line.\n\n");
    return EXIT_FAILURE;
  }
}