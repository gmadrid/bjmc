###
### Most of this stolen from:
###  https://stackoverflow.com/questions/21163188/most-simple-but-complete-cmake-example
###

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
file(GLOB_RECURSE sources      src/lib/*.cc src/lib/*.h)
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
add_executable(bjmc ${sources} ${sources_main})

###
### unittests
###
enable_testing()
add_executable(unit_tests ${sources} ${sources_test})
target_link_libraries(unit_tests gtest gtest_main)
add_test(NAME    bjmc_test
         COMMAND unit_tests)

###
### target acquisition
###

#target_compile_options(bjmc PUBLIC -Wall -std=c++1z)

###
### Acquire and build GTest, adding to our project
###
#configure_file(CMakeGTest.txt.in googletest-download/CMakeLists.txt)
#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#  RESULT_VARIABLE result
#  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#if(result)
#  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
#endif()

###execute_process(COMMAND ${CMAKE_COMMAND} --build .
#  RESULT_VARIABLE result
#  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#if(result)
#  message(FATAL_ERROR, "Build step for googletest failed: ${result}")
#endif()




###
### Now build it all.
### 

#enable_testing()

#add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#		 ${CMAKE_BINARY_DIR}/googletest-build
#		 EXCLUDE_FROM_ALL)

#add_executable(unit_tests ${sources_test} ${sources})
#target_compile_options(unit_tests PUBLIC -Wall -std=c++1z)
#target_link_libraries(unit_tests gtest gtest_main)
#add_test(NAME bjmc_test COMMAND unit_tests)

#find_package(GFlags REQUIRED)

