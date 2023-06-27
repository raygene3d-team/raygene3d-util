set(NAME raygene3d)

set(UTIL_DIR ${CMAKE_SOURCE_DIR}/${NAME}-util/util)
set(UTIL_SOURCE
	${UTIL_DIR}/broker.h
	${UTIL_DIR}/broker.cpp
)

set(UTIL_BROKER_DIR ${UTIL_DIR}/broker)
set(UTIL_BROKER_SOURCE
	${UTIL_BROKER_DIR}/import_broker.h
	${UTIL_BROKER_DIR}/import_broker.cpp
	${UTIL_BROKER_DIR}/lightmap_broker.h
	${UTIL_BROKER_DIR}/lightmap_broker.cpp
	${UTIL_BROKER_DIR}/environment_broker.h
	${UTIL_BROKER_DIR}/environment_broker.cpp
)

set(SOURCE util.h util.cpp
	${UTIL_SOURCE}
	${UTIL_BROKER_SOURCE}
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
