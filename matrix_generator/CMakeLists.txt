cmake_minimum_required(VERSION 2.8)

project(matrix_generator)

set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist")

FILE(GLOB SOURCES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist
)
