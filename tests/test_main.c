#include <check.h>

Suite *capture_suite( void );
Suite *filter_suite( void );

int main( void ) {
    int failed = 0;

    SRunner *sr = srunner_create( capture_suite() );
    srunner_add_suite( sr, filter_suite() );

    srunner_run_all( sr, CK_NORMAL );
    failed = srunner_ntests_failed( sr );
    srunner_free( sr );

    return ( failed == 0 ) ? 0 : 1;
}