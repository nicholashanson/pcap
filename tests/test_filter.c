#include <check.h>
#include "../src/filter.h"

START_TEST( test_ldh_abs )
{
    struct sock_filter prog[] = {
        { 0x28, 0, 0, 4 },  // BPF_LD | BPF_H | BPF_ABS       
        { 0x06, 0, 0, 0 }        
    };

    uint8_t pkt[] = { 0, 1, 2, 3, 0x12, 0x34 };  
    uint32_t result = run_bpf( prog, 2, pkt, sizeof( pkt ) );

    ck_assert_int_eq( result, 0x1234 );
}
END_TEST

START_TEST( test_ldb_abs )
{
    struct sock_filter prog[] = {
        { 0x30, 0, 0, 4 },   // BPF_LD | BPF_B | BPF_ABS
        { 0x06, 0, 0, 0 }    
    };

    uint8_t pkt[] = { 0, 1, 2, 3, 0xab, 0xcd };
    uint32_t result = run_bpf( prog, 2, pkt, sizeof( pkt ) );

    ck_assert_int_eq( result, 0xab );
}
END_TEST

Suite *filter_suite( void ) {
    Suite *s = suite_create( "Filter" );
    TCase *tc = tcase_create( "RawSocket" );

    tcase_add_test( tc, test_ldh_abs );
    tcase_add_test( tc, test_ldb_abs );
    suite_add_tcase( s, tc );

    return s;
}


