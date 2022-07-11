cmake_minimum_required(VERSION 3.0.0)
project(names VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

include(CTest)

add_compile_options(-Wall -Wextra -Werror)

if(ENABLE_TEST)
    add_compile_options(--coverage -g)
    add_link_options(--coverage)
endif()

find_package(CLI11 REQUIRED)

execute_process(COMMAND python3 script/gen_vector.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(names main.cpp)
target_include_directories(names PRIVATE include)
target_link_libraries(names PRIVATE CLI11::CLI11)
