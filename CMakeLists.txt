cmake_minimum_required(VERSION 3.10)

project(keyframer)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS_DEBUG "-g")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(hover examples/hover.cpp)
include_directories(hover ${CMAKE_SOURCE_DIR}/dep/raylib/include)
target_link_libraries(hover PUBLIC ${CMAKE_SOURCE_DIR}/dep/raylib/lib/libraylib.a)

add_executable(playmodes examples/playmodes.cpp)
include_directories(playmodes ${CMAKE_SOURCE_DIR}/dep/raylib/include)
target_link_libraries(playmodes PUBLIC ${CMAKE_SOURCE_DIR}/dep/raylib/lib/libraylib.a)

add_executable(colors examples/colors.cpp)
include_directories(colors ${CMAKE_SOURCE_DIR}/dep/raylib/include)
target_link_libraries(colors PUBLIC ${CMAKE_SOURCE_DIR}/dep/raylib/lib/libraylib.a)

add_executable(basiccpp examples/basic.cpp)
include_directories(basiccpp ${CMAKE_SOURCE_DIR}/dep/raylib/include)
target_link_libraries(basiccpp PUBLIC ${CMAKE_SOURCE_DIR}/dep/raylib/lib/libraylib.a)

if(APPLE)
    set(FRAMEWORKS "-framework CoreVideo"
                   "-framework IOKit" 
                   "-framework Cocoa"
                   "-framework GLUT" 
                   "-framework OpenGL")
    target_link_libraries(basiccpp PUBLIC ${FRAMEWORKS})
    target_link_libraries(hover PUBLIC ${FRAMEWORKS})
    target_link_libraries(playmodes PUBLIC ${FRAMEWORKS})
    target_link_libraries(colors PUBLIC ${FRAMEWORKS})
endif()