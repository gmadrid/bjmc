
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
### library
###
add_library(bjmc_lib ${sources_lib})
target_link_libraries(bjmc_lib absl_strings)
target_include_directories(bjmc_lib PRIVATE absl_strings)

###
### bjmc
###
add_executable(bjmc ${sources_main})
target_link_libraries(bjmc bjmc_lib)

###
### unittests
###
enable_testing()
add_executable(unit_tests ${sources_test})
target_link_libraries(unit_tests bjmc_lib gtest gtest_main)
add_test(NAME    bjmc_test
         COMMAND unit_tests)


