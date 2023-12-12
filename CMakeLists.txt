# Set the minimum required version of CMake to be 3.10
cmake_minimum_required(VERSION 3.10)

# Create a project 
project(Graphs  VERSION 0.1)

# Set the variable CMAKE_CXX_STANDARD to 20
# and the variable CMAKE_CXX_STANDARD_REQUIRED to True
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-g") 

# download the Catch2 libary from git 
Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# alternative with Catch2 in a subdirectory
#add_subdirectory(lib/Catch2)

# alternatively in CMake is installed system wide
#find_package(Catch2 3 REQUIRED)

# adds an executable named `graph_tests`
add_executable(graph_test testingcode.cpp weighted_graph.cpp)
#add_executable(btree_test btree_test.cpp)
add_executable(rbtree_test rbtree_test.cpp)
add_executable(rbtree_main rbtree_main.cpp)

# These tests can use the Catch2-provided main
target_link_libraries(graph_test PRIVATE Catch2::Catch2WithMain)
#target_link_libraries(btree_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(rbtree_test PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(graph_test)
catch_discover_tests(rbtree_test)

