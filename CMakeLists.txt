# CMakeList.txt : CMake project for XbSymbolSymbolDatabase, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10.2)

project (XbSymbolDatabase)

file(GLOB_RECURSE SOURCES
 "XbSymbolDatabase.c"
 "OOVPADatabase/*.inl"
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES})

add_library (XbSymbolDatabase ${SOURCES})
target_compile_definitions(XbSymbolDatabase PRIVATE _CRT_SECURE_NO_WARNINGS)

# For any optional tools, use list(APPEND ${INSTALL_TOOLS} "tool_name")
set(INSTALL_TOOLS "XbSymbolDatabase")

set_target_properties(XbSymbolDatabase PROPERTIES
 PUBLIC_HEADER XbSymbolDatabase.h
 C_STANDARD 11
 C_STANDARD_REQUIRED ON
)

install(TARGETS ${INSTALL_TOOLS}
 RUNTIME DESTINATION bin
 PUBLIC_HEADER DESTINATION include
 LIBRARY DESTINATION lib_shared
 ARCHIVE DESTINATION lib_static
)

install(FILES LICENSE README.md DESTINATION .)
