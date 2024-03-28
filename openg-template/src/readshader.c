
#include "headers/openglutils.h"

char *readShader (char *fileName)
{
  FILE *file = fopen(fileName, "r");
  char *buffer = NULL;
  if (file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(size);
    if (fread(buffer, 1, size, file) != size) {
      return NULL;
    }
    fclose(file);
  }
  return buffer;
}

