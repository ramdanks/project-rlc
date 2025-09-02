cmake_minimum_required(VERSION 3.16)
project(luajit-wrapper C)

set(LUAJIT_SRC ${CMAKE_SOURCE_DIR}/../../dependencies/luajit/src)

if(NOT MSVC)
    message(FATAL_ERROR "LuaJIT wrapper: only MSVC is supported.")
endif()

if (NOT EXISTS ${LUAJIT_SRC}/msvcbuild.bat)
    message(FATAL_ERROR "msvcbuild.bat not found in ${LUAJIT_SRC}")
endif()

# Build step
add_custom_target(build_luajit ALL
    COMMAND ${CMAKE_COMMAND} -E chdir ${LUAJIT_SRC} msvcbuild.bat
    WORKING_DIRECTORY ${LUAJIT_SRC}
    COMMENT "Building LuaJIT using msvcbuild.bat"
)

# Install step
install(FILES
    ${LUAJIT_SRC}/lua.h
    ${LUAJIT_SRC}/luaconf.h
    ${LUAJIT_SRC}/luajit.h
    ${LUAJIT_SRC}/lauxlib.h
    ${LUAJIT_SRC}/lualib.h
    DESTINATION include
)

install(FILES
    ${LUAJIT_SRC}/lua51.lib
    DESTINATION lib
)

install(FILES
    ${LUAJIT_SRC}/lua51.dll
    ${LUAJIT_SRC}/luajit.exe
    DESTINATION bin
)
