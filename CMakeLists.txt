cmake_minimum_required(VERSION 3.29)
project(tests VERSION 0.0.1 LANGUAGES CXX)

file(GLOB_RECURSE SOURCES src/*/*.cpp)

include(ExternalProject)
find_package(Git REQUIRED)

function(INCLUDE_DOCTEST_CACHE)
	include_directories(${CMAKE_BINARY_DIR}/doctest/src/doctest/doctest)
endfunction()

function(INCLUDE_DOCTEST_GIT)
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
	include_directories(${DOCTEST_INCLUDE_DIR})
endfunction()

function(INCLUDE_DOCTEST CONNECTION_UNAVAILABLE)
	if(CONNECTION_UNAVAILABLE EQUAL 0)
		include_doctest_git()
	else()
		include_doctest_cache()
	endif()
endfunction()

function(INCLUDE_BOOST)
	find_package(Boost REQUIRED)
	set(Boost_USE_STATIC_LIBS OFF)
	set(Boost_USE_MULTITHREADED ON)
	set(Boost_USE_STATIC_RUNTIME OFF)
	message(STATUS "Boost version: ${Boost_VERSION}")
	include_directories(${Boost_INCLUDE_DIR})
endfunction()

if(MSVC)
	execute_process(
		COMMAND ping www.google.com -n 2
		ERROR_QUIET
		RESULT_VARIABLE NO_CONNECTION
	)
else()
	execute_process(
		COMMAND ping www.google.com -c 2
		ERROR_QUIET
		RESULT_VARIABLE NO_CONNECTION
	)
endif()

include_directories(include)
include_doctest(${NO_CONNECTION})
include_boost()

add_executable(tests src/Tests.cpp ${SOURCES})
target_compile_features(tests PRIVATE cxx_std_23)

add_executable(program src/Program.cpp ${SOURCES})
target_compile_features(program PRIVATE cxx_std_23)
