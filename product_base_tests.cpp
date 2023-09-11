
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../DDietTracker/allproductsbase.h"
#include <boost/test/floating_point_comparison.hpp>
#include "../DDietTracker/ddt.h"
#include <QString>

BOOST_AUTO_TEST_SUITE( product_base )

BOOST_AUTO_TEST_CASE( singleton_features )
{
    Product product2("Orzechy");
    {
    auto products = AllProductsBase::GetInstance();
    Product product1("Marmolada");

    products->AddProduct(product1);
    products->AddProduct(product2);

    products->GetProduct("Marmolada")._kcalories = {500, 2};
    }

    auto products = AllProductsBase::GetInstance();
    BOOST_CHECK_CLOSE(products->GetProduct("Marmolada")._kcalories.value().GetValue(), 500.0, 0.001);
    BOOST_CHECK_CLOSE(products->GetProduct("Marmolada")._kcalories.value().GetUncertainty(), 2, 0.001);
    BOOST_CHECK_THROW(products->AddProduct(product2), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
