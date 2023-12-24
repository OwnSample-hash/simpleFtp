#ifndef _SIMPLE_SOCKET
#define _SIMPLE_SOCKET

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef enum { SUCCESS, GEN_FAILURE, EMPTY_TYPE } sock_status;
static int sock_erno = SUCCESS;

typedef enum { LISTEN, CONNECT } sock_type;

typedef struct __socket_request {
  sock_type type;
  char data[sizeof(int) * 2 + sizeof(char *)];
} sock_req;

typedef struct __socket_request_server {
  sock_type type;
  const char *addr;
  const int port;
  const int listen;
} sock_req_ser;

typedef struct __socket_request_client {
  sock_type type;
  const char *addr;
  const int port;
  char pad[4];
} sock_req_cli;

typedef struct sockaddr_in sockaddr_in_t;

// request: struct that contains inof abt the socket creation
// out is needed for socket type CONNECT
sock_status sock_request(const sock_req *request, sockaddr_in_t *out);

#endif
