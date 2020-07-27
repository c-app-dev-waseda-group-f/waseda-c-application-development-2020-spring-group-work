#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "configs.h"
#include "color.h"
#include "gameBoard.h"
#include "character.h"

void drawPlayer(Character player, double radius, GameBoard gameBoard) {

    glPushMatrix();

    glTranslatef(player.coordinate.x * gameBoard.lengthOfBlock, player.coordinate.y * gameBoard.lengthOfBlock, player.coordinate.z);
    glTranslatef(0.0, 0.0, radius);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GREEN]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

    glutSolidSphere(radius, 100, 100);

    glPopMatrix();
}

void drawEnemies(EnemyList enemyList, double radius, GameBoard gameBoard) {

    glTranslatef(0.0, 0.0, radius);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    for (int i = 0; i < enemyList.count; i++) {
        glPushMatrix();
        glTranslatef(enemyList.enemies[i].coordinate.x * gameBoard.lengthOfBlock, enemyList.enemies[i].coordinate.y * gameBoard.lengthOfBlock, enemyList.enemies[i].coordinate.z);
        glutSolidSphere(radius, 100, 100);
        glPopMatrix();
    }
}

// 壁との衝突判定 衝突したらtrue
bool collidedWithWall(Character character, GameBoard gameBoard) {

    int sx = floor(character.coordinate.x);
    int sy = floor(character.coordinate.y);
    int ex = ceil(character.coordinate.x);
    int ey = ceil(character.coordinate.y);

    if (fabs(sx - character.coordinate.x) <= 0.01) {

        ex = sx;
    } else if (fabs(ex - character.coordinate.x) <= 0.01) {

        sx = ex;
    }

    if (fabs(sy - character.coordinate.y) <= 0.01) {

        ey = sy;
    } else if (fabs(ey - character.coordinate.y) <= 0.01) {

        sy = ey;
    }

    for (int i = sx; i <= ex; i ++)
        for (int j = sy; j <= ey; j ++)
            if (gameBoard.mapElements[i][j] == WALL) {

                return true;
            }

    return false;
}

Character move(Character character, CharacterMovement movement, GameBoard gameBoard) {

    int groundXMin = 0;
    int groundXMax = (gameBoard.mapSize.x - 1) * gameBoard.lengthOfBlock;
    int groundYMin = 0;
    int groundYMax = (gameBoard.mapSize.y - 1) * gameBoard.lengthOfBlock;

    switch (movement) {
        case UP:
            character.coordinate.y += CHARACTER_UNIT_MOVING_LENGTH / LENGTH_OF_MAP_BLOCK;
            if (collidedWithWall(character, gameBoard))
                character.coordinate.y -= CHARACTER_UNIT_MOVING_LENGTH / LENGTH_OF_MAP_BLOCK;
            if (character.coordinate.y > groundYMax)
                character.coordinate.y = groundYMax;
            break;
        case DOWN:
            character.coordinate.y -= CHARACTER_UNIT_MOVING_LENGTH / LENGTH_OF_MAP_BLOCK;
            if (collidedWithWall(character, gameBoard))
                character.coordinate.y += CHARACTER_UNIT_MOVING_LENGTH / LENGTH_OF_MAP_BLOCK;
            if (character.coordinate.y < groundYMin)
                character.coordinate.y = groundYMin;
            break;
        case LEFT:
            character.coordinate.x -= CHARACTER_UNIT_MOVING_LENGTH / LENGTH_OF_MAP_BLOCK;
            if (collidedWithWall(character, gameBoard))
                character.coordinate.x += CHARACTER_UNIT_MOVING_LENGTH / LENGTH_OF_MAP_BLOCK;
            if (character.coordinate.x < groundXMin)
                character.coordinate.x = groundXMin;
            break;
        case RIGHT:
            character.coordinate.x += CHARACTER_UNIT_MOVING_LENGTH / LENGTH_OF_MAP_BLOCK;
            if (collidedWithWall(character, gameBoard))
                character.coordinate.x -= CHARACTER_UNIT_MOVING_LENGTH / LENGTH_OF_MAP_BLOCK;
            if (character.coordinate.x > groundXMax)
                character.coordinate.x = groundXMax;
            break;
    }
    return character;
}

Character newPlayer(GameBoard gameBoard) {

    Character player;

    for (int i = 0; i < gameBoard.mapSize.x; i++)
        for (int j = 0; j < gameBoard.mapSize.y; j++)
            if (gameBoard.mapElements[i][j] == ROAD) {

                player.coordinate.x = i;
                player.coordinate.y = j;
                player.coordinate.z = 0;

                return player;
            }
}

EnemyList newEnemyList(GameBoard gameBoard, Character player) {

    EnemyList enemyList;

    // TODO: 自動敵機生成＜自機・壁と被らないように＞
    CharacterCoordinate c[3] = {
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}
    };
    double x0 = 0.0;
    double y0 = 0.0;
    for(int i = 0; i < 3; i++){
        //gameboardの右下、右上、左上の順で一機ずつ設定
        int count = 1;
        if(i == 0) x0 += gameBoard.mapSize.x / 2;
        if(i == 1) y0 += gameBoard.mapSize.y / 2;
        if(i == 2) x0 -= gameBoard.mapSize.x / 2;
        while(count){
            double x = (double)(rand() % (gameBoard.mapSize.x / 2));
            double y = (double)(rand() % (gameBoard.mapSize.y / 2));
            if(gameBoard.mapElements[(int)(x + x0)][(int)(y + y0)] != WALL){
                c[i].x = x + x0;
                c[i].y = y + y0;
                count--;
            }
        }
    }

    for (int i = 0; i <= (sizeof(c) / sizeof(c[0])); i++) {

        enemyList.enemies[i].coordinate = c[i];
    }
    enemyList.count = (int)(sizeof(c) / sizeof(c[0]));

    return enemyList;
}