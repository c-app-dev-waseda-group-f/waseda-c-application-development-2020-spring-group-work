#include <GL/glut.h>
#include "color.h"
#include "gameBoard.h"
#include "character.h"

#include <stdio.h>

void drawPlayer(Player player, int lengthOfElement) {

    glPushMatrix();

    glTranslatef(player.coordinate.x, player.coordinate.y, player.coordinate.z);
    glTranslatef(0.0, 0.0, 0.5);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GREEN]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

    glutSolidSphere((double)lengthOfElement / 2, 100, 100);

    glPopMatrix();
}

void drawEnemies(EnemyList enemyList, int lengthOfElement) {

    glTranslatef(0.0, 0.0, 0.5);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    for (int i = 0; i < enemyList.count; i++) {
        glPushMatrix();
        glTranslatef(enemyList.coordinates[i].x, enemyList.coordinates[i].y, enemyList.coordinates[i].z);
        glutSolidSphere((double)lengthOfElement / 2, 100, 100);
        glPopMatrix();
    }
}

Player newPlayer(GameBoard gameBoard) {

    Player player;

    // TODO: 自動自機生成＜壁と被らないように＞
    CharacterCoordinate c = {0, 0, 0};
    player.coordinate = c;

    return player;
}

EnemyList newEnemyList(GameBoard gameBoard, Player player) {

    EnemyList enemyList;

    // TODO: 自動敵機生成＜自機・壁と被らないように＞
    CharacterCoordinate c[3] = {
            {2.0, 6.0, 0.0},
            {4.0, 3.0, 0.0},
            {1.0, 1.0, 0.0}
    };
    for (int i = 0; i <= (sizeof(c) / sizeof(c[0])); i++) {

        enemyList.coordinates[i] = c[i];
    }
    enemyList.count = (int)(sizeof(c) / sizeof(c[0]));

    return enemyList;
}