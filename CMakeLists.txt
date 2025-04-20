# project
set(name "xwrap")
cmake_minimum_required(VERSION 3.10)
project(${name} CXX)

# clang setting
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "C++ compiler" FORCE)
set(CMAKE_CXX_STANDARD 26)

# src
file(GLOB_RECURSE SRC src/*.cpp)
add_library(${name} ${SRC})

# link std library staticly
target_link_options(${name} PRIVATE -static-libgcc -static-libstdc++)

# include header
target_include_directories(${name} PUBLIC include/)

# add third party dependencies here
# add_subdirectory(./vendor/hierro2d-cpp)
# target_link_libraries(${name} PUBLIC hierro)

find_package(X11 REQUIRED)
target_link_libraries(${name} PUBLIC ${X11_LIBRARIES})
target_link_libraries(${name} PUBLIC X11::Xcomposite)
target_link_libraries(${name} PUBLIC X11::Xfixes)
target_link_libraries(${name} PUBLIC X11::Xdamage)
target_link_libraries(${name} PUBLIC X11::Xtst)

find_package(OpenCV REQUIRED)
target_link_libraries(${name} PUBLIC ${OpenCV_LIBRARIES})

add_subdirectory(./vendor/tasklet)
target_link_libraries(${name} PUBLIC tasklet)
