# CMakeList.txt : CMake project for libXbSymbolDatabase.
#
cmake_minimum_required (VERSION 3.10.2)

project (libXbSymbolDatabase LANGUAGES C)

file(GLOB INCLUDES
 "${XBSDB_ROOT_DIR}/include/Xbe.h"
 "${XBSDB_ROOT_DIR}/include/libXbSymbolDatabase.h"
)
source_group(TREE ${XBSDB_ROOT_DIR} FILES ${INCLUDES})

file(GLOB HEADERS
 "${XBSDB_ROOT_DIR}/src/lib/internal_db_version.h"
 "${XBSDB_ROOT_DIR}/src/lib/internal_functions.h"
 "${XBSDB_ROOT_DIR}/src/lib/internal_tests.h"
 "${XBSDB_ROOT_DIR}/src/lib/manual_custom.h"
 "${XBSDB_ROOT_DIR}/src/lib/manual_d3d8__ltcg.h"
 "${XBSDB_ROOT_DIR}/src/lib/manual_dsound.h"
 "${XBSDB_ROOT_DIR}/src/lib/manual_xapilib.h"
 "${XBSDB_ROOT_DIR}/src/OOVPADatabase/OOVPA.h"
)
source_group(TREE ${XBSDB_ROOT_DIR}/src PREFIX header FILES ${HEADERS})

file(GLOB_RECURSE SOURCES
 "${XBSDB_ROOT_DIR}/src/libXbSymbolDatabase.c"
 "${XBSDB_ROOT_DIR}/src/OOVPADatabase/*.inl"
)
source_group(TREE ${XBSDB_ROOT_DIR} FILES ${SOURCES})

add_library (${PROJECT_NAME} ${INCLUDES} ${HEADERS} ${SOURCES})

# NOTES:
# Using INTERFACE keyword will not work within the project. Only PUBLIC/PRIVATE keywords does.
target_include_directories(${PROJECT_NAME}
 PUBLIC "${XBSDB_ROOT_DIR}/include"
 PRIVATE "${XBSDB_ROOT_DIR}/src/OOVPADatabase"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)

set_target_properties(${PROJECT_NAME} PROPERTIES
 PUBLIC_HEADER "${INCLUDES}"
 C_STANDARD 11
 C_STANDARD_REQUIRED ON
 FOLDER XbSymbolDatabase
)

if(XBSDB_INSTALL_LIB)
 install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION include
  LIBRARY DESTINATION lib_shared
  ARCHIVE DESTINATION lib_static
 )
endif()
