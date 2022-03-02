#include "SocketUtil.h"

#include <unistd.h>
#include <assert.h>
#include <string.h>

#include <iostream>

using std::cerr;
using std::endl;
#define BUF 256

// Performs a DNS lookup with hostname "name" and no service.
// Initializes the port of the first resulting struct sockaddr to
// "port" and returns it via the output parameter "ret_addr". The
// returned socket address may be IPv4 or IPv6.
// Returns the length of the socket address through output parameter
// "ret_addrlen".
//
// On failure, returns false.  On success, returns true.
bool LookupName(char* name,
                unsigned short port,
                struct sockaddr_storage* ret_addr,
                size_t* ret_addrlen) {
  // TODO: fill in this function
  int retval;
  struct addrinfo hints, *results;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if ((retval = getaddrinfo(name, nullptr, &hints, &results)) != 0) {
    std::cerr << "getaddrinfo failed: ";
    // gai_strerror is defined in netdb.h and returns a
    // string describing getaddrinfo() error value.
    std::cerr << gai_strerror(retval) << std::endl;
    return false;
  }
  if (results->ai_family == AF_INET) {
    struct sockaddr_in* v4addr =
              reinterpret_cast<struct sockaddr_in*>(results->ai_addr);
    v4addr->sin_port = htons(port);
  } else if (results->ai_family == AF_INET6) {
    struct sockaddr_in6* v6addr =
              reinterpret_cast<struct sockaddr_in6* >(results->ai_addr);
    v6addr->sin6_port = htons(port);
  } else {
    std::cerr << "  unknown address family " << results->ai_family << std::endl;
    freeaddrinfo(results);
    return false;
  }
  assert(results!=nullptr);
  memcpy(ret_addr, results->ai_addr, results->ai_addrlen);
  *ret_addrlen = results->ai_addrlen;
  freeaddrinfo(results);
  return true;

  
}
// Creates a socket and connects to the remote host and port specified
// by "addr" and "addrlen" via TCP. Returns the file descriptor of the
// connected socket through the output parameter "ret_fd".
//
// On failure, returns false.  On success, returns true.
bool Connect(const struct sockaddr_storage& addr,
             const size_t& addrlen,
             int* ret_fd) {
  // TODO: fill in this function
 
  int socket_fd = socket(addr.ss_family, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    std::cerr << "socket() failed: " << strerror(errno) << std::endl;
    return false;
  }
  int res = connect(socket_fd,
                    const_cast<sockaddr*>(reinterpret_cast<const sockaddr*>(&addr)),
                    addrlen);
  if (res == -1) {
    std::cerr << "connect() failed: " << strerror(errno) << std::endl;
  }
  close(*ret_fd);
  return true;
}
// A wrapper around "read" that shields the caller from dealing
// with the ugly issues of partial reads, EINTR, EAGAIN, and so
// on.
//
// Attempts to read "readlen" bytes from the file descriptor fd
// into the buffer "buf".  Returns the number of bytes actually
// read.  On fatal error, returns -1.  If EOF is hit and no
// bytes have been read, returns 0.  Might read fewer bytes
// than requested (for instance, if we are close to the end of
// the file).
// You may assume that buf has enough space for writelen bytes.

int WrappedRead(int fd, unsigned char* buf, int readlen) {
  // TODO: fill in this function
  int res;
  while (1) {
    res = read(fd, buf, readlen);
    if (res == 0) {
      std::cerr << "socket closed prematurely" << std::endl;
      close(fd);
      return -1;
    }
    if (res == -1) {
      if (errno == EINTR)
        continue;
      std::cerr << "socket read failure: " << strerror(errno) << std::endl;
      close(fd);
      return -1;
    }
    break;
  }
  return res;
}
// A wrapper around "write" that shields the caller from dealing
// with the ugly issues of partial writes, EINTR, EAGAIN, and so
// on.
//
// Writes "writelen" bytes to the file descriptor fd from
// the buffer "buf".  Blocks the caller until either writelen
// bytes have been written, or an error is encountered.  Returns
// the total number of bytes written. If this number is less
// than writelen, it's because some fatal error was encountered,
// like the connection being dropped.
// You may assume that buf has enough space for writelen bytes.

int WrappedWrite(int fd, unsigned char* buf, int writelen) {
  // TODO: fill in this function
  int written = 0;
  int wres = 0;
  while (written < writelen) {
    wres = write(fd, buf+written, writelen - written);
    if (wres == 0) {
      std::cerr << "socket closed prematurely" << std::endl;
      close(fd);
      return -1;
    }
    if (wres == -1) {
      if (errno == EINTR)
        continue;
      std::cerr << "socket write failure: " << strerror(errno) << std::endl;
      close(fd);
      return -1;
    }
    break;
    written += wres;
  }

  // Clean up.
  close(fd);
  return written;
}
