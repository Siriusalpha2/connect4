################################################################################
# Project configuration
################################################################################

cmake_minimum_required(VERSION 3.11)
project(connect4 VERSION 0.1.0 LANGUAGES C CXX)
option(BUILD_TESTING "Enable unit tests" ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


################################################################################
# Output directories for build
################################################################################

# Install command default destination
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

# ---------- Setup Library Output Directory -------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib 
    CACHE PATH "Single Build Directory for all Libraries")

# --------- Setup Static Library Output Directory -------------------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib 
    CACHE PATH "Single Build Directory for all static libraries.")

# --------- Setup the Executable output Directory -------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin 
    CACHE PATH "Single Build Directory for all Executables.")

# --------- Setup the Include output Directory ----------------------
set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/include 
    CACHE PATH "Single Build Directory for all include files.")

################################################################################

add_subdirectory(grid)

add_executable(connect4 main.c)
# target_compile_options(connect4 PRIVATE -Wall -Wextra -pedantic -Werror)
target_compile_features(connect4 PUBLIC c_std_11)
target_link_libraries(connect4 PUBLIC connect4grid)
install(TARGETS connect4 DESTINATION bin)


################################################################################
# Unit tests
################################################################################
if (BUILD_TESTING)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# Enable testing
    include(CTest)
    # Include unit tests folder for compilation
    add_subdirectory(tests)
endif()
################################################################################
    