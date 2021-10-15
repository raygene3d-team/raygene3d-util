set(NAME raygene3d)

set(UTIL_DIR ${CMAKE_SOURCE_DIR}/${NAME}-util)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


set(SOURCE types.h types.cpp property.h property.cpp
	#${UTIL_DIR}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE})

add_library(${NAME}-util STATIC ${SOURCE})
	
target_include_directories(${NAME}-util PUBLIC
	${CMAKE_SOURCE_DIR}/3rdparty
)

IF(WIN32)

ELSE(WIN32)
target_link_libraries(${NAME}-util PRIVATE
	optimized -ldl
	optimized -lpthread
)
ENDIF(WIN32)
