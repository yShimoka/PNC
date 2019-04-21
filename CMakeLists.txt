# Require cmake version 3.
cmake_minimum_required(VERSION 3.0.0)


# Create the project.
project(PNC VERSION 0.1.0)
set_property(GLOBAL PROPERTY C_STANDARD 99)
set(CMAKE_C_FLAGS "-std=c99")

# Enable C compiling.
enable_language(C)
# --- Load platform and architecture info ---
    # Check if a target system was specified.
    if("$ENV{PLATFORM}" STREQUAL "")
        message(WARNING "No target system specified. Defaulting to host system (${CMAKE_HOST_SYSTEM_NAME})")
        set(ENV{PLATFORM} "${CMAKE_HOST_SYSTEM_NAME}")
    endif()

    # Check if a target processor was specified.
    if("$ENV{ARCH}" STREQUAL "")
        message(WARNING "No target architecture specified. Defaulting to host system (${CMAKE_HOST_SYSTEM_PROCESSOR})")
        set(ENV{ARCH} "${CMAKE_HOST_SYSTEM_PROCESSOR}")
    endif()
    # Log the used toolchain file for this build.
    message(STATUS "Loaded toolchain file at : ${CMAKE_TOOLCHAIN_FILE}")
# ---

# --- Load build info ---
    # Check the debug status of this build.
    if($ENV{DEBUG})
        # Build in debug mode.
        set(CMAKE_BUILD_TYPE Debug)
        message(STATUS "Building in Debug mode.")
    else()
        # Build in release mode.
        set(CMAKE_BUILD_TYPE Release)
        message(STATUS "Building in Release mode.")
    endif()

    # Set the output directory.
    set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/Build)

    # Set the output file structure.
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# ---

# --- Load library info ---
    # Set the library loading path.
    set(CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/Libraries")
    set(CMAKE_FRAMEWORK_PATH "${PROJECT_SOURCE_DIR}/Frameworks")

    # Prepare the platform-specific linkers.
    message(STATUS "Loading linker file : Scripts/Linkers/${CMAKE_SYSTEM_NAME}.cmake")
    include("Scripts/Linkers/${CMAKE_SYSTEM_NAME}.cmake")
# ---

# Include all the header files.
include_directories(${PROJECT_SOURCE_DIR}/Headers)

# Compile all the sources.
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} Sources/*.c)
add_executable(
    PNC
    ${SOURCES}
)