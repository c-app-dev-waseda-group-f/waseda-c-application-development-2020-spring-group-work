#include <GL/glut.h>
#include <stdbool.h>
#include "color.h"
#include "gameBoard.h"
#include "character.h"

void drawPlayer(Character player, double radius) {

    glPushMatrix();

    glTranslatef(player.coordinate.x, player.coordinate.y, player.coordinate.z);
    glTranslatef(0.0, 0.0, 0.5);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GREEN]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

    glutSolidSphere(radius, 100, 100);

    glPopMatrix();
}

void drawEnemies(EnemyList enemyList, double radius) {

    glTranslatef(0.0, 0.0, 0.5);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    for (int i = 0; i < enemyList.count; i++) {
        glPushMatrix();
        glTranslatef(enemyList.enemies[i].coordinate.x, enemyList.enemies[i].coordinate.y, enemyList.enemies[i].coordinate.z);
        glutSolidSphere(radius, 100, 100);
        glPopMatrix();
    }
}

// 壁との衝突判定 衝突したらtrue
bool collidedWithWall(Character character, GameBoard gameBoard) {

    // TODO: 壁との衝突判定

    return false;
}

Character move(Character character, CharacterMovement movement, GameBoard gameBoard) {

    int groundXMin = 0;
    int groundXMax = (gameBoard.mapSize.x - 1) * gameBoard.lengthOfBlock;
    int groundYMin = 0;
    int groundYMax = (gameBoard.mapSize.y - 1) * gameBoard.lengthOfBlock;

    switch (movement) {
        case UP:
            character.coordinate.y += 0.1;
            if (collidedWithWall(character, gameBoard))
                character.coordinate.y -= 0.1;
            if (character.coordinate.y > groundYMax)
                character.coordinate.y = groundYMax;
            break;
        case DOWN:
            character.coordinate.y -= 0.1;
            if (collidedWithWall(character, gameBoard))
                character.coordinate.y += 0.1;
            if (character.coordinate.y < groundYMin)
                character.coordinate.y = groundYMin;
            break;
        case LEFT:
            character.coordinate.x -= 0.1;
            if (collidedWithWall(character, gameBoard))
                character.coordinate.x += 0.1;
            if (character.coordinate.x < groundXMin)
                character.coordinate.x = groundXMin;
            break;
        case RIGHT:
            character.coordinate.x += 0.1;
            if (collidedWithWall(character, gameBoard))
                character.coordinate.x -= 0.1;
            if (character.coordinate.x > groundXMax)
                character.coordinate.x = groundXMax;
            break;
    }
    return character;
}

Character newPlayer(GameBoard gameBoard) {

    Character player;

    // TODO: 自動自機生成＜壁と被らないように＞
    CharacterCoordinate c = {3, 3, 0};
    player.coordinate = c;

    return player;
}

EnemyList newEnemyList(GameBoard gameBoard, Character player) {

    EnemyList enemyList;

    // TODO: 自動敵機生成＜自機・壁と被らないように＞
    CharacterCoordinate c[3] = {
            {2.0, 6.0, 0.0},
            {4.0, 3.0, 0.0},
            {1.0, 1.0, 0.0}
    };
    for (int i = 0; i <= (sizeof(c) / sizeof(c[0])); i++) {

        enemyList.enemies[i].coordinate = c[i];
    }
    enemyList.count = (int)(sizeof(c) / sizeof(c[0]));

    return enemyList;
}