#include "socket.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef GIT_COMMIT
#define GIT_COMMIT ""
#endif

int main(int argc, char *argv[]) {
  printf("simpleFtp server %s\n", GIT_COMMIT);
  const sock_req_ser srs = {
      .addr = "0x7f.1", .port = 2121, .type = LISTEN, .listen = 1};
  sockaddr_in_t *addr = calloc(1, sizeof(sockaddr_in_t));
  int sfd = sock_request((const sock_req *)&srs, addr);
  if (sfd == GEN_FAILURE) {
    free(addr);
    return EXIT_FAILURE;
  }
  printf("Serving on %d", addr->sin_port);
  int cfd = accept(sfd, NULL, NULL);
  char buffer[1024] = {0};
  write(cfd, buffer, read(cfd, buffer, 1024));
  printf("%s\n", buffer);
  free(addr);
  return EXIT_SUCCESS;
}
