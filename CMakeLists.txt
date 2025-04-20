cmake_minimum_required(VERSION 3.14.0)
project(emulator8080 LANGUAGES CXX C)

add_compile_options(-fmacro-prefix-map=${CMAKE_SOURCE_DIR}=)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB emulator8080_src "src/*.cpp")
add_executable(emulator8080 ${emulator8080_src})
target_include_directories(emulator8080 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

