cmake_minimum_required(VERSION 3.12)
project(Saper)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)

IF (WIN32)
    set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()


find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

add_library(minesweeper_core src/MinesweeperBoard.cpp)
target_include_directories(minesweeper_core PUBLIC include)

add_executable(minesweeper src/main.cpp src/MinesweeperBoard.cpp src/MSTextController.cpp src/MSBoardTextView.cpp)
target_link_libraries(minesweeper sfml-graphics)
