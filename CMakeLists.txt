cmake_minimum_required(VERSION 3.29)
project(search_engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)





add_subdirectory(nlohmann_json)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)
FetchContent_MakeAvailable(googletest)




enable_testing()
add_executable(search_engine
        ConverterJSON.cpp
        tests.cpp
        InvertedIndex.cpp
        SearchServer.cpp
)


target_include_directories(search_engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/nlohmann_json

)


target_link_libraries(search_engine PRIVATE
        nlohmann_json::nlohmann_json
        gtest_main
)
include(GoogleTest)
gtest_discover_tests(search_engine)