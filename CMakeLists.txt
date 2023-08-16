cmake_minimum_required(VERSION 3.10)

project(test_task)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test_task ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/Castle.cpp ${PROJECT_SOURCE_DIR}/ChessBoard.cpp ${PROJECT_SOURCE_DIR}/Position.cpp)
target_link_libraries(${PROJECT_NAME} pthread)

target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )


