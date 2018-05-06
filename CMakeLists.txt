
project (bjmc)

include(cmake/DownloadProject.cmake)

###
### config
###
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "-std=c++1z -Wall ${CMAKE_CXX_FLAGS}")

###
### Finding source files
###
file(GLOB_RECURSE sources_lib      src/lib/*.cc src/lib/*.h)
file(GLOB_RECURSE sources_main src/main/*.cc)
file(GLOB_RECURSE sources_test src/test/*.cc)

###
### gtest
###
download_project(PROJ                googletest
		 GIT_REPOSITORY      https://github.com/google/googletest.git
		 GIT_TAG             master
		 UPDATE_DISCONNECTED 1)
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

###
### abseil
###
set(BUILD_TESTING "OFF")
download_project(PROJ                abseil
		 GIT_REPOSITORY      https://github.com/abseil/abseil-cpp.git
		 GIT_TAG             master
		 UPDATE_DISCONNECTED 1)
add_subdirectory(${abseil_SOURCE_DIR} ${abseil_BINARY_DIR})

###
### bjmc
###
add_executable(bjmc ${sources_lib} ${sources_main})
target_include_directories(bjmc PRIVATE absl_strings)
target_link_libraries(bjmc absl_strings)

###
### unittests
###
enable_testing()
add_executable(unit_tests ${sources_lib} ${sources_test})
target_include_directories(unit_tests PRIVATE absl_strings)
target_link_libraries(unit_tests absl_strings gtest gtest_main)
add_test(NAME    bjmc_test
         COMMAND unit_tests)


