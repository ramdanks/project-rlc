cmake_minimum_required(VERSION 3.16)
project(Application C)

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

# Build executables from all .c files.
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")

# Define application executable, it's properties, and linking.
if(APPLE)
    add_executable(app MACOSX_BUNDLE ${SOURCES})

    set_target_properties(app PROPERTIES
        BUILD_RPATH   "@executable_path/../Frameworks"
        INSTALL_RPATH "@executable_path/../Frameworks"
        MACOSX_RPATH  ON

        OUTPUT_NAME                        "Application"
        MACOSX_BUNDLE_BUNDLE_NAME          "Application"
        MACOSX_BUNDLE_GUI_IDENTIFIER       "com.example.application"
        MACOSX_BUNDLE_INFO_STRING          "Prototype of PROJECT-RLC"
        MACOSX_BUNDLE_ICON_FILE            "AppIcon.icns"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
        MACOSX_BUNDLE_BUNDLE_VERSION       "1"
    )

    find_library(RAYLIB_LIB raylib     PATHS ${RAYLIB_DIR}/lib NO_DEFAULT_PATH)
    find_library(LUAJIT_LIB luajit-5.1 PATHS ${LUAJIT_DIR}/lib NO_DEFAULT_PATH)

    target_link_libraries(app PRIVATE ${RAYLIB_LIB} ${LUAJIT_LIB})

    install(TARGETS app
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION bin
    )

    file(GLOB RAYLIB_DYLIBS "${RAYLIB_DIR}/lib/*.dylib")
    file(GLOB LUAJIT_DYLIBS "${LUAJIT_DIR}/lib/*.dylib")

    install(
        FILES ${RAYLIB_DYLIBS} ${LUAJIT_DYLIBS}
        DESTINATION "$<TARGET_BUNDLE_DIR_NAME:app>/Contents/Frameworks"
    )

    install(
        DIRECTORY content/
        DESTINATION "$<TARGET_BUNDLE_DIR_NAME:app>/Contents/Resources/content"
    )

elseif(WIN32)
    add_executable(app ${SOURCES})

    find_library(RAYLIB_LIB raylib PATHS ${RAYLIB_DIR}/lib NO_DEFAULT_PATH)
    find_library(LUAJIT_LIB lua51  PATHS ${LUAJIT_DIR}/lib NO_DEFAULT_PATH)

    target_link_libraries(app PRIVATE ${RAYLIB_LIB} ${LUAJIT_LIB})

    install(TARGETS app RUNTIME DESTINATION bin)
    install(FILES "${RAYLIB_DIR}/bin/raylib.dll" DESTINATION bin)
    install(FILES "${LUAJIT_DIR}/bin/lua51.dll"  DESTINATION bin)
    install(DIRECTORY content/ DESTINATION content)

else()
    message(FATAL_ERROR "Not supported on this platform.")

endif()

# Dependencies include directories.
target_include_directories(app PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${RAYLIB_DIR}/include
    ${LUAJIT_DIR}/include
)

# Compiler specific options.
if(MSVC)
    add_compile_options(/MP)
    add_compile_options(/W4 /permissive-)

    install(FILES "$<TARGET_PDB_FILE:app>" DESTINATION bin CONFIGURATIONS Debug)
endif()