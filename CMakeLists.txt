cmake_minimum_required(VERSION 3.16)

project(vectorND LANGUAGES C CXX VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# flags
# set(CMAKE_CXX_FLAGS "-O3 -Werror -Wall -Wextra -Wpedantic")
# set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS "-O3 -Wall")
set(OpenMP_CXX_FLAGS "-fopenmp -lpthread")

# ---- Google tests ----
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# --------

enable_testing()

# headers, sources
include_directories(./include ./src)

set(HEADERS
    ./include/Vector.hpp
)

# set(SOURCES
# )

# add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include/)

add_subdirectory(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)