
cmake_minimum_required(VERSION 3.14)
project(Qt3D_compute_particles)

# Find the Qt6 packages
find_package(Qt6 COMPONENTS Core 3DCore 3DRender 3DInput 3DExtras Quick Qml REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    src/main.cpp
    src/computematerial.cpp
    src/computeframegraph.cpp
)

set(PROJECT_HEADERS
    src/computematerial.h
    src/computeframegraph.h
)

qt6_add_resources(PROJECT_RESOURCES_QRC
    compute-particles-cpp.qrc
)

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Qt3D_compute_particles
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_RESOURCES_QRC}
    )


target_link_libraries(Qt3D_compute_particles
    PRIVATE
    Qt6::Core
    Qt6::3DCore
    Qt6::3DRender
    Qt6::3DInput
    Qt6::3DExtras
    Qt6::Quick
    Qt6::Qml)

