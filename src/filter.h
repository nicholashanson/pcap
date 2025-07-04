#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>
#include <stddef.h>

enum bpf_class {
    BPF_LD = 0x00
};

enum bpf_size {
    BPF_H = 0x08
};

enum bpf_mode {
    BPF_ABS = 0x20
};

struct sock_filter {
    uint16_t code;
    uint8_t jt;
    uint8_t jf;
    uint32_t k;
};

uint32_t run_bpf( const struct sock_filter* prog, size_t prog_len, const uint8_t* pkt, size_t pkt_len );

#endif