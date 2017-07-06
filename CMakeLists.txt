cmake_minimum_required(VERSION 3.5)
project(genNN CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



set(src
	neuron.hpp neuron.cpp
	net.hpp net.cpp
	mnistNet.cpp
  )

set(test_src unittests.cpp)

add_executable(unittests catch.hpp ${test_src} ${src})

add_executable(genNN genNN.cpp ${src})

add_test(unit unittests)


