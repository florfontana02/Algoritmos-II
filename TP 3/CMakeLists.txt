cmake_minimum_required(VERSION 3.5)
project(TP_Lolla)

set(CMAKE_CXX_STANDARD 11)

# Algunos flags para pasar al compilador (gnu++11 en vez de c++11 para que sea cross-plat)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=gnu++11 -ggdb3 -g")

# Dependencia de Google Test
SET(BUILD_GMOCK OFF)
SET(BUILD_GTEST ON)
add_library(gtest STATIC tests/gtest-1.8.1/gtest-all.cc)
add_library(gtest_main STATIC tests/gtest-1.8.1/gtest_main.cc)

# Leemos todos los archivos fuentes en ./src
file(GLOB SOURCE_FILES src/*.cpp src/*.h src/*.hpp)
file(GLOB TESTS tests/*.cpp)

add_executable(correrTests ${SOURCE_FILES} ${TESTS} src/tipos2.h)

# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTests gtest gtest_main)

# Test suites a ejecutar
add_test(correrTests tests_consumos tests_lollapatuza)

# Target para correr Valgrind
add_custom_target(correrValgrind
        valgrind --leak-check=full -v ./correrTests 2>&1
        DEPENDS correrTests)