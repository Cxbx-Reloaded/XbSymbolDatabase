# CMakeList.txt : CMake project for XbSymbolDatabaseCLI.
#
cmake_minimum_required(VERSION 3.10.2)

project(XbSymbolDatabaseCLI LANGUAGES C)

find_package(Threads)

add_executable(${PROJECT_NAME} ${XBSDB_ROOT_DIR}/src/cli/main.c)

target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)

target_link_libraries(${PROJECT_NAME} libXbSymbolDatabase Threads::Threads)

set_target_properties(${PROJECT_NAME} PROPERTIES
 C_STANDARD 11
 C_STANDARD_REQUIRED ON
 FOLDER XbSymbolDatabase
)

if(XBSDB_INSTALL_CLI)
 install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
 )
endif()
