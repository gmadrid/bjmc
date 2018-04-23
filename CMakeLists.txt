###
### Most of this stolen from:
###  https://stackoverflow.com/questions/21163188/most-simple-but-complete-cmake-example
###

cmake_minimum_required(VERSION 3.0)
project (bjmc)

###
### Finding source files
###
file(GLOB_RECURSE sources      src/main/*.cc src/main/*.h)
file(GLOB_RECURSE sources_test src/test/*.cc)

###
### target acquisition
###
add_executable(bjmc ${sources})

target_compile_options(bjmc PUBLIC -Wall -std=c++1z)

###
### Acquire and build GTest, adding to our project
###
configure_file(CMakeGTest.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR, "Build step for googletest failed: ${result}")
endif()

enable_testing()

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
		 ${CMAKE_BINARY_DIR}/googletest-build
		 EXCLUDE_FROM_ALL)

add_executable(unit_tests ${sources_test} ${sources})
target_link_libraries(unit_tests gtest_main)
add_test(NAME bjmc_test COMMAND unit_tests)

if(GTEST_FOUND)
  add_executable(unit_tests ${sources_test} ${sources})
  target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)
  target_link_libraries(unit_tests PUBLIC
    ${GTEST_BOTH_LIBRARIES}
    bjmc
  )

  target_include_directories(unit_tests PUBLIC
    ${GTEST_INCLUDE_DIRS}
  )
endif()

find_package(GFlags REQUIRED)

