cmake_minimum_required(VERSION 3.5)

project(3DViewer VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER gcc)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

include_directories(
    Models
    View
    View/GLWidget
    Controllers
    Library/QGifImage
)
add_subdirectory(Library/QGifImage)

set(PROJECT_SOURCES
        Models/geometry.h
        Models/geometry_elements.h
        Models/geometry.cc
        Models/geometry_glstate.h
        Models/geometry_observer.h
        Models/geometry_subject.h
        Models/geometry_subject.cc
        Models/geometry_normalization_parameters.h
        Models/geometry_normalization_parameters.cc
        Models/geometry_normalization_parameters_builder.h
        Models/geometry_normalization_parameters_builder_interface.h
        Models/geometry_normalization_parameters_builder.cc
        Models/geometry_defaults.h
        Models/geometry_defaults.cc
        View/mainwindow.cc
        View/mainwindow.h
        View/mainwindow.ui
        View/GLWidget/glmodel.h
        View/GLWidget/glmodel.cc
        View/GLWidget/glmodel_projection.h
        Controllers/geometry_controller.h
        Controllers/geometry_controller_interface.h
        Controllers/geometry_controller.cc
        main.cc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(3DViewer PUBLIC QGifImage)

set_target_properties(3DViewer PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS 3DViewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer)
endif()
