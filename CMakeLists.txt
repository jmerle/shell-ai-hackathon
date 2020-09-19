cmake_minimum_required(VERSION 3.17)
project(shell-ai-hackathon)

# Install cmake-conan
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

# Check if Conan is installed
conan_check(REQUIRED)

# Install dependencies and create CMake targets for them
conan_cmake_run(REQUIRES
        # Eigen for linear algebra
        eigen/3.3.7

        # Catch2 for unit tests
        catch2/2.13.1

        # Create CMake targets for all dependencies and build dependencies that can't be downloaded as binaries
        BASIC_SETUP CMAKE_TARGETS BUILD missing)

# C++17 is used throughout the project
set(CPP_VERSION cxx_std_17)

# Compile with -march=native if possible
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if (COMPILER_SUPPORTS_MARCH_NATIVE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif ()

# Find OpenMP
find_package(OpenMP)

# Variables for the main executable
file(GLOB_RECURSE MAIN_SOURCES src/*.cpp)
list(REMOVE_ITEM MAIN_SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/benchmark.cpp")
set(MAIN_HEADERS src)
set(MAIN_LIBRARIES CONAN_PKG::eigen OpenMP::OpenMP_CXX)

# Variables for the benchmark executable
file(GLOB_RECURSE BENCHMARK_SOURCES src/*.cpp)
list(REMOVE_ITEM BENCHMARK_SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp")
set(BENCHMARK_LIBRARIES ${MAIN_LIBRARIES})

# Variables for the tests executable
file(GLOB_RECURSE TESTS_SOURCES tests/*.cpp)
set(MAIN_SOURCES_WITHOUT_MAIN ${MAIN_SOURCES})
list(REMOVE_ITEM MAIN_SOURCES_WITHOUT_MAIN "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp")
set(TESTS_HEADERS tests)
set(TESTS_LIBRARIES CONAN_PKG::catch2)

# Configuration for the main executable
add_executable(main ${MAIN_SOURCES})
target_compile_features(main PUBLIC ${CPP_VERSION})
target_include_directories(main PUBLIC ${MAIN_HEADERS})
target_link_libraries(main ${MAIN_LIBRARIES})

# Configuration for the benchmark executable
add_executable(benchmark ${BENCHMARK_SOURCES})
target_compile_features(benchmark PUBLIC ${CPP_VERSION})
target_include_directories(benchmark PUBLIC ${MAIN_HEADERS})
target_link_libraries(benchmark ${MAIN_LIBRARIES})

# Configuration for the tests executable
add_executable(tests ${TESTS_SOURCES} ${MAIN_SOURCES_WITHOUT_MAIN})
target_compile_features(tests PUBLIC ${CPP_VERSION})
target_include_directories(tests PUBLIC ${TESTS_HEADERS} ${MAIN_HEADERS})
target_link_libraries(tests ${TESTS_LIBRARIES} ${MAIN_LIBRARIES})
