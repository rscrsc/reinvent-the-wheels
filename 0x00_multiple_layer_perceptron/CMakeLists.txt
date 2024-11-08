cmake_minimum_required(VERSION 3.10)
project( 0x00_multiple_layer_perceptron VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SRC "src/*.cpp")
add_executable(main ${SRC})
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)

# libcurl
find_package(CURL REQUIRED)
target_link_libraries(main PRIVATE ${CURL_LIBRARY})
if(CURL_STATIC)
    message(STATUS "Linking against static libcurl")
else()
    message(WARNING "Static libcurl not found; linking against shared version.")
endif()

# fmt
find_package(fmt REQUIRED)
target_link_libraries(main PRIVATE fmt::fmt)
