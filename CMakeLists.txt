cmake_minimum_required (VERSION 3.8)

# about this project
# ------------------
project (Farmwatch )
set(CMAKE_CXX_STANDARD 11)

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")


# set environment 
# -----------------
add_definitions( -D DEF_RET_1)

message ("Binary Tree Path: ${PROJECT_BINARY_DIR}")

# add subfolders
# -----------------
add_subdirectory(exec)
add_subdirectory(libsrc)

