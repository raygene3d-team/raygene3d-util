set(NAME raygene3d)

set(UTIL_DIR ${CMAKE_SOURCE_DIR}/${NAME}-util/util)
set(UTIL_SOURCE
	${UTIL_DIR}/property.h
	${UTIL_DIR}/property.cpp
	${UTIL_DIR}/storage.h
	${UTIL_DIR}/storage.cpp
	${UTIL_DIR}/types.h
	${UTIL_DIR}/types.cpp
)
set(UTIL_STORAGE_DIR ${UTIL_DIR}/storage)
set(UTIL_STORAGE_SOURCE
	${UTIL_STORAGE_DIR}/local_storage.h
	${UTIL_STORAGE_DIR}/local_storage.cpp
	${UTIL_STORAGE_DIR}/remote_storage.h
	${UTIL_STORAGE_DIR}/remote_storage.cpp
)

set(SOURCE util.h util.cpp
	${UTIL_SOURCE}
	${UTIL_STORAGE_SOURCE}
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
