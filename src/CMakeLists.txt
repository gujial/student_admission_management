file(GLOB_RECURSE SOURCES
        *.cpp
)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        REQUIRED)

find_package(OpenSSL REQUIRED)

add_executable(student_admission_management ${SOURCES}
        ${PROJECT_SOURCE_DIR}/resources.qrc)
target_link_libraries(student_admission_management
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        OpenSSL::Crypto
)
target_include_directories(student_admission_management PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/dialogs
        ${PROJECT_SOURCE_DIR}/include/models
)
