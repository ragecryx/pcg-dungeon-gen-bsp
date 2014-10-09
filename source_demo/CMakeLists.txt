# PCG-BSPDungeonGen Demo/Example


# Dependencies
# -


# Sources and Building

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
)

file(GLOB DemoSourceFiles
	"${PROJECT_SOURCE_DIR}/source_demo/*.cpp"
)

add_executable(PCG_BSPDungeonGen_Demo ${DemoSourceFiles})
target_link_libraries(PCG_BSPDungeonGen_Demo PCG_BSPDungeonGen)


# Installation
install(TARGETS PCG_BSPDungeonGen_Demo DESTINATION bin)

