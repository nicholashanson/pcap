#include "test_packets.h"

const uint8_t pkt_ipv4_tcp[] = {                 
    /* ethernet header */                                           /* ethernet header */
    0x14, 0xf6, 0xd8, 0xaa, 0x69, 0xfa,                             // destination mac address
    0x04, 0x81, 0x9b, 0x17, 0x26, 0x81,                             // source mac address
    0x08, 0x00,                                                     // ether-type 
    /* ipv4 header */                                               /* ipv4 header */
    0x45,                                                           
    0x00,                                                           
    0x01, 0xf9,                                                      
    0x34, 0x64,                                                     
    0x40, 0x00,                                                     
    0x70,                                                           
    0x06,                                                           // protocol 
    0xbe, 0x5e,                                                     
    0x14, 0x2a, 0x41, 0x55,                                         
    0xc0, 0xa8, 0x00, 0x15,                                         
    /* tcp header */                                                /* tcp header */ 
    0x01, 0xbb,                                                     // source port
    0xcd, 0xcc,                                                     // destination port
    0x9f, 0xa5, 0x08, 0x57,                                         // sequence number
    0x1d, 0x42, 0x03, 0xb7,                                         // acknowledgment number
    0x50, 0x19,                                                     // data offset
    0x40, 0x02,                                                     // window size
    0x95, 0x2f,                                                     // checksum
    0x00, 0x00                                                      // urgent pointer
};

const uint8_t pkt_ipv4_udp[]  = {                 
        /* ethernet header */                                           /* ethernet header */
        0x04, 0x81, 0x9b, 0x17, 0x26, 0x81,                             // destination mac address
        0x14, 0xf6, 0xd8, 0xaa, 0x69, 0xfa,                             // source mac address
        0x08, 0x00,                                                     // ether-type
        /* ipv4 header */                                               /* ipv4 header */
        0x45,                                                           // version = 4, header-length = 5 X 4 = 20 bytes
        0x00,                                                           // DSCP and ECN
        0x00, 0x3f,                                                     // total length of packet
        0xdd, 0x2e,                                                     // identification
        0x40, 0x00,                                                     // flags and fragment offset
        0x40,                                                           // time-to-live
        0x11,                                                           // protocol
        0x00, 0x00,                                                     // header checksum
        0xc0, 0xa8, 0x00, 0x15,                                         // source ip address
        0xad, 0xc2, 0x03, 0x49,                                         // destination ip address
        /* udp header */                                                /* udp header */
        0x01, 0xbb,                                                     // source port
        0xce, 0xb9,                                                     // destination port
        0x04, 0xea,                                                     // length
        0x01, 0xb8                                                      // checksum
    };   

const size_t pkt_ipv4_tcp_len = sizeof( pkt_ipv4_tcp );