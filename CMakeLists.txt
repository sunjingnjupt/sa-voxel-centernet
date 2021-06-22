cmake_minimum_required(VERSION 2.8.3)
project(simpleViewer)
add_definitions(-Wall)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# if has no defined build set it to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${PROJECT_SOURCE_DIR}/cmake_modules"
    )

# Qt5
set(Qt5_DIR "/opt/Qt5.6.0/5.6/gcc_64/lib/cmake/Qt5")
set(Qt5_Widgets "/opt/Qt5.6.0/5.6/gcc_64/lib/cmake/Qt5Widgets")
find_package(Qt5 COMPONENTS Core Widgets Gui Xml OpenGL REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5OpenGL_INCLUDE_DIRS})

set(MY_QT_LIBRARIES
        ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES}
        ${Qt5Gui_LIBRARIES}
        ${Qt5Xml_LIBRARIES}
        ${Qt5OpenGL_LIBRARIES}
        ${Boost_LIBRARIES}
        /usr/lib/x86_64-linux-gnu/libtiff.so.5
        )

# for opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE})

find_package(QGLViewer REQUIRED)
message(STATUS "Linking against Qt libs: ${MY_QT_LIBRARIES}")
message(STATUS "Linking against QGlViewer lib: ${QGLVIEWER_LIBRARY}")

## include
include_directories($CMAKE_CURRENT_SOURCE_DIR)
add_executable(${PROJECT_NAME} main.cpp View.cpp simpleViewer.cpp utils.cpp)
target_link_libraries(
        ${PROJECT_NAME}
        ${QGLVIEWER_LIBRARY}
        ${MY_QT_LIBRARIES}
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY})



