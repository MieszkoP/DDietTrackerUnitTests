# DDietTrackerUnitTests

Unit tests for [Desktop Diet Tracker v. 0.0.1](https://github.com/MieszkoP/DDietTracker).

## Dependencies you needed include:
- Qt (I used version 5.15.2 Qt)
- Cmake (I used 3.24.2)
- Jsoncpp
- C++ 20 (so, You need to make sure you use the correct compiler - I used g++ 11.4.0)
- Boost library 

## How to run?
In CmakeLists, change two lines. Change to one where you have the jsoncpp and boost libraries downloaded.

```
set(BOOST_INCLUDE_DIR "/home/mieszko/boost_1_83_0") # Change the location to where you have the Boost library
...
set(CMAKE_PREFIX_PATH "~/vcpkg/packages/jsoncpp_x64-linux" ${CMAKE_PREFIX_PATH})
```

Unit tests directory should be in the same directory as base project directory:

".../SomeDirectory/DDietTracker/" and ".../SomeDirectory/DDietTrackerUnitTests/"
