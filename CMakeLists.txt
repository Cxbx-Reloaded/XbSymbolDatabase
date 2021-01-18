# CMakeList.txt : CMake solution for XbSymbolDatabase.
#
cmake_minimum_required (VERSION 3.10.2)

project (XbSymbolDatabase)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
 set(XBSDB_DEFAULT_CONFIGS ON)
else()
 set(XBSDB_DEFAULT_CONFIGS OFF)
endif()

option(XBSDB_INSTALL_LIB "Install libXbSymbolDatabase library" ${XBSDB_DEFAULT_CONFIGS})
option(XBSDB_BUILD_CLI "Build XbSymbolDatabase CLI tool" ${XBSDB_DEFAULT_CONFIGS})
include(CMakeDependentOption)
cmake_dependent_option(XBSDB_INSTALL_CLI "Install XbSymbolDatabase CLI tool" ${XBSDB_DEFAULT_CONFIGS}
                       "XBSDB_BUILD_CLI" OFF)

# For any optional tools, use list(APPEND XBSDB_INSTALL_TOOLS "tool_name")

if(XBSDB_INSTALL_LIB)
 list(APPEND XBSDB_INSTALL_TOOLS "libXbSymbolDatabase")
endif()

if(XBSDB_INSTALL_CLI)
 list(APPEND XBSDB_INSTALL_TOOLS "XbSymbolDatabaseCLI")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(XBSDB_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory("${PROJECT_SOURCE_DIR}/projects")

if (XBSDB_INSTALL_TOOLS)

 if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  install(FILES "LICENSE" "README.md" DESTINATION .)
 else()
  install(FILES "LICENSE" "README.md" DESTINATION "XbSymbolDatabase")
 endif()
endif()
