cmake_minimum_required(VERSION 3.22)
project(ExamplePostgreSQL VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

# Set MSYS2 compiler flags
if (CMAKE_GENERATOR MATCHES "Unix Makefiles")
    message("-- Using MSYS2")
    set(CMAKE_CXX_COMPILER "/mingw64/bin/g++")
    set(CMAKE_C_COMPILER "/mingw64/bin/gcc")
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
elseif(CMAKE_GENERATOR MATCHES "Visual Studio")
    message("-- Using Visual Studio is not supported currently")
endif()

# Custom location of the PostgreSQL library
set(PostgreSQL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/PostgreSQL14")
set(PostgreSQL_ROOT "${PostgreSQL_DIR}")
set(PostgreSQL_LIBRARY_DIR "${PostgreSQL_DIR}/lib")
set(PostgreSQL_INCLUDE_DIRS "${PostgreSQL_DIR}/include")
set(PostgreSQL_LIBRARIES "${PostgreSQL_DIR}/lib/libpq.lib")

# Find the PostgreSQL library which will add the INCLUDE and LIBRARY paths
#find_package(PostgreSQL REQUIRED PATHS ${PostgreSQL_ROOT})

# Include the found INCLUDE directory
include_directories(${PostgreSQL_INCLUDE_DIRS})

# Include the found LIBRARY directory
link_directories(${PostgreSQL_LIBRARY_DIRS})

# Print the PostgreSQL locations
message("-- PostgreSQL_ROOT: ${PostgreSQL_ROOT}")
message("-- PostgreSQL_INCLUDE_DIR: ${PostgreSQL_INCLUDE_DIRS}")
message("-- PostgreSQL_LIBRARY_DIR: ${PostgreSQL_LIBRARY_DIR}")
message("-- PostgreSQL_LIBRARIES: ${PostgreSQL_LIBRARIES}")

# Create an executable
add_executable(ExamplePostgreSQL main.cpp)

# Link the executable `ExamplePostgreSQL` with the PostgreSQL library
target_link_libraries(ExamplePostgreSQL ${PostgreSQL_LIBRARIES})

# Fetch all needed PostgreSQL *.dll libraries
file(GLOB_RECURSE PostgreSQL_LIBRARY_FILES "${PostgreSQL_ROOT}/*.dll")

# Copy all PostgreSQL library files into the build folder
foreach(PostgreSQL_LIBRARY_FILE ${PostgreSQL_LIBRARY_FILES})
   add_custom_command(TARGET ExamplePostgreSQL POST_BUILD 
   COMMAND "${CMAKE_COMMAND}" -E copy ${PostgreSQL_LIBRARY_FILE} ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
endforeach()

