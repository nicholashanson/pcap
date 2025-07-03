#include "capture.h"

int create_raw_socket() {

    int sock = socket( AF_PACKET, SOCK_RAW, htons( ETH_P_ALL ) );

    if ( sock < 0 ) {
        perror( "socket" );
    }
    return sock;
}

int bind_socket_to_interface( int sockfd, const char* if_name ) {
    struct sockaddr_ll sll;
    memset( &sll, 0, sizeof( sll ) );

    int if_index = if_nametoindex( if_name );
    if ( if_index == 0 )
        return -1;

    sll.sll_family = AF_PACKET;
    sll.sll_protocol = htons( ETH_P_ALL );
    sll.sll_ifindex = ifindex;

    return bind( sockfd, ( struct sockaddr * )&sll, sizeof( sll ) );
}