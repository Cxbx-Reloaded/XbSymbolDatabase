# CMakeList.txt : CMake solution for XbSymbolDatabase.
#
cmake_minimum_required (VERSION 3.10.2)

project (XbSymbolDatabase)

if(NOT CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
 option(XBSDB_INSTALL_LIB "Install libXbSymbolDatabase library" OFF)
else()
 set(XBSDB_INSTALL_LIB ON)
endif()

# For any optional tools, use list(APPEND XBSDB_INSTALL_TOOLS "tool_name")

if(XBSDB_INSTALL_LIB)
 list(APPEND XBSDB_INSTALL_TOOLS "libXbSymbolDatabase")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(XBSDB_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory("${PROJECT_SOURCE_DIR}/projects")

if (XBSDB_INSTALL_TOOLS)
 install(TARGETS ${XBSDB_INSTALL_TOOLS}
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION include
  LIBRARY DESTINATION lib_shared
  ARCHIVE DESTINATION lib_static
 )

 if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  install(FILES "LICENSE" "README.md" DESTINATION .)
 else()
  install(FILES "LICENSE" "README.md" DESTINATION "XbSymbolDatabase")
 endif()
endif()
