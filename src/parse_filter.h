#ifndef PARSE_FILTER_H
#define PARSE_FILTER_H

#define _POSIX_C_SOURCE 200809L
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NODE_AND,
    NODE_OR,
    NODE_NOT,  
    NODE_FILTER
} node_type;

typedef struct filter_node {
    node_type type;
    union {
        struct {
            struct filter_node* lhs;
            struct filter_node* rhs;
        } compound;  

        struct filter_node* child;  

        const char* filter_text;  
    } data;
} filter_node;

filter_node* parse_filter( const char* filter );

#endif // PARSE_FILTER_H

