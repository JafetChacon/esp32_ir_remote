# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ir_remote_controller
            DESCRIPTION "IR NEC Codes Emitter ESP32 Based"
            LANGUAGES C)


#add_library(disp7seg STATIC)
#target_include_directories(disp7seg PRIVATE "${PROJECT_SOURCE_DIR}")
#add_subdirectory("lib")

#add_executable(ir_remote)
#target_sources(ir_remote PRIVATE "main/main.c")
#target_link_libraries(ir_remote PRIVATE disp7seg)

#install(TARGETS disp7seg FILE_SET HEADERS)