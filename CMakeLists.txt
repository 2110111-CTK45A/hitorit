cmake_minimum_required(VERSION 3.28)
project(tests VERSION 0.0.1 LANGUAGES CXX)

file(GLOB_RECURSE SOURCES src/*/*.cpp)

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
	doctest
	PREFIX ${CMAKE_BINARY_DIR}/doctest
	GIT_REPOSITORY https://github.com/doctest/doctest.git
	TIMEOUT 10
	UPDATE_COMMAND ${GIT_EXECUTABLE} pull
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")

find_package(Boost REQUIRED)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
message(STATUS "Boost version: ${Boost_VERSION}")

include_directories(include)
include_directories(${DOCTEST_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})

add_executable(tests ${SOURCES})
target_compile_features(tests PRIVATE cxx_std_20)
