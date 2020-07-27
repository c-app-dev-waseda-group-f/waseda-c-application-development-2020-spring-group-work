#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"
#include "gameBoard.h"

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

    for (int i = 0; i <= gameBoard.mapSize.x; i ++)
        for (int j = 0; j <= gameBoard.mapSize.y; j ++)
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

                if (gameBoard.mapElements[i][j] == ROAD){
                  //まだ甘いが。。。
                  //チェックポイントが横並びになるのも防いでしまうが、どうでしょうか
                  if(gameBoard.mapElements[i-1][j]!=ROAD&&gameBoard.mapElements[i+1][j]!=ROAD&&gameBoard.mapElements[i][j-1]!=ROAD&&gameBoard.mapElements[i][j+1]!=ROAD){
                    break;
                  }else{
                    if (rand() % 10001 < (int) (checkPointDensity * 10000)) {

                      gameBoard.mapElements[i][j] = UNCHECKED_POINT;
                      gameBoard.countOfUncheckedPoints++;
                    }
                  }

                }

            }
        }

    return gameBoard;
}

GameBoard newGameBoard(int lengthOfBlock, MapSize mapSize, double checkPointDensity) {

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

    gameBoard = resetCheckPoints(gameBoard, checkPointDensity);

    gameBoard.lengthOfBlock = lengthOfBlock;

    return gameBoard;
}
