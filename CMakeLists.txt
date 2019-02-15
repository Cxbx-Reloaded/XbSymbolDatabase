# CMakeList.txt : CMake project for XbSymbolSymbolDatabase, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project (XbSymbolDatabase)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

file(GLOB SOURCES
 "XbSymbolDatabase.c"
 "OOVPADatabase/*.inl"
 "OOVPADatabase/D3D8/*.inl"
 "OOVPADatabase/D3D8LTCG/*.inl"
 "OOVPADatabase/DSound/*.inl"
 "OOVPADatabase/XActEng/*.inl"
 "OOVPADatabase/Xapi/*.inl"
)

add_library (XbSymbolDatabase ${SOURCES})
