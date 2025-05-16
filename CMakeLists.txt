cmake_minimum_required(VERSION 4.0)
project(student_admission_management)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/dialogs
        ${PROJECT_SOURCE_DIR}/include/models
)
add_subdirectory(src)
