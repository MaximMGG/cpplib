#include "strbuf.hpp"
#include <stdio.h>


int main() {
  Strbuf sb;

  sb << (char *)"Hello ";
  sb << (char *)"world!";

  sb.replace("!", " Cubaba");
  char *str = sb.toString();
  printf("%s\n", str);
  delete [] str;

  return 0;
}
