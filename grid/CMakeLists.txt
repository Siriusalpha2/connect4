
add_library(connect4grid Connect4Grid.c)
target_include_directories(connect4grid PUBLIC 
                           ${PROJECT_SOURCE_DIR})
install(TARGETS connect4grid DESTINATION lib)
install(FILES Connect4Grid.h DESTINATION include)