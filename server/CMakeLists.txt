include_directories(${SHADOW_DIR}/include)
include_directories(${ASIO_DIR}/include)
include_directories(${THIRD_DIR}/include)

link_directories(${SHADOW_DIR}/lib)

add_executable (server "main.cpp" ${SHADOW_DIR}/include ${ASIO_DIR}/include ${THIRD_DIR}/include)

target_include_directories(server PUBLIC ${SHADOW_DIR}/include)

target_link_libraries(server shadow crypto)

