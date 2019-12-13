cmake_minimum_required(VERSION 2.8)

project(matrix_multiplication_parallel)

add_executable(${PROJECT_NAME}1 multiply1.cpp ../common_main.cpp)
target_compile_features(${PROJECT_NAME}1 PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME}1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist"
)

add_executable(${PROJECT_NAME}2 multiply2.cpp ../common_main.cpp)
target_compile_features(${PROJECT_NAME}2 PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME}2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist"
)

add_executable(${PROJECT_NAME}1_schedule_runtime multiply1_schedule_runtime.cpp ../common_main.cpp)
target_compile_features(${PROJECT_NAME}1_schedule_runtime PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME}1_schedule_runtime PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist"
)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME}1 PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(${PROJECT_NAME}2 PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(${PROJECT_NAME}1_schedule_runtime PUBLIC OpenMP::OpenMP_CXX)
endif()
