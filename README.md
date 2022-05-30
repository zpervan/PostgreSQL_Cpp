# PostgreSQL_Cpp #

This is a template repository which includes basic PostgreSQL queries. In the README below you can find a detailed instruction on how to setup your environment to use it within your C++ application. This README will contain all tools that I am using in my development environment. Of course, you are free to use the tools that you're most comfortable with :)

Currently, this works in a Windows 10 environment, but it is planned to expand this guide to a Linux environment in some point of time.

## Prerequirements ##

* Operating system: Windows 10
* Database server: [PostgreSQL](https://www.postgresql.org/download/)
* Database GUI tool: [DBeaver](https://dbeaver.io/) or [DataGrip](https://www.jetbrains.com/datagrip/download/download-thanks.html?platform=windows)
* Development environment: [MSYS2](https://www.msys2.org/)
* C++ standard: 20
* Build system: CMake
* IDE: [VS Code](https://code.visualstudio.com/) or [CLion](https://www.jetbrains.com/clion/)

## Database setup ##

1. Install the PostgreSQL server on your Windows 10 PC.
    + You can follow [this](https://www.2ndquadrant.com/en/blog/pginstaller-install-postgresql/) guide for a more detailed explanation
2. After the installation is completed, restart your PC to run the PostgreSQL server
3. To check whether your database is successfully created, open your database GUI tool and connect your local database. The picture below shows the connection parameters for a default installed database.
![01_test_connection](/Assets/01_db_connection_test.PNG)
4. After you verified that the database is successfully created, add a new table. In my case the table is called `pc`.
5. Add some attributes and fill the table with some dummy data. In my case, this looks like the following. 
![02_table](/Assets/02_table.PNG)
6. And out database is ready to be queried :)

## Developement environment ##

In order to build this project, we will use the MSYS environment. Do the following to setup the developement environment:
1. Follow the steps on https://www.msys2.org/ 
2. Install the following dependencies:
```shell
pacman -S --needed base-devel mingw-w64-x86_64-toolchain  mingw-w64-x86_64-cmake
```
## C++ code ##

The main .cpp contains all the logic for a basic `SELECT` query. What you should consider is to change (i.e. adapt it for your database) the following:
```cpp
const char conninfo[] = "postgresql://postgres@localhost?port=5432&dbname=postgres&user=postgres&password=root";
```
The string consists of 5 parameters:
* `postgresql://postgres@localhost` - Address of the database (or in my case localhost)
* `port=5432` - The port over which the communitcation will take place. This is specified during the installation phase of the PostgreSQL database, so you should use the port number which you defined during that phase.
* `dbname=postgres` - The name of the database. Also, specified during the installation phase.
* `user=postgres` - The username to access the database . This is a default username.
* `password=root` - Password to access the database.

The rest of the code represents the connection and querying logic. For more examples you can look up directly [page](https://gist.github.com/ictlyh/12fe787ec265b33fd7e4b0bd08bc27cb).

## Building the project ##

1. In order to query your PostgreSQL database, you need to link it with the library which comes in the PostgreSQL installation package. In order to do that, add the following CMake code to your `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.22)
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

# Include the INCLUDE directories
include_directories(${PostgreSQL_INCLUDE_DIRS})

# Link the LIBRARY directory
link_directories(${PostgreSQL_LIBRARY_DIRS})

# Create an executable
add_executable(ExamplePostgreSQL main.cpp)

# Link the executable `ExamplePostgreSQL` with the PostgreSQL library
target_link_libraries(ExamplePostgreSQL ${PostgreSQL_LIBRARIES})
```

2. Open up the MSYS2 console and navigate to the root of this project.

3. Create a new folder and create a new `build` folder. Execute the following command:
```shell
mkdir -p build
```
4. `cd` into your `build` folder and execute the CMake generation command
```cmake
cmake ..
```
5. Build the project:
```shell
cmake --build .
```
6. Run the built executable in a Windows DOS box:
```shell
.\ExamplePostgreSQL.exe
```
If an error like the following appears such as:
```shell
C:/msys64/home/user/PostgreSQL_Cpp/build/ExamplePostgreSQL.exe: error while loading shared libraries: LIBPQ.dll: cannot open shared object file: No such file or directory
```
Then you need to ensure you add your PostgreSQL installation's bin folder to your windows path variable. For example: `C:\Program Files\PostgreSQL\14\bin`

In my case, it will output the following:
![03_output](/Assets/03_output.PNG)


## Additional ##

If you have any question, feel free to send me a message or raise an issue.

Thanks and happy coding :)
