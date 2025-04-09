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
        src/ConverterJSON.cpp
        src/InvertedIndex.cpp
        src/SearchServer.cpp
        src/main.cpp
)

add_executable(search_engine_test
        src/ConverterJSON.cpp
        test/tests.cpp
        src/InvertedIndex.cpp
        src/SearchServer.cpp
)

target_include_directories(search_engine_test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/nlohmann_json
)

target_include_directories(search_engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/nlohmann_json
)
target_link_libraries(search_engine_test PRIVATE
        nlohmann_json::nlohmann_json
        gtest_main
        gtest
)

target_link_libraries(search_engine PRIVATE
        nlohmann_json::nlohmann_json
)
include(GoogleTest)
gtest_discover_tests(search_engine_test)