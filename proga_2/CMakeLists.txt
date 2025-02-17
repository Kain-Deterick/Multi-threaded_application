cmake_minimum_required(VERSION 3.10)

project (infotecs_2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/proga_2")

set(SOURCE2 "${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp")
set(HEADER2 "${CMAKE_CURRENT_SOURCE_DIR}/headers/Socket_server.h")

add_executable(proge_2_server ${SOURCE2} ${HEADER2})

