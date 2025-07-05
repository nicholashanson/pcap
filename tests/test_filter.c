#include <check.h>
#include "../src/filter.h"

START_TEST( test_ldh_abs )
{
    struct sock_filter prog[] = {
        { 0x28, 0, 0, 4 },  // BPF_LD | BPF_H | BPF_ABS       
        { 0x16, 0, 0, 0 }        
    };

    ck_assert_int_eq( BPF_LD | BPF_H | BPF_ABS, 0x28 );
    ck_assert_int_eq( BPF_RET | BPF_A, 0x16 );

    uint8_t pkt[] = { 0, 1, 2, 3, 0x12, 0x34 };  
    uint32_t result = run_bpf( prog, 2, pkt, sizeof( pkt ) );

    ck_assert_int_eq( result, 0x1234 );
}
END_TEST

START_TEST( test_ldb_abs )
{
    struct sock_filter prog[] = {
        { 0x30, 0, 0, 4 },   // BPF_LD | BPF_B | BPF_ABS
        { 0x16, 0, 0, 0 }    
    };

    ck_assert_int_eq( BPF_LD | BPF_B | BPF_ABS, 0x30 );

    uint8_t pkt[] = { 0, 1, 2, 3, 0xab, 0xcd };
    uint32_t result = run_bpf( prog, 2, pkt, sizeof( pkt ) );

    ck_assert_int_eq( result, 0xab );
}
END_TEST

START_TEST( test_ldw_abs )
{
    struct sock_filter prog[] = {
        { 0x20, 0, 0, 0 },  // BPF_LD | BPF_W | BPF_ABS
        { 0x16, 0, 0, 0 }
    };

    ck_assert_int_eq( BPF_LD | BPF_W | BPF_ABS, 0x20 );

    uint8_t pkt[] = { 0x01, 0x23, 0x45, 0x67 };
    uint32_t result = run_bpf( prog, 2, pkt, sizeof( pkt ) );

    ck_assert_int_eq( result, 0x01234567 );
}
END_TEST

START_TEST( test_jump_eq_k_true )
{
    struct sock_filter prog[] = {
        { 0x30, 0, 0, 0x00000017 },    
        { 0x15, 1, 0, 0x00000006 },    
        { 0x6,  0, 0, 0x00000000 },   
        { 0x6,  0, 0, 0x0000ffff },    
    };

    ck_assert_int_eq( BPF_JMP | BPF_JEQ | BPF_K, 0x15 );

    uint8_t pkt[ 64 ] = { 0 };
    pkt[ 23 ] = 0x06;

    uint32_t result = run_bpf( prog, 4, pkt, sizeof( pkt ) );
    ck_assert_int_eq( result, 0x0000ffff );
}
END_TEST

Suite *filter_suite( void ) {
    Suite *s = suite_create( "Filter" );
    TCase *tc = tcase_create( "RawSocket" );

    tcase_add_test( tc, test_ldh_abs );
    tcase_add_test( tc, test_ldb_abs );
    tcase_add_test( tc, test_ldw_abs );
    tcase_add_test( tc, test_jump_eq_k_true );
    suite_add_tcase( s, tc );

    return s;
}


