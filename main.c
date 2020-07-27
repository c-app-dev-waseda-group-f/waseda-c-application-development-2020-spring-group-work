#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "configs.h"
#include "color.h"
#include "gameBoard.h"
#include "character.h"
#include "text.h"

///Githubわかんね

typedef enum {
    PLAYING, MENU
} GameStatus;

const int windowWidth = 300;
const int windowHeight = 300;

GLfloat pos1[] = { 0.0, 0.0, 5.0, 1.0 };

GameBoard gameBoard;
Character player;
EnemyList enemyList;

time_t startTime;
double timeLimit;
char readableElapsedTimeInfo[30] = "";

GameStatus status;

void init(void);

//githubテストpull
//初めてのpull。
//＃めでたい
//＃初プルおめ

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawGameBoard(gameBoard);
	drawPlayer(player, (double)gameBoard.lengthOfBlock / 2, gameBoard);
	drawEnemies(enemyList, (double)gameBoard.lengthOfBlock / 2, gameBoard);

	double x = 20;
	double y = 20;
	drawText("Copyright 2020 Group F All Rights Reserved.", x, y, windowHeight, windowWidth);
	drawText(readableElapsedTimeInfo, x, 2 * y, windowHeight, windowWidth);

	if (status==MENU) {
        char readableScoreInfo[30];
        snprintf(readableScoreInfo, sizeof(readableScoreInfo) / sizeof(char), "Score: %d/%d", gameBoard.countOfCheckedPoints, gameBoard.countOfCheckedPoints + gameBoard.countOfUncheckedPoints);
        drawText(readableScoreInfo, x, y * 3, windowHeight, windowWidth);
        drawText("Press END key to quit.", x, y * 4, windowHeight, windowWidth);
        drawText("Press HOME key to retry.", x, y * 5, windowHeight, windowWidth);
    }

	glPopMatrix();
	glutSwapBuffers();
}

void restartGame() {

    gameBoard = newGameBoard(LENGTH_OF_MAP_BLOCK, (MapSize){MAP_SIZE_X, MAP_SIZE_Y}, CHECK_POINT_DENSITY);
    player = newPlayer(gameBoard);
    enemyList = newEnemyList(gameBoard, player);
    timeLimit = gameBoard.mapSize.x * gameBoard.mapSize.y / CHARACTER_UNIT_MOVING_LENGTH * sqrt(CHECK_POINT_DENSITY) * 0.1;
    startTime = clock();
    status = PLAYING;
}

void quitGame() {

    exit(0);
}

void breakGame() {

    status = MENU;
}

void checkPointsInGameBoardIfNeeded() {

    for (int i = 0; i < gameBoard.mapSize.x; i ++)
        for (int j = 0; j < gameBoard.mapSize.y; j ++)
            if (gameBoard.mapElements[i][j] == UNCHECKED_POINT)
                if ((fabs(player.coordinate.x - i) < CHECK_POINT_SENSITIVITY) && (fabs(player.coordinate.y - j) < CHECK_POINT_SENSITIVITY)) {

                    gameBoard.mapElements[i][j] = CHECKED_POINT;
                    gameBoard.countOfUncheckedPoints--;
                    gameBoard.countOfCheckedPoints++;
                }
};

void finishGameIfCollidedWithEnemies() {

    for (int i = 0; i < enemyList.count; i++) {
        if (sqrt(pow(player.coordinate.x - enemyList.enemies[i].coordinate.x, 2) + pow(player.coordinate.y - enemyList.enemies[i].coordinate.y, 2)) < 0.9) {  // ここで感度調整が可能です。
            breakGame();
        }
    }
}

void finishGameIfTimeLimitReached(){

    if (difftime(clock(), startTime) / CLOCKS_PER_SEC > timeLimit) {
        breakGame();
    }
}

void finishGameIfAllPointsChecked() {

    if (gameBoard.countOfUncheckedPoints == 0) {
        breakGame();
    }
}

void finishGameIfNeeded() {

    finishGameIfAllPointsChecked();
    finishGameIfCollidedWithEnemies();
    finishGameIfTimeLimitReached();
}

// 自機の移動
void timerFunc(int value) {

    if (status == PLAYING) {

        // 視点を移動
        glLoadIdentity();
        gluLookAt(0.0 + player.coordinate.x * gameBoard.lengthOfBlock,
                  -22.0 + player.coordinate.y * gameBoard.lengthOfBlock, 15.0,
                  0.0 + player.coordinate.x * gameBoard.lengthOfBlock, 0.0 + player.coordinate.y * gameBoard.lengthOfBlock,
                  1.5, 0.0, 0.0, 1.0);

        // 敵機の移動
        if (((int) clock()) % (CLOCKS_PER_SEC / 50) == 0)
            for (int i = 0; i < enemyList.count; i++)
                while (true) {

                    if (((int) clock()) % (CLOCKS_PER_SEC * 10) == 0) {
                        int r = rand();
                        if (r % 4 == 0) {
                            enemyList.enemies[i].lastMovement = UP;
                        } else if (r % 4 == 1) {
                            enemyList.enemies[i].lastMovement = DOWN;
                        } else if (r % 4 == 2) {
                            enemyList.enemies[i].lastMovement = LEFT;
                        } else if (r % 4 == 3) {
                            enemyList.enemies[i].lastMovement = RIGHT;
                        }
                    }

                    int r = rand();
                    if (r % 4 == 0) {
                        if (enemyList.enemies[i].lastMovement == DOWN) {
                            continue;
                        } else {
                            enemyList.enemies[i] = move(enemyList.enemies[i], UP, gameBoard);
                            break;
                        }
                    } else if (r % 4 == 1) {
                        if (enemyList.enemies[i].lastMovement == UP) {
                            continue;
                        } else {
                            enemyList.enemies[i] = move(enemyList.enemies[i], DOWN, gameBoard);
                            break;
                        }
                    } else if (r % 4 == 2) {
                        if (enemyList.enemies[i].lastMovement == LEFT) {
                            continue;
                        } else {
                            enemyList.enemies[i] = move(enemyList.enemies[i], RIGHT, gameBoard);
                            break;
                        }
                    } else if (r % 4 == 3) {
                        if (enemyList.enemies[i].lastMovement == RIGHT) {
                            continue;
                        } else {
                            enemyList.enemies[i] = move(enemyList.enemies[i], LEFT, gameBoard);
                            break;
                        }
                    }
                }

        // チェックポイント検査
        checkPointsInGameBoardIfNeeded();

        // 時間計測のリフレッシュ
        double timeLeft = timeLimit - difftime(clock(), startTime) / CLOCKS_PER_SEC;
        if (timeLeft < 0)
            timeLeft = 0;
        snprintf(readableElapsedTimeInfo, sizeof(readableElapsedTimeInfo) / sizeof(char), "Time Left: %.3fs", timeLeft);

        // ゲーム終了検査
        finishGameIfNeeded();
    }

    glutTimerFunc(1, timerFunc, 0);
}

// 移動キー入力に関する部分
void mySpecialFunc(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_UP:
            if (status == PLAYING) {
                player = move(player, UP, gameBoard);
            }
            break;
        case GLUT_KEY_LEFT:
            if (status == PLAYING) {
                player = move(player, LEFT, gameBoard);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (status == PLAYING) {
                player = move(player, RIGHT, gameBoard);
            }
            break;
        case GLUT_KEY_DOWN:
            if (status == PLAYING) {
                player = move(player, DOWN, gameBoard);
            }
            break;
        case GLUT_KEY_HOME:
            if (status == MENU) {
                restartGame();
            }
            break;
        case GLUT_KEY_END:
            if (status == MENU) {
                quitGame();
            }
            break;
	    default:
		    break;
	}
}

void idle(void) {

	glutPostRedisplay();
}

void init(void) {

    srand((unsigned int)time(NULL));

    glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutSpecialFunc(mySpecialFunc);

	glutIdleFunc(idle);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1, .1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, -10.0, 2.0, 0.0, 0.0, 1.5, 0.0, 0.0, 1.0);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color[WHITE]);
	glutTimerFunc(1, timerFunc, 0);
}

int main(int argc, char *argv[]) {

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 640);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(WINDOWS_NAME);
	glutDisplayFunc(display);
	init();
	restartGame();
	glutMainLoop();
	return 0;
}
