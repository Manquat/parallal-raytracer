cmake_minimum_required(VERSION 3.2)
project(raytracer)

#set(CMAKE_C_COMPILER "/ssoft/gcc/4.8.3/RH6/gcc-4.4.7/x86_E5v2/gcc/bin/gcc")
#set(CMAKE_CXX_COMPILER "/ssoft/intel/2016/RH6/all/x86_E5v2/impi/5.1.3.181/bin64//mpicxx")
set(CMAKE_CXX_COMPILER "/usr/bin/mpic++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lm -fopenmp -O3")

set(SOURCE_FILES main.cpp utils.h Ray.cpp Ray.h Sphere.cpp Sphere.h Primitive.h Primitive.cpp Scene.cpp Scene.h Camera.cpp Camera.h Screen.cpp Screen.h Light.cpp Light.h Material.cpp Material.h Generator.cpp Generator.h Serializer.cpp Serializer.h)
add_executable(raytracer ${SOURCE_FILES})
