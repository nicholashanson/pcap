#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "parse_filter.h"

#ifndef WIN32
#include <linux/filter.h>
#endif

#ifdef WIN32
enum bpf_class {
	BPF_LD = 0x00,
	BPF_JMP = 0x05,
	BPF_RET  = 0x06
};

enum bpf_size {
	BPF_W = 0x00,
	BPF_H = 0x08,
	BPF_B = 0x10
};

enum bpf_mode {
	BPF_K   = 0x00,
	BPF_ABS = 0x20
};

enum bpf_jump {
	BPF_JEQ 0x10
};

enum bpf_src {
	BPF_A = 0x10  
};

struct sock_filter {
    uint16_t code;
    uint8_t jt;
    uint8_t jf;
    uint32_t k;
};
#endif

extern struct sock_filter tcp_filter_code[];

uint32_t run_bpf( const struct sock_filter* prog, size_t prog_len, const uint8_t* pkt, size_t pkt_len );

const struct sock_filter* compile_filter( const char* filter_name, size_t* out_len );

#endif