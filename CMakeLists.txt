cmake_minimum_required(VERSION 3.15)
project(BioluminescentWave)

set(CMAKE_CXX_STANDARD 17)

# Automatically find the vcpkg-installed SFML 3.0
find_package(SFML COMPONENTS Graphics Window System REQUIRED)

add_executable(b bio.cpp)
target_link_libraries(b PRIVATE SFML::Graphics SFML::Window SFML::System)
