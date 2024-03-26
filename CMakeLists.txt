cmake_minimum_required(VERSION 3.20)

if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(twenty_four_point VERSION 0.1)
find_package(Qt6 REQUIRED COMPONENTS Quick)
qt_standard_project_setup()
set(CMAKE_AUTORCC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
qt_add_executable(twenty_four_point
    "resources.qrc"
    "include/main.h"
    "include/algorithm_utils.h"
    "include/simple_lexer.h"
    "include/rank_list_storage.h"
    "include/view_ui_controller.h"
    "include/menu_ui_controller.h"
    "include/game_ui_controller.h"
    "include/rank_list_model.h"
    "include/view_rule_ui_controller.h"
    "include/random_nickname.h"
    "src/main.cpp"
    "src/algorithm_utils.cpp"
    "src/simple_lexer.cpp"
    "src/rank_list_storage.cpp"
    "src/view_ui_controller.cpp"
    "src/menu_ui_controller.cpp"
    "src/game_ui_controller.cpp"
    "src/rank_list_model.cpp"
    "src/view_rule_ui_controller.cpp"
    "src/random_nickname.cpp")
target_include_directories(twenty_four_point PRIVATE "include")
qt_add_qml_module(twenty_four_point 
    URI twenty_four_point 
    RESOURCE_PREFIX / 
    VERSION 1.0 
    QML_FILES
        "qml/app.qml"
        "qml/menu.qml"
        "qml/view_rule.qml"
        "qml/start_game.qml"
        "qml/game.qml"
        "qml/rank_list.qml")

if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.27)
    get_target_property(_sources twenty_four_point SOURCES)
    foreach(_source IN ITEMS ${_sources})
        get_source_file_property(_generated ${_source} GENERATED)
        if(_generated)
            set_source_files_properties(${_source} PROPERTIES SKIP_LINTING TRUE)
        endif()
    endforeach()
    unset(_sources)
else()
    message(WARNING "CMake version is less than 3.27, automatic generated files will not be skipped linting.")
endif()

if (VCPKG_TARGET_TRIPLET MATCHES "-windows-static$")
    set_property(TARGET twenty_four_point PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
set_property(TARGET twenty_four_point PROPERTY CXX_STANDARD 17)
target_link_libraries(twenty_four_point PRIVATE Qt6::Quick)
set_target_properties(twenty_four_point PROPERTIES 
    MACOSX_BUNDLE_GUI_IDENTIFIER twenty_four_point.njupt.dev 
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE 
    WIN32_EXECUTABLE TRUE)

install(TARGETS twenty_four_point BUNDLE DESTINATION . LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
