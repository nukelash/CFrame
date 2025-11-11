cmake_minimum_required(VERSION 3.10)

project(keyframer)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS_DEBUG "-g")

add_executable(example example.c)
include_directories(example ${CMAKE_SOURCE_DIR}/dep/raylib/include)
target_link_libraries(example PUBLIC ${CMAKE_SOURCE_DIR}/dep/raylib/lib/libraylib.a)

if(APPLE)
    set(FRAMEWORKS "-framework CoreVideo"
                   "-framework IOKit" 
                   "-framework Cocoa"
                   "-framework GLUT" 
                   "-framework OpenGL")
    target_link_libraries(example PUBLIC ${FRAMEWORKS})
endif()

add_executable(hover hover.c)
include_directories(hover ${CMAKE_SOURCE_DIR}/dep/raylib/include)
target_link_libraries(hover PUBLIC ${CMAKE_SOURCE_DIR}/dep/raylib/lib/libraylib.a)

if(APPLE)
    set(FRAMEWORKS "-framework CoreVideo"
                   "-framework IOKit" 
                   "-framework Cocoa"
                   "-framework GLUT" 
                   "-framework OpenGL")
    target_link_libraries(hover PUBLIC ${FRAMEWORKS})
endif()