cmake_minimum_required(VERSION 3.5)

project(DDietTrackerUnitTests LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES_FILES_FROM_MAIN_PROJECT
    ../DDietTracker/*.cpp
    ../DDietTracker/*.h
)

list(FILTER SOURCES_FILES_FROM_MAIN_PROJECT EXCLUDE REGEX "window")
list(FILTER SOURCES_FILES_FROM_MAIN_PROJECT EXCLUDE REGEX "main")
list(FILTER SOURCES_FILES_FROM_MAIN_PROJECT EXCLUDE REGEX "chart")
list(FILTER SOURCES_FILES_FROM_MAIN_PROJECT EXCLUDE REGEX "table")

#
add_executable(DDietTrackerTests size_unc_tests.cpp
 ${SOURCES_FILES_FROM_MAIN_PROJECT}
 serialization_tests.cpp
 product_creator_tests.cpp
 product_base_tests.cpp


)
#
add_test(NAME DDietTrackerTests COMMAND DDietTrackerTests)

if (DEFINED ENV{BOOST_INCLUDE_DIR})
    set(BOOST_INCLUDE_DIR $ENV{BOOST_INCLUDE_DIR})
else ()
    set(BOOST_INCLUDE_DIR "/home/mieszko/boost_1_83_0") # Change the location to where you have the Boost library
endif ()
if (BOOST_INCLUDE_DIR STREQUAL "")
    message("BOOST_INCLUDE_DIR is not set, assuming Boost can be found automatically in your system")
elseif (EXISTS ${BOOST_INCLUDE_DIR})
    include_directories(${BOOST_INCLUDE_DIR})
endif ()

set(CMAKE_PREFIX_PATH "~/vcpkg/packages/jsoncpp_x64-linux" ${CMAKE_PREFIX_PATH})
find_package(jsoncpp CONFIG REQUIRED)
include_directories(${jsoncpp_INCLUDE_DIRS})
target_link_libraries(DDietTrackerTests PRIVATE JsonCpp::JsonCpp)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
target_link_libraries(DDietTrackerTests PRIVATE Qt5::Widgets)

