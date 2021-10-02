cmake_minimum_required(VERSION 3.10)
project(simplex)

set(CMAKE_CXX_STANDARD 17)

set (SOURCE_FILES
		src/main.cpp
		src/hittable_list.cpp
		src/sphere.cpp
)

add_executable(simplex ${SOURCE_FILES})