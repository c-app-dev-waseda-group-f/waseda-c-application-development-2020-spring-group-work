#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include "gameBoard.h"

typedef enum {
    UP, DOWN , LEFT, RIGHT
} CharacterMovement;

// 自機と敵機用
typedef struct {
    double x, y, z;
} CharacterCoordinate;

typedef struct {
    CharacterCoordinate coordinate;
} Character;

typedef struct {
    Character enemies[1000];
    int count;
} EnemyList;

void drawPlayer(Character player, double radius, GameBoard gameBoard);

void drawEnemies(EnemyList enemyList, double radius, GameBoard gameBoard);

Character move(Character character, CharacterMovement movement, GameBoard gameBoard);

Character newPlayer(GameBoard gameBoard);

EnemyList newEnemyList(GameBoard gameBoard, Character player);

#endif //GAME_CHARACTER_H
