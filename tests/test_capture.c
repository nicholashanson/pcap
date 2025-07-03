#include <check.h>
#include "../src/capture.h"

START_TEST( test_create_raw_socket_should_succeed )
{
    int fd = create_raw_socket();
    ck_assert_int_ge( fd, 0 );
}
END_TEST

START_TEST( test_bind_socket_to_loopback_should_succeed )
{
    int sockfd = create_raw_socket();
    int result = bind_socket_to_interface( sockfd, "lo" );
    ck_assert_int_eq( result, 0 );

    close( sockfd );
}
END_TEST

Suite *capture_suite( void ) {
    Suite *s = suite_create( "Capture" );
    TCase *tc = tcase_create( "RawSocket" );

    tcase_add_test( tc, test_create_raw_socket_should_succeed );
    tcase_add_test( tc, test_bind_socket_to_loopback_should_succeed );
    suite_add_tcase( s, tc );

    return s;
}