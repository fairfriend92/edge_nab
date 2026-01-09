cmake_minimum_required(VERSION 3.18)

project(edge_nab
    VERSION 0.1
    DESCRIPTION "Edge AI anomaly detection on NAB (CPU/OpenMP/CUDA)"
    LANGUAGES CXX
)

# ------------------------------------------------------------
# C++ standard
# ------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------
# Build type default
# ------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# ------------------------------------------------------------
# Compiler warnings (systems-friendly)
# ------------------------------------------------------------
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# ------------------------------------------------------------
# Sources
# ------------------------------------------------------------
set(SOURCES
    src/main.cpp
    src/nab_loader.cpp
    src/event_encoder.cpp
    src/temporal_operator.cpp
    src/csv_writer.cpp
)

# ------------------------------------------------------------
# Executable
# ------------------------------------------------------------
add_executable(edge_nab ${SOURCES})

target_include_directories(edge_nab PRIVATE src)

# ------------------------------------------------------------
# Optimization flags (Release)
# ------------------------------------------------------------
if(NOT MSVC)
    target_compile_options(edge_nab PRIVATE
        $<$<CONFIG:Release>:-O3>
    )
endif()
