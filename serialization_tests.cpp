
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "jsoncpp/json/json.h"
#include <fstream>
#include <QString>
#include "../DDietTracker/product.h"
#include "../DDietTracker/productserializer.h"
#include "../DDietTracker/productdeserializer.h"
#include "../DDietTracker/allproductsbase.h"
#include "../DDietTracker/apbaseserializer.h"
#include "../DDietTracker/apbasedeserializer.h"
#include "../DDietTracker/eatenproduct.h"
#include "../DDietTracker/eatenproductserializer.h"
#include "../DDietTracker/eatenproductdeserializer.h"
#include "../DDietTracker/eatenday.h"
#include "../DDietTracker/eatendayserializer.h"
#include "../DDietTracker/eatendaydeserializer.h"



//#include "../DDietTracker/size_unc.h"

BOOST_AUTO_TEST_SUITE( serialization_tests )

BOOST_AUTO_TEST_CASE( json_root_test )
{
    Json::Value root;
    root[QString("kaczka").toStdString()] = QString("dziwaczka").toStdString();
    root[QString("małpka").toStdString()] = QString("gorzałka").toStdString();
    Json::Value root2;
    root2["rymy"] = root;

    std::ofstream file("json_root_test.json");
    file << root2;
    file.close();
    Json::Value root3;
    std::ifstream file2("json_root_test.json");
    file2 >> root3;
    BOOST_TEST(root3["rymy"]["małpka"] == "gorzałka");
    file2.close();
}

BOOST_AUTO_TEST_CASE( product_test )
{
    //Product Initialization
    Product water;
    water._fats = 3;
    water._carbons = size_unc(3, 2);
    water._productCategory = ProductCategory("Drink");

    //Product Serialization
    Json::Value root;
    ProductSerializer serializer(root);
    serializer.ObjectToRoot(water);
    std::ofstream file("product_test.json");
    file << root;
    file.close();

    //Product Deserialization
    std::ifstream file2("product_test.json");
    Json::Value root2;
    Product water2;
    ProductDeserializer deserializer(root2);
    deserializer.FileToRoot(file2);
    deserializer.RootToObject(water2);
    file2.close();


    BOOST_TEST(water2 == water);
}

BOOST_AUTO_TEST_CASE( product_base_test )
{
    Product product1("Marmolada");
    Product product2("Orzechy");
    auto products = AllProductsBase::GetInstance();
    Product product3("Ćżąłgrądź");

    product1._carbons={500, 20};
    product2._kcalories={5300, 20};
    product3._fats={9, 2};

    products->AddProduct(product1);
    products->AddProduct(product2);
    products->AddProduct(product3);

    //Product Base Serialization
    Json::Value root;
    APBaseSerializer apbkserializer(root);
    apbkserializer.ObjectToRoot(products);
    std::ofstream file("product_base_test.json");
    file << root;
    file.close();

    //Product Base Deserialization
    products->ClearBase();
    std::ifstream file2("product_base_test.json");
    Json::Value root2;
    APBaseDeserializer deserializer(root2);
    deserializer.FileToRoot(file2);
    deserializer.RootToObject(products);
    file2.close();

    BOOST_TEST(products->GetProduct("Marmolada") == product1);
    BOOST_TEST(products->GetProduct("Orzechy") == product2);
    BOOST_TEST(products->GetProduct("Ćżąłgrądź") == product3);
    products->ClearBase();
}

BOOST_AUTO_TEST_CASE( Eatenproduct_test )
{
    Product product("Marmolada");

    product._carbons={500, 20};
    product._kcalories={5300, 20};
    product._fats={9, 2};


    EatenProduct eatenProduct(product);
    eatenProduct.SetDate(2023, 9, 4);
    eatenProduct.SetTime(15, 58);

    //Eaten Product Serialization
    Json::Value root;
    EatenProductSerializer eatenProductSerializer(root);
    eatenProductSerializer.ObjectToRoot(eatenProduct);
    std::ofstream file("eaten_product_test.json");
    file << root;
    file.close();

    //Eaten Product Deserialization
    EatenProduct eatenProduct2;
    std::ifstream file2("eaten_product_test.json");
    Json::Value root2;
    EatenProductDeserializer deserializer(root2);
    deserializer.FileToRoot(file2);
    deserializer.RootToObject(eatenProduct2);
    file2.close();

    BOOST_TEST(eatenProduct2 == eatenProduct);

}

BOOST_AUTO_TEST_CASE( EatenDay_test )
{
    EatenDay day;
    Product product1("Marmolada");
    Product product2("Orzechy");
    Product product3("Ćżąłgrądź");

    product1._kcalories={500, 20};
    product2._kcalories={5300, 20};
    product3._kcalories={9, 2};

    EatenProduct eaten1 = EatenProduct(product1, 400);
    EatenProduct eaten2 = EatenProduct(product2, 123);
    EatenProduct eaten3 = EatenProduct(product3, 222);

    day.AddEatenProduct(eaten1);
    day.AddEatenProduct(eaten2);
    day.AddEatenProduct(eaten3);

    //Eaten Day Serialization

    Json::Value root;
    EatenDaySerializer eatenDaySerializer(root);
    eatenDaySerializer.ObjectToRoot(day);
    std::ofstream file("eaten_day_test.json");
    file << root;
    file.close();


    //Eaten Day Deserialization

    EatenDay eatenDay2;
    std::ifstream file2("eaten_day_test.json");
    Json::Value root2;
    EatenDayDeserializer deserializer(root2);
    deserializer.FileToRoot(file2);
    deserializer.RootToObject(eatenDay2);
    file2.close();

    BOOST_TEST(day == eatenDay2);

}

BOOST_AUTO_TEST_SUITE_END()
