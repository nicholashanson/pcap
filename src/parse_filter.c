#include "parse_filter.h"

static filter_node* create_filter_node( const char* filter_text ) {
    filter_node* node = malloc( sizeof( filter_node ) );
    if ( !node ) return NULL;
    node->type = NODE_FILTER;
    node->data.filter_text = strdup( filter_text );
    return node;
}

filter_node* parse_filter( const char* filter ) {
	filter_node* node = malloc( sizeof( filter_node ) );
    if ( !node ) return NULL;

    if ( strstr( filter, " and " ) ) {
    	const char* and_ptr = strstr( filter, " and " );
        size_t lhs_len = and_ptr - filter;
        size_t rhs_len = strlen( filter ) - lhs_len - 5;

        char* lhs_str = malloc( lhs_len + 1 );
        char* rhs_str = malloc( rhs_len + 1 );
        if ( !lhs_str || !rhs_str ) return NULL;

        strncpy( lhs_str, filter, lhs_len );
        lhs_str[ lhs_len ] = '\0';
        strncpy( rhs_str, and_ptr + 5, rhs_len );
        rhs_str[ rhs_len ] = '\0';

        node->type = NODE_AND;
        node->data.compound.lhs = create_filter_node( lhs_str );  
        node->data.compound.rhs = create_filter_node( rhs_str ); 

        free( lhs_str );
        free( rhs_str );

        return node;
    }

    if ( strstr( filter, " or " ) ) {

        const char* or_ptr = strstr( filter, " or " );
        size_t lhs_len = or_ptr - filter;
        size_t rhs_len = strlen( filter ) - lhs_len - 4;

        char* lhs_str = malloc( lhs_len + 1 );
        char* rhs_str = malloc( rhs_len + 1 );
        if (!lhs_str || !rhs_str) return NULL;

        strncpy( lhs_str, filter, lhs_len );
        lhs_str[ lhs_len ] = '\0';
        strncpy( rhs_str, or_ptr + 4, rhs_len );
        rhs_str[ rhs_len ] = '\0';

        node->type = NODE_OR;
        node->data.compound.lhs = create_filter_node( lhs_str );
        node->data.compound.rhs = create_filter_node( rhs_str );

        free( lhs_str );
        free( rhs_str );

        return node;
    }

    node->type = NODE_FILTER;
    node->data.filter_text = strdup( filter );
    return node;
}

