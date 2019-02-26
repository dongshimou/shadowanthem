include_directories(${ASIO_DIR}/include)

include_directories(${SHADOW_DIR}/include)

include_directories(${THIRD_DIR}/include)

set(LIBRARY_OUTPUT_PATH ${SHADOW_DIR}/lib)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_DIR)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/include INCLUDE_DIR)

add_library(shadow STATIC ${SRC_DIR} ${INCLUDE_DIR} ${ASIO_DIR}/include)