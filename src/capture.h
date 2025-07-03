#ifndef CAPTURE_H
#define CAPTURE_H

#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

int create_raw_socket();

int bind_socket_to_interface( int sockfd, const char* if_name );

#endif