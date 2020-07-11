#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

// 自機と敵機用
typedef struct {
    double x, y, z;
} CharacterCoordinate;

typedef struct {
    CharacterCoordinate coordinate;
} Player;

typedef struct {
    CharacterCoordinate coordinates[1000];
    int count;
} EnemyList;

void drawPlayer(Player player, int lengthOfElement);

void drawEnemies(EnemyList enemyList, int lengthOfElement);

Player newPlayer(GameBoard gameBoard);

EnemyList newEnemyList(GameBoard gameBoard, Player player);

#endif //GAME_CHARACTER_H
