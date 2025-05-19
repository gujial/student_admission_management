file(GLOB_RECURSE SOURCES
        *.cpp
        ${PROJECT_SOURCE_DIR}/src/*.cpp
)

set(MAIN_CPP "${PROJECT_SOURCE_DIR}/src/main.cpp")
list(REMOVE_ITEM SOURCES "${MAIN_CPP}")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        REQUIRED)

find_package(OpenSSL REQUIRED)

add_executable(test ${SOURCES})
target_link_libraries(test
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        OpenSSL::Crypto
)
target_include_directories(test PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/dialogs
        ${PROJECT_SOURCE_DIR}/include/models
)
