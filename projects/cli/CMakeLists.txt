# CMakeList.txt : CMake project for XbSymbolDatabaseCLI.
#
cmake_minimum_required(VERSION 3.10.2)

project(XbSymbolDatabaseCLI LANGUAGES C)

find_package(Threads)

add_executable(XbSymbolDatabaseCLI ${XBSDB_ROOT_DIR}/src/cli/main.c)

target_compile_definitions(XbSymbolDatabaseCLI PRIVATE _CRT_SECURE_NO_WARNINGS)

target_link_libraries(XbSymbolDatabaseCLI libXbSymbolDatabase Threads::Threads)

set_target_properties(XbSymbolDatabaseCLI PROPERTIES
 C_STANDARD 11
 C_STANDARD_REQUIRED ON
 FOLDER XbSymbolDatabase
)
