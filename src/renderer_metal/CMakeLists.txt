# CMake configuration for Metal renderer
cmake_minimum_required(VERSION 3.10)
project(renderer_metal)

set(SRC
    tr_metal_init.c
    tr_metal_main.c
    tr_metal_backend.c
    tr_metal_image.c
    tr_metal_scene.c
)

add_library(renderer_metal STATIC ${SRC})

if(APPLE)
    target_sources(renderer_metal PRIVATE tr_metal_shader.metal)
    target_compile_options(renderer_metal PRIVATE -fobjc-arc)
    target_link_libraries(renderer_metal "-framework Metal" "-framework QuartzCore")
endif()
