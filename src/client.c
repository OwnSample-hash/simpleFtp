#include <stdio.h>
#include <stdlib.h>

#ifndef GIT_COMMIT
#define GIT_COMMIT ""
#endif

int main(int argc, char *argv[]) {
  printf("simpleFtp server %s\n", GIT_COMMIT);
  return EXIT_SUCCESS;
}
