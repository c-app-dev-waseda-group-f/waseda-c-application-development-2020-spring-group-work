#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

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

void drawPlayer(Character player, double radius);

void drawEnemies(EnemyList enemyList, double radius);

Character move(Character character, CharacterMovement movement, GameBoard gameBoard);

Character newPlayer(GameBoard gameBoard);

EnemyList newEnemyList(GameBoard gameBoard, Character player);

#endif //GAME_CHARACTER_H
