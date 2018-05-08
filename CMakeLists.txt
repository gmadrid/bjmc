
project (bjmc)

include(cmake/DownloadProject.cmake)

###
### config
###
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "-std=c++1z -Wall ${CMAKE_CXX_FLAGS}")

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
add_library(bjmc_lib
  src/lib/basic_strategy.cc
  src/lib/card.cc
  src/lib/deck.cc
  src/lib/game.cc
  src/lib/hand.cc
  src/lib/strategy.cc
  src/lib/table.cc)
target_link_libraries(bjmc_lib
  PUBLIC
    absl_strings)

###
### bjmc
###
add_executable(bjmc src/main/main.cc)
target_link_libraries(bjmc
  PRIVATE
    bjmc_lib)

###
### unittests
###
enable_testing()
add_executable(unit_tests
  src/test/basic_strategy_test.cc
  src/test/card_test.cc
  src/test/chipstack_test.cc
  src/test/deck_test.cc
  src/test/hand_test.cc
  src/test/rules_test.cc
  src/test/strategy_test.cc)

target_link_libraries(unit_tests
  PRIVATE
    bjmc_lib
    gtest
    gtest_main)
add_test(NAME    bjmc_test
         COMMAND unit_tests)


