#include "filter.h"

uint32_t run_bpf( const struct sock_filter* prog, size_t prog_len, const uint8_t* pkt, size_t pkt_len ) {
    uint32_t A = 0;
    size_t pc = 0;

    while ( pc < prog_len ) {
        struct sock_filter ins = prog[ pc ];

        switch (ins.code) {
            case BPF_LD | BPF_H | BPF_ABS:
                if ( ins.k > pkt_len - 2 ) return 0;
                A = ( pkt[ ins.k ] << 8) | pkt[ ins.k + 1 ];
                break;

            case 0x06:
                return A;

            default:
                return 0;  
        }

        pc++;
    }

    return 0;
}

struct sock_filter tcp_filter_code[] = {
    { 0x28, 0, 0, 0x0000000c }, // load ether-type
    { 0x15, 0, 5, 0x00000800 }, // check ether-type == ipv4
    { 0x6,  0, 0, 0x00000000 }, // drop if not
    { 0x30, 0, 0, 0x00000017 }, // load ip protocol
    { 0x15, 0, 2, 0x00000006 }, // check if tcp
    { 0x6,  0, 0, 0x00000000 }, // drop if not
    { 0x6,  0, 0, 0x0000ffff }, // accept packet
};