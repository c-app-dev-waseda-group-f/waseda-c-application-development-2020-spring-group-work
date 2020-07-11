#ifndef GAME_GAMEBOARD_H
#define GAME_GAMEBOARD_H

typedef enum {
    WALL, ROAD , CHECKED_POINT, UNCHECKED_POINT
} MapElement;

typedef struct {
    int x, y;
} MapSize;

typedef struct {
    MapSize mapSize;
    MapElement mapElements[500][500];
    int countOfCheckedPoints;
    int countOfUncheckedPoints;
} GameBoard;

void drawGameBoard(GameBoard gameBoard, int lengthOfElement);

GameBoard newGameBoard();

#endif //GAME_GAMEBOARD_H