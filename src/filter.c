#include "filter.h"

uint32_t run_bpf( const struct sock_filter* prog, size_t prog_len, const uint8_t* pkt, size_t pkt_len ) {
    uint32_t A = 0;
    size_t pc = 0;

    while ( pc < prog_len ) {
        struct sock_filter ins = prog[ pc ];

        switch ( ins.code ) {
            case BPF_LD | BPF_H | BPF_ABS:
                if ( ins.k > pkt_len - 2 ) return 0;
                A = ( pkt[ ins.k ] << 8 ) | pkt[ ins.k + 1 ];
                break;
            case BPF_LD | BPF_B | BPF_ABS:
                if ( ins.k >= pkt_len ) return 0;
                A = pkt[ ins.k ];
                break;
            case BPF_LD | BPF_W | BPF_ABS:
                if ( ins.k > pkt_len - 4 ) return 0;
                A = ( pkt[ ins.k ]     << 24 ) | ( pkt[ ins.k + 1 ] << 16 ) | 
                    ( pkt[ ins.k + 2 ] <<  8 ) | ( pkt[ ins.k + 3 ] );
                break;
            case BPF_JMP | BPF_JEQ | BPF_K:
                if ( A == ins.k ) {
                    if ( pc + ins.jt + 1 >= prog_len ) return 0; 
                    pc += ins.jt + 1;
                } else {
                    if ( pc + ins.jf + 1 >= prog_len ) return 0;  
                    pc += ins.jf + 1;
                }
                continue;
            case BPF_RET | BPF_K:
                return ins.k;
            case BPF_RET | BPF_A:
                return A;

            default:
                return 0;  
        }

        pc++;
    }

    return 0;
}

struct sock_filter ip_filter_code[] = {
    { 0x28, 0, 0, 0x0000000c }, // load ether-type
    { 0x15, 0, 1, 0x00000800 }, // check ether-type == ipv4
    { 0x6,  0, 0, 0x0000ffff }, // accept packet
    { 0x6,  0, 0, 0x00000000 }, // drop packet
};

struct sock_filter tcp_filter_code[] = {
    { 0x28, 0, 0, 0x0000000c }, // load ether-type
    { 0x15, 1, 0, 0x00000800 }, // check ether-type == ipv4
    { 0x6,  0, 0, 0x00000000 }, // drop if not
    { 0x30, 0, 0, 0x00000017 }, // load ip protocol
    { 0x15, 1, 0, 0x00000006 }, // check if tcp
    { 0x6,  0, 0, 0x00000000 }, // drop if not
    { 0x6,  0, 0, 0x0000ffff }, // accept packet
};

const struct sock_filter* compile_filter( const char* filter_name, size_t* out_len ) {
    if ( strcmp( filter_name, "ip" ) == 0 ) {
        if ( out_len ) *out_len = sizeof( ip_filter_code ) / sizeof( ip_filter_code[ 0 ] );
        return ip_filter_code;
    }
    if ( strcmp( filter_name, "tcp" ) == 0 ) {
        if ( out_len ) *out_len = sizeof( tcp_filter_code ) / sizeof( tcp_filter_code[ 0 ] );
        return tcp_filter_code;
    }
    if ( out_len ) *out_len = 0;
    return NULL;
}
