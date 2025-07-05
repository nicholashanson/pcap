#include <check.h>
#include "parse_filter.h"

START_TEST( test_parse_filter_and )
{
    filter_node* root = parse_filter( "ip and tcp" );
    ck_assert_ptr_nonnull( root );
    ck_assert_int_eq( root->type, NODE_AND );

    ck_assert_ptr_nonnull( root->data.compound.lhs );
    ck_assert_int_eq( root->data.compound.lhs->type, NODE_FILTER );
    ck_assert_str_eq( root->data.compound.lhs->data.filter_text, "ip" );

    ck_assert_ptr_nonnull( root->data.compound.rhs );
    ck_assert_int_eq( root->data.compound.rhs->type, NODE_FILTER );
    ck_assert_str_eq( root->data.compound.rhs->data.filter_text, "tcp" );

    // TODO: free the filter_node tree after test
}
END_TEST

START_TEST( test_parse_filter_or )
{
    filter_node* root = parse_filter( "ip or tcp" );
    ck_assert_ptr_nonnull( root );
    ck_assert_int_eq( root->type, NODE_OR );

    ck_assert_ptr_nonnull( root->data.compound.lhs );
    ck_assert_int_eq( root->data.compound.lhs->type, NODE_FILTER );
    ck_assert_str_eq( root->data.compound.lhs->data.filter_text, "ip" );

    ck_assert_ptr_nonnull( root->data.compound.rhs );
    ck_assert_int_eq( root->data.compound.rhs->type, NODE_FILTER );
    ck_assert_str_eq( root->data.compound.rhs->data.filter_text, "tcp" );

    // TODO: free the filter_node tree after test
}
END_TEST

Suite* parse_filter_suite( void ) {
    Suite* s = suite_create( "ParseFilter" );
    TCase* tc = tcase_create( "Core" );

    tcase_add_test( tc, test_parse_filter_and );
    tcase_add_test( tc, test_parse_filter_or );
    suite_add_tcase( s, tc );
    return s;
}