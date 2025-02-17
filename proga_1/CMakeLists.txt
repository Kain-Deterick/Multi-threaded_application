
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/proga_1")

set(SOURCE1 "${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp")
set(HEADER1 "${CMAKE_CURRENT_SOURCE_DIR}/headers/working_with_buffer.h" 
            "${CMAKE_CURRENT_SOURCE_DIR}/headers/conn_linux_socket.h")

add_executable(proga_1_client ${SOURCE1} ${HEADER1})

