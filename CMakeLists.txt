cmake_minimum_required(VERSION 3.9)
project(connect4 VERSION 0.1.0 LANGUAGES C)

# include(CTest)
# enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_executable(connect4 main.c connect4.c grid.c)
target_compile_features(connect4 PUBLIC c_std_11)
target_compile_options(connect4 PRIVATE -Wall -Wextra -pedantic -Werror)
install(TARGETS connect4 ARCHIVE DESTINATION bin)
