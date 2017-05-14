cmake_minimum_required(VERSION 3.5)
project(genNN CXX)

# require a C++17 compiler
# use it for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# EDIT: add your (non-test) source files to this list
set(src
  )

# EDIT: add any additional test source files to this list
set(test_src unittests.cpp)

# You should not need to edit below this line
#-----------------------------------------------------------------------
#-----------------------------------------------------------------------

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# create unittests
add_executable(unittests catch.hpp ${test_src} ${src})


# create the vtray executable
add_executable(genNN genNN.cpp ${src})


enable_testing()

# unit tests
add_test(unit unittests)


