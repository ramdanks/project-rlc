cmake_minimum_required(VERSION 3.16)
project(MyProject C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Build output goes to root/build/bin and root/build/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Path to your installed dependencies
set(RAYLIB_DIR ${PROJECT_SOURCE_DIR}/.install/raylib)
set(LUAJIT_DIR ${PROJECT_SOURCE_DIR}/.install/luajit)

# Dependencies include directories.
include_directories(${RAYLIB_DIR}/include)
include_directories(${LUAJIT_DIR}/include)

# Dependencies linking directories.
link_directories(${RAYLIB_DIR}/lib)
link_directories(${LUAJIT_DIR}/lib)

# Build executables from all .c files.
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
add_executable(app ${SOURCES})

# Build your executable and link the libs.
target_link_libraries(app PRIVATE raylib)
target_link_libraries(app PRIVATE lua51)

# Target install configuration
install(TARGETS app RUNTIME DESTINATION bin)
install(DIRECTORY content/ DESTINATION content)

# Copy dynamic link library.
if(MSVC)
    install(FILES
        "${RAYLIB_DIR}/bin/raylib.dll"
        DESTINATION bin
    )

    install(FILES
        "${LUAJIT_DIR}/bin/lua51.dll"
        DESTINATION bin
    )
endif()


# Target install extra for debug
if(MSVC)
    install(FILES "$<TARGET_PDB_FILE:app>"
        DESTINATION bin
        CONFIGURATIONS Debug
    )
endif()