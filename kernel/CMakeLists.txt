add_subdirectory(arch/${ARCH})
add_subdirectory(fs/)

add_executable(apricot_kernel ${CRTI} main.c kutils.c printf.c psf.c color.c screen.c ${ARCH_SRCS} ${FS_SRCS} ${CRTN})
set_target_properties(apricot_kernel PROPERTIES SUFFIX ".elf")
target_compile_options(apricot_kernel PRIVATE ${ROOT_OPTIONS} -fpic -fno-stack-protector)
target_include_directories(apricot_kernel PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" ${ARCH_INCLUDE} "${CMAKE_CURRENT_SOURCE_DIR}/arch/include")
target_compile_definitions(apricot_kernel PRIVATE "BG=40, 44, 52" "FG=171, 178, 191")
target_link_options(apricot_kernel PRIVATE -T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld ${ROOTLINK_OPTIONS} -fpic -fno-stack-protector)