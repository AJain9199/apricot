cmake_minimum_required(VERSION 3.23)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
project(apricot VERSION 0.1 LANGUAGES C ASM)


set(ROOT_OPTIONS -ffreestanding -nostdlib  -O2 -Wall -I${CMAKE_CURRENT_SOURCE_DIR}/include)

if (NOT DEFINED ARCH)
    set(ARCH x86_64)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    if (ARCH EQUAL x86_64)
        list(APPEND ROOT_OPTIONS --target=x86_64-none-elf -march=x86-64)
    endif()
endif()

set(ROOTLINK_OPTIONS ${ROOT_OPTIONS})

add_subdirectory(kernel/)
add_subdirectory(boot/)

add_custom_target(create_iso ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/initrd/apricot
#        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/fonts/Tamsyn8x16r.psf ${CMAKE_BINARY_DIR}/initrd
        COMMAND ${CMAKE_COMMAND} -E copy ${CONFIG} ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:apricot_kernel> ${ENVFILE} ${CMAKE_BINARY_DIR}/initrd/apricot
        COMMAND $ENV{HOME}/opt/bin/mkbootimg ${CMAKE_BINARY_DIR}/mkbootimg.json apricot.img
        DEPENDS ${ENVFILE} ${CONFIG}
        )
