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
    MapElement mapElements[100][100];
    int countOfCheckedPoints;
    int countOfUncheckedPoints;
    int lengthOfBlock;
} GameBoard;

void drawGameBoard(GameBoard gameBoard);

GameBoard newGameBoard(int lengthOfBlock, MapSize mapSize, double checkPointDensity);

#endif //GAME_GAMEBOARD_H