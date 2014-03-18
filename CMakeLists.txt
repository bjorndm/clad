cmake_minimum_required(VERSION 2.8)
# Set policy: link_directories is relative to source dir
cmake_policy(SET CMP0015 NEW)

# Set the project name.
project(CLAD C)

# tell CMake to search first in the cmake subdirectory for FIND_PACKAGE() or INCLUDE()
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

include(CheckCSourceCompiles)

if(CMAKE_COMPILER_IS_GNUCC)
 set(COMPILER_GCC 1)
set(CMAKE_C_FLAGS "-W -Wall -Wno-unused -Wno-unknown-pragmas -g -std=c89 -ffast-math -fstrict-aliasing -Wstrict-aliasing=2")
# set(CMAKE_LD_FLAGS "-pg")
# Use c89, debugging, all warnings except unused and unknown pragmas.
# when compiling with gnu compiler.  
# Warn about alisasing because otherwise aliasing problems it may not be detected.
endif(CMAKE_COMPILER_IS_GNUCC)

# Set include and lib dirs. 
include_directories("include" "include/clad")

set(CLAD_SRC_FILES src/test.c src/variant.c src/memory.c src/allocator.c 
                   src/pool.c src/slre.c src/sb.c)
message(STATUS ${CLAD_SRC_FILES})
set_source_files_properties(${CLAD_SRC_FILES} PROPERTIES LANGUAGE C)


# Allow the developer to select if Dynamic or Static libraries are built
option(CLAD_BUILD_SHARED "Build Shared Library" OFF)
# Set the LIB_TYPE variable to STATIC
set(CLAD_LIB_TYPE STATIC)
if(CLAD_BUILD_SHARED)
  set(CLAD_LIB_TYPE SHARED)
endif(CLAD_BUILD_SHARED)

add_library(clad ${CLAD_LIB_TYPE} ${CLAD_SRC_FILES})




enable_testing()
# Let ctest run valgrind
# test exe in the test subdir (first one should work, but doesnt, hmmm...)
set(CMAKE_CTEST_OPTIONS --output-on-failure)
set(CTEST_OUTPUT_ON_FAILURE TRUE)
set(CTEST_MEMORYCHECK_COMMAND:FILEPATH "/usr/bin/valgrind")

# exe in the bin subdir (first one should work, but doesn't, hmmm...)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_subdirectory("test")


# Allow installation of the lib and it's headers
IF (NOT WIN32)
  install(TARGETS clad DESTINATION lib)
  install(DIRECTORY include/clad DESTINATION include)
ENDIF()









