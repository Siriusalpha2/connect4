cmake_minimum_required(VERSION 3.0.0)
project(connect4 VERSION 0.1.0 LANGUAGES C)

# include(CTest)
# enable_testing()

add_library(connect4Grid grid.c)

add_executable(connect4 main.c connect4.c)
target_link_libraries(connect4 connect4Grid)


# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
