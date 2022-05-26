cmake_minimum_required(VERSION 3.23)
project(ExamplePostgreSQL VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

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