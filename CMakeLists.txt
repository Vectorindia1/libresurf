cmake_minimum_required(VERSION 3.20)
project(LibreSurf VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ─── Build options ────────────────────────────────────────────────────────────
option(BUILD_TESTS "Build unit and integration tests" ON)
option(BUILD_ASAN  "Enable AddressSanitizer"          OFF)
option(ENABLE_CLANG_TIDY "Run clang-tidy during build" OFF)

# ─── Output directories ───────────────────────────────────────────────────────
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ─── Compiler flags ───────────────────────────────────────────────────────────
if(MSVC)
    add_compile_options(/W4 /WX /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
    if(BUILD_ASAN)
        add_compile_options(-fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    endif()
endif()

# ─── CEF ──────────────────────────────────────────────────────────────────────
# Set CEF_ROOT to the path of your CEF distribution.
# Download from: https://cef-builds.spotifycdn.com/index.html
# Example: cmake -DCEF_ROOT=/opt/cef ..
if(NOT DEFINED CEF_ROOT)
    set(CEF_ROOT "" CACHE PATH "Path to CEF prebuilt distribution")
endif()

if(CEF_ROOT)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")
    find_package(CEF REQUIRED)
    include(${CEF_ROOT}/cmake/cef_variables.cmake)
    include_directories(${CEF_ROOT})
    message(STATUS "CEF found at: ${CEF_ROOT}")
else()
    message(WARNING
        "CEF_ROOT not set. Browser core will not be built.\n"
        "  cmake -DCEF_ROOT=/path/to/cef_binary .."
    )
endif()

# ─── Subdirectories ───────────────────────────────────────────────────────────
add_subdirectory(engine/cef)
add_subdirectory(core)
add_subdirectory(networking)
add_subdirectory(privacy)
add_subdirectory(platform/${CMAKE_SYSTEM_NAME_LOWER})

if(BUILD_TESTS)
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)
    add_subdirectory(tests/unit)
    add_subdirectory(tests/integration)
    add_subdirectory(tests/security)
endif()

# ─── Install ──────────────────────────────────────────────────────────────────
install(TARGETS libresurf RUNTIME DESTINATION bin)
