#include <GL/glut.h>
#include "color.h"
#include "gameBoard.h"

// 地面の描画
void drawGround(GameBoard gameBoard) {

    GLdouble normal[3] = { 0.0, 0.0, 1.0 };

    glPushMatrix();

    glNormal3dv(normal);

    // TODO: チェックポイントの色変え

    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GRAY]);//灰色
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glBegin(GL_QUADS);
    for (int i = 1; i < gameBoard.mapSize.y; i++)
        for (int j = 0; j < gameBoard.mapSize.x; j++) {
            GLdouble v[4][3];
            if (!((i^j) & 1))
                continue;
            v[0][0] = (j + 0 - 0.5) * gameBoard.lengthOfBlock;
            v[0][1] = (i + 0 - 0.5) * gameBoard.lengthOfBlock;
            v[0][2] = 0;
            v[1][0] = (j + 1 - 0.5) * gameBoard.lengthOfBlock;
            v[1][1] = (i + 0 - 0.5) * gameBoard.lengthOfBlock;
            v[1][2] = 0;
            v[2][0] = (j + 1 - 0.5) * gameBoard.lengthOfBlock;
            v[2][1] = (i + 1 - 0.5) * gameBoard.lengthOfBlock;
            v[2][2] = 0;
            v[3][0] = (j + 0 - 0.5) * gameBoard.lengthOfBlock;
            v[3][1] = (i + 1 - 0.5) * gameBoard.lengthOfBlock;
            v[3][2] = 0;
            glVertex3dv(v[0]);
            glVertex3dv(v[1]);
            glVertex3dv(v[2]);
            glVertex3dv(v[3]);
        }
    glEnd();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLACK]);//黒
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glBegin(GL_QUADS);
    for (int i = 0; i < gameBoard.mapSize.y; i++)
        for (int j = 0; j < gameBoard.mapSize.x; j++) {
            GLdouble v[4][3];
            if ((i^j) & 1)continue;
            v[0][0] = (j + 0 - 0.5) * gameBoard.lengthOfBlock;
            v[0][1] = (i + 0 - 0.5) * gameBoard.lengthOfBlock;
            v[0][2] = 0;
            v[1][0] = (j + 1 - 0.5) * gameBoard.lengthOfBlock;
            v[1][1] = (i + 0 - 0.5) * gameBoard.lengthOfBlock;
            v[1][2] = 0;
            v[2][0] = (j + 1 - 0.5) * gameBoard.lengthOfBlock;
            v[2][1] = (i + 1 - 0.5) * gameBoard.lengthOfBlock;
            v[2][2] = 0;
            v[3][0] = (j + 0 - 0.5) * gameBoard.lengthOfBlock;
            v[3][1] = (i + 1 - 0.5) * gameBoard.lengthOfBlock;
            v[3][2] = 0;
            glVertex3dv(v[0]);
            glVertex3dv(v[1]);
            glVertex3dv(v[2]);
            glVertex3dv(v[3]);
        }
    glEnd();

    glPopMatrix();
}

// 壁の描画
void drawWalls(GameBoard gameBoard) {

    for (int i = 0; i <= gameBoard.mapSize.x; i ++)
        for (int j = 0; j <= gameBoard.mapSize.y; j ++)
            if (gameBoard.mapElements[i][j] == WALL) {

                glPushMatrix();
                glTranslatef(i, j, 0.0);
                glTranslatef(0.0, 0.0, 0.5);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
                glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLUE]);
                glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
                glMaterialf(GL_FRONT, GL_SHININESS, 5.0);
                glutSolidCube(1);
                glPopMatrix();
            }
}

void drawGameBoard(GameBoard gameBoard) {

    drawGround(gameBoard);
    drawWalls(gameBoard);
}

GameBoard newGameBoard(int lengthOfBlock, MapSize mapSize) {

    GameBoard gameBoard;

    // TODO: 壁をボードに入れる（必須）
    // TODO: チェックポイントをボードに入れる（必須）
    gameBoard.mapSize = mapSize;
    for (int i = 0; i <= gameBoard.mapSize.x; i++)
        for (int j = 0; j <= gameBoard.mapSize.y; j++) {
            gameBoard.mapElements[i][j] = ROAD;
        }

    gameBoard.mapElements[0][1] = WALL;
    gameBoard.mapElements[2][2] = WALL;
    gameBoard.mapElements[2][3] = WALL;
    gameBoard.mapElements[1][0] = UNCHECKED_POINT;
    gameBoard.mapElements[3][0] = UNCHECKED_POINT;
    gameBoard.mapElements[3][5] = CHECKED_POINT;

    gameBoard.countOfCheckedPoints = 0;
    gameBoard.countOfUncheckedPoints = 0;
    gameBoard.lengthOfBlock = lengthOfBlock;

    return gameBoard;
}