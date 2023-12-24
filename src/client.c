#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#ifndef GIT_COMMIT
#define GIT_COMMIT ""
#endif

int main(int argc, char *argv[]) {
  printf("simpleFtp client %s\n", GIT_COMMIT);
  const sock_req_cli src = {.addr = "0x7f.1", .port = 2121, .type = CONNECT};
  sockaddr_in_t *addr = calloc(1, sizeof(sockaddr_in_t));
  int sfd = sock_request((const sock_req *)&src, addr);
  if (sfd == GEN_FAILURE) {
    return EXIT_FAILURE;
  }
  if (connect(sfd, (const struct sockaddr *)addr, sizeof(sockaddr_in_t)) != 0) {
    perror("connect");
    free(addr);
    return EXIT_FAILURE;
  }
  char buffer[1024] = {0};
  read(sfd, buffer, write(sfd, "HELLO\n", 8));
  printf("%s\n", buffer);
  free(addr);
  return EXIT_SUCCESS;
}
