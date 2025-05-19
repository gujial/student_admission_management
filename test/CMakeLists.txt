file(GLOB_RECURSE SOURCES
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

add_executable(userTest ${SOURCES}
        userTest.cpp)
target_link_libraries(userTest
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        OpenSSL::Crypto
)
target_include_directories(userTest PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/dialogs
        ${PROJECT_SOURCE_DIR}/include/models
)

add_executable(studentTest ${SOURCES}
        studentTest.cpp)
target_link_libraries(studentTest
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        OpenSSL::Crypto
)
target_include_directories(studentTest PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/dialogs
        ${PROJECT_SOURCE_DIR}/include/models
)
