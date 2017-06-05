cmake_minimum_required(VERSION 3.7)
project(OthelloExam)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Resources/Othello.jpg
        Resources/OthelloBlackTile.png
        Resources/OthelloBlackTileOld.png
        Resources/OthelloWhiteTile.png
        Resources/OthelloWhiteTileOld.png
        board.c
        board.h
        checks.c
        checks.h
        exam_v2.c
        gameLog.c
        gameLog.h
        gui.c
        gui.h
        input.c
        input.h
        makefile
        readmeForLecturer.txt
        utilities.c
        utilities.h)

include_directories(.)
include_directories(Resources)

add_executable(OthelloExam ${SOURCE_FILES})