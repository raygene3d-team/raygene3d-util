set(NAME raygene3d)

set(CORE_DIR ${CMAKE_SOURCE_DIR}/${NAME}-core)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CORE_SOURCE
	${CORE_DIR}/handler.h
	${CORE_DIR}/handler.cpp
	${CORE_DIR}/property.h
	${CORE_DIR}/property.cpp
	${CORE_DIR}/types.h
	${CORE_DIR}/types.cpp
)
set(HANDLER_CORE_DIR ${CORE_DIR}/handler)
set(HANDLER_CORE_SOURCE
	${HANDLER_CORE_DIR}/import_handler.h
	${HANDLER_CORE_DIR}/import_handler.cpp
	${HANDLER_CORE_DIR}/lightmap_handler.h
	${HANDLER_CORE_DIR}/lightmap_handler.cpp
	${HANDLER_CORE_DIR}/environment_handler.h
	${HANDLER_CORE_DIR}/environment_handler.cpp
)

set(SOURCE core.h core.cpp
	${CORE_SOURCE}
	${HANDLER_CORE_SOURCE}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE})

add_library(${NAME}-core STATIC ${SOURCE})
	
target_include_directories(${NAME}-core PUBLIC
	${CMAKE_SOURCE_DIR}/3rdparty
)

IF(WIN32)

ELSE(WIN32)
target_link_libraries(${NAME}-core PRIVATE
	optimized -ldl
	optimized -lpthread
)
ENDIF(WIN32)
