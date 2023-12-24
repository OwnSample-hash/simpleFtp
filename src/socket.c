#include "socket.h"

sock_status sock_request(const sock_req *request, sockaddr_in_t *out) {
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd < 0) {
    perror("sock_request,socket");
    return GEN_FAILURE;
  }
  if (request->type == LISTEN) {
    sock_req_ser *ser_req = (sock_req_ser *)request;
    struct in_addr addr;
    inet_aton(ser_req->addr, &addr);
    struct sockaddr_in sin = {.sin_family = AF_INET,
                              .sin_port = htons(ser_req->port),
                              .sin_addr = addr.s_addr};
    if (bind(sfd, (const struct sockaddr *)&sin, sizeof(sin)) != 0) {
      perror("sock_request,bind");
      return GEN_FAILURE;
    }
    listen(sfd, ser_req->listen);
    return sfd;
  } else if (request->type == CONNECT) {
    sock_req_cli *cli_req = (sock_req_cli *)request;
    struct in_addr addr;
    inet_aton(cli_req->addr, &addr);
    *out = (sockaddr_in_t){.sin_family = AF_INET,
                           .sin_port = htons(cli_req->port),
                           .sin_addr = addr.s_addr};
    return sfd;
  } else
    return EMPTY_TYPE;
  return GEN_FAILURE;
}
