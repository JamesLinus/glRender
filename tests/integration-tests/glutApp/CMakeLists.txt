cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic")

aux_source_directory(src SOURCES)
add_executable (glutApp ${SOURCES})

find_package(GLUT REQUIRED)

include_directories(
    ${GLUT_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/lib/include/
)

target_link_libraries(glutApp LINK_PUBLIC
    ${GLUT_LIBRARIES}
    glRender
)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})