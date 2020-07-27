#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"
#include "gameBoard.h"
#include "stdio.h"

void drawCheckPoints(GameBoard gameBoard) {

    for (int i = 0; i <= gameBoard.mapSize.x; i ++)
        for (int j = 0; j <= gameBoard.mapSize.y; j ++)
            if (gameBoard.mapElements[i][j] == CHECKED_POINT) {

                double coordinates[5][2];

                for (int k = 0; k < 5; k++) {

                    coordinates[k][0] = cos(M_PI * 2 * k * 2 / 5) * gameBoard.lengthOfBlock / 2;
                    coordinates[k][1] = sin(M_PI * 2 * k * 2 / 5) * gameBoard.lengthOfBlock / 2;
                }

                glPushMatrix();
                glTranslatef(i * gameBoard.lengthOfBlock, j * gameBoard.lengthOfBlock, 0.01);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, color[MAGENTA]);

                glBegin(GL_TRIANGLE_FAN);
                for (int k = 0; k < 5; k++) {

                    glVertex3d(0, 0, 0);
                    glVertex3d(coordinates[k % 5][0], coordinates[k % 5][1], 0);
                    glVertex3d(coordinates[(k + 1) % 5][0], coordinates[(k + 1) % 5][1], 0);
                }
                glEnd();

                glPopMatrix();
            } else if (gameBoard.mapElements[i][j] == UNCHECKED_POINT) {

                double coordinates[5][2];

                for (int k = 0; k < 5; k++) {

                    coordinates[k][0] = cos(M_PI * 2 * k * 2 / 5) * gameBoard.lengthOfBlock / 2;
                    coordinates[k][1] = sin(M_PI * 2 * k * 2 / 5) * gameBoard.lengthOfBlock / 2;
                }

                glPushMatrix();
                glTranslatef(i * gameBoard.lengthOfBlock, j * gameBoard.lengthOfBlock, 0.01);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, color[MAGENTA]);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                glBegin(GL_TRIANGLE_FAN);
                for (int k = 0; k < 5; k++) {

                    glVertex3d(0, 0, 0);
                    glVertex3d(coordinates[k % 5][0], coordinates[k % 5][1], 0);
                    glVertex3d(coordinates[(k + 1) % 5][0], coordinates[(k + 1) % 5][1], 0);
                }
                glEnd();

                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glPopMatrix();
            }
}

// 地面の描画
void drawGround(GameBoard gameBoard) {

    GLdouble normal[3] = { 0.0, 0.0, 1.0 };

    glPushMatrix();

    glNormal3dv(normal);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GRAY]);//灰色
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glBegin(GL_QUADS);
    for (int i = 0; i < gameBoard.mapSize.y; i++)
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

    for (int i = 0; i < gameBoard.mapSize.x; i ++)
        for (int j = 0; j < gameBoard.mapSize.y; j ++)
            if (gameBoard.mapElements[i][j] == WALL) {

                glPushMatrix();
                glTranslatef(i * gameBoard.lengthOfBlock, j * gameBoard.lengthOfBlock, 0.0);
                glTranslatef(0.0, 0.0, 0.5 * gameBoard.lengthOfBlock);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
                glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLUE]);
                glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
                glMaterialf(GL_FRONT, GL_SHININESS, 5.0);
                glutSolidCube(gameBoard.lengthOfBlock);
                glPopMatrix();
            }
}

void drawGameBoard(GameBoard gameBoard) {

    drawGround(gameBoard);
    drawWalls(gameBoard);
    drawCheckPoints(gameBoard);
}

GameBoard removeAllCheckPoints(GameBoard gameBoard) {

    for (int i = 0; i < gameBoard.mapSize.x; i++)
        for (int j = 0; j < gameBoard.mapSize.y; j++)
            if ((gameBoard.mapElements[i][j] == CHECKED_POINT) || (gameBoard.mapElements[i][j] == UNCHECKED_POINT))
                gameBoard.mapElements[i][j] = ROAD;

    gameBoard.countOfUncheckedPoints = 0;
    gameBoard.countOfCheckedPoints = 0;

    return gameBoard;
}

int numberOfRoads(GameBoard gameBoard) {

    int sum = 0;

    for (int i = 0; i < gameBoard.mapSize.x; i++)
        for (int j = 0; j < gameBoard.mapSize.y; j++)
            if (gameBoard.mapElements[i][j] == ROAD)
                sum++;

    return sum;
}

GameBoard  resetCheckPoints(GameBoard gameBoard, double checkPointDensity) {

    srand((unsigned int)time(NULL));

    gameBoard = removeAllCheckPoints(gameBoard);

    int numberOfCheckPoints = floor(numberOfRoads(gameBoard) * checkPointDensity);

    while (gameBoard.countOfUncheckedPoints < numberOfCheckPoints)
        for (int i = 0; i < gameBoard.mapSize.x; i++) {

            if (gameBoard.countOfUncheckedPoints >= numberOfCheckPoints)
                break;

            for (int j = 0; j < gameBoard.mapSize.y; j++) {

                if (gameBoard.countOfUncheckedPoints >= numberOfCheckPoints)
                    break;

                if (gameBoard.mapElements[i][j] == ROAD)
                    if (rand() % 10001 < (int) (checkPointDensity * 10000)) {

                        gameBoard.mapElements[i][j] = UNCHECKED_POINT;
                        gameBoard.countOfUncheckedPoints++;
                    }
            }
        }

    return gameBoard;
}

GameBoard newGameBoard(int lengthOfBlock, MapSize mapSize, double checkPointDensity) {

    GameBoard gameBoard;

    srand((unsigned int)time(NULL));
    // TODO: 壁をボードに入れる（必須）
    // TODO: チェックポイントをボードに入れる（必須）
    gameBoard.mapSize = mapSize;
    for (int i = 0; i < gameBoard.mapSize.x; i++)
        for (int j = 0; j < gameBoard.mapSize.y; j++) {
            if (i % 2 == 1 && j % 2 == 1) { // 棒倒し法の準備。1マス間隔で壁を設置。
                gameBoard.mapElements[i][j] = WALL;
            } else {
                gameBoard.mapElements[i][j] = ROAD;
            }
        }

    int wallDirection, k, l; // wallDirection: 壁を生成する方向。下を0として反時計回りに1ずつ増加。
    // 棒倒し法により左から右に迷路を生成する
    for (int i = 0; i < gameBoard.mapSize.x; i++)
        for (int j = 0; j < gameBoard.mapSize.y; j++) {

            if (i % 2 == 0 || j % 2 == 0)
                continue;
            while (1) {
                if (i == 1) {
                    wallDirection = rand() % 4;
                } else {
                    wallDirection = rand() % 3;
                }

                switch (wallDirection) {
                    case 0: // 下
                        k = i;
                        l = j - 1;
                        break;
                    case 1: // 右
                        k = i + 1;
                        l = j;
                        break;
                    case 2: // 上
                        k = i;
                        l = j + 1;
                        break;
                    case 3: // 左
                        k = i - 1;
                        l = j;
                        break;
                }

                if (k < 0 || l < 0 || k >= gameBoard.mapSize.x || l >= gameBoard.mapSize.y || gameBoard.mapElements[k][l] == WALL)
                    continue;

                gameBoard.mapElements[k][l] = WALL;
                break;
            }
        }

    gameBoard = resetCheckPoints(gameBoard, checkPointDensity);

    gameBoard.lengthOfBlock = lengthOfBlock;

    return gameBoard;
}