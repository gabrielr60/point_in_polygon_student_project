cmake_minimum_required(VERSION 3.22)
project(LIDAR C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSL REQUIRED gsl)


add_executable(test
    src/main.c
    src/las_reader.c
    src/linalg.c
    src/kdtree.c
    src/heap.c
)

target_include_directories(test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(test
    PRIVATE
        ${GSL_LIBRARIES}
)
