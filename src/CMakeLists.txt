add_library(functionality Box.cpp Obstacle.cpp Parser.cpp Jumper.cpp)

target_include_directories(functionality INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})