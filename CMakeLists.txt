cmake_minimum_required (VERSION 2.6)
project(PCGBSPDungeonGen)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR/DIST}")
set(CMAKE_CXX_FLAGS "-std=c++11 -static-libstdc++ ${CMAKE_CXX_FLAGS}")

# Project Options/Settings

set(PCG_DUNGEONGEN_VERSION_MAJOR 0)
set(PCG_DUNGEONGEN_VERSION_MINOR 1)

option(BUILD_DEMO
	"Build the demos/examples"
	ON
)

if(BUILD_DEMO)
	add_subdirectory(source_demo)
endif(BUILD_DEMO)


# Dependencies
# -


# Sources and Building

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
)

file(GLOB SourceFiles
	"source/*.cpp"
)

add_library(PCG_BSPDungeonGen STATIC ${SourceFiles})


# Installation
install(TARGETS PCG_BSPDungeonGen DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/PCG-BSPDungeonGen DESTINATION include)
