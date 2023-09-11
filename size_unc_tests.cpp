#define BOOST_TEST_MODULE My test module
#include <boost/test/included/unit_test.hpp>
#include <../DDietTracker/size_unc.h>
#include <boost/test/floating_point_comparison.hpp>

#include <QString>

BOOST_AUTO_TEST_SUITE( size_unc_test )

BOOST_AUTO_TEST_CASE( size_unc_test_compare )
{
    size_unc x = 2;
    size_unc y = 2;
    BOOST_TEST( x==y);
    BOOST_TEST( x==2);
}

BOOST_AUTO_TEST_CASE( size_unc_test_multiply )
{
    size_unc x = {2, 4};
    size_unc y = {3, 4};
    auto r = x*y;
    BOOST_TEST(r == size_unc(6, 14.422205));
}

BOOST_AUTO_TEST_CASE( size_unc_test_divide )
{
    size_unc x = {2, 4};
    size_unc y = {3, 4};
    auto r = x/y;
    BOOST_TEST(r == size_unc(0.666666687, 1.40545678));
}

BOOST_AUTO_TEST_SUITE_END()
