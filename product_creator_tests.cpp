
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "../DDietTracker/productcreator.h"
BOOST_AUTO_TEST_SUITE( product_creator )

BOOST_AUTO_TEST_CASE( missing_cannot_calculate_test )
{
    ProductCreator creator;
    creator.SetName("Wołowina");
    creator.SetQuantity(500);
    creator.SetFatsPerQuantity(50);
    BOOST_REQUIRE_THROW(creator.CalculateMissing(), std::bad_optional_access);
}

BOOST_AUTO_TEST_CASE( missing_can_calculate_test )
{
    ProductCreator creator;
    creator.SetName("Wołowina");
    creator.SetQuantity(500);
    creator.SetThreeMacros(50, 50, 50);
    creator.CalculateMissing();
    BOOST_CHECK_CLOSE(creator.Result()._kcalories.value().GetValue(), 800.0, 1e-4);
}



BOOST_AUTO_TEST_SUITE_END()
