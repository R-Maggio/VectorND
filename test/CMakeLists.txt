cmake_minimum_required(VERSION 3.16)

set(This vectorNDTests)

set(SOURCES
    VectorTests.cpp
)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(${This} ${SOURCES})
target_link_libraries(${This} PUBLIC
    gtest_main
    vectorND
)

include(GoogleTest)
gtest_discover_tests(${This})

# add_test(NAME ${This} COMMAND ${This})