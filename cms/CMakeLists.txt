add_library(cms CenteredMenu.cpp)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

target_include_directories(cms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cms PUBLIC menu ${CURSES_LIBRARIES})