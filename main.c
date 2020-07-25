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

const int windowWidth = 300;
const int windowHeight = 300;

GLfloat pos0[] = { 5.0, 0.0, 0.0, 1.0 };
GLfloat pos1[] = { 0.0, 0.0, 5.0, 1.0 };

GameBoard gameBoard;
Character player;
EnemyList enemyList;

time_t startTime;
double timeLimit;
char readableElapsedTimeInfo[30] = "";

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

	glPopMatrix();
	glutSwapBuffers();
}

void checkPointsInGameBoardIfNeeded() {

    for (int i = 0; i <= gameBoard.mapSize.x; i ++)
        for (int j = 0; j <= gameBoard.mapSize.y; j ++)
            if (gameBoard.mapElements[i][j] == UNCHECKED_POINT)
                if ((fabs(player.coordinate.x - i) < CHECK_POINT_SENSITIVITY) && (fabs(player.coordinate.y - j) < CHECK_POINT_SENSITIVITY)) {

                    gameBoard.mapElements[i][j] = CHECKED_POINT;
                    gameBoard.countOfUncheckedPoints--;
                    gameBoard.countOfCheckedPoints++;
                }
};

void finishGameIfCollidedWithEnemies() {

    for (int i = 0; i < enemyList.count; i++) {
        // TODO: 敵との衝突判定
        if (sqrt(pow(player.coordinate.x - enemyList.enemies[i].coordinate.x, 2) + pow(player.coordinate.y - enemyList.enemies[i].coordinate.y, 2)) < 0.9) {  // ここで感度調整が可能です。
            // TODO: 衝突時のゲームオーバーの処理
            printf("GAME OVER");
            exit(0);
        }
    }
}

void finishGameIfAllPointsChecked() {

    if (gameBoard.countOfUncheckedPoints == 0) {

        // TODO: ゴール処理(成功)
    }
}

void finishGameIfTimeLimitAchieved() {

    if (difftime(clock(), startTime) / 1000 > timeLimit) {

        // TODO: 時間超過時のゲームオーバーの処理(失敗)
    }
}

void finishGameIfNeeded() {

    finishGameIfAllPointsChecked();
    finishGameIfCollidedWithEnemies();
    finishGameIfTimeLimitAchieved();
}

// 自機の移動
void timerFunc(int value) {

	// 視点を移動
	glLoadIdentity();
	gluLookAt(0.0 + player.coordinate.x * gameBoard.lengthOfBlock, -22.0 + player.coordinate.y * gameBoard.lengthOfBlock, 15.0, 0.0 + player.coordinate.x * gameBoard.lengthOfBlock, 0.0 + player.coordinate.y * gameBoard.lengthOfBlock, 1.5, 0.0, 0.0, 1.0);

	// 敵機の移動
    for (int i = 0; i < enemyList.count; i++) {
        // TODO: 敵機の移動
    }

    // チェックポイント検査
    checkPointsInGameBoardIfNeeded();

    // ゲーム終了検査
    finishGameIfNeeded();

    // 時間計測のリフレッシュ
    double timeLeft = timeLimit - difftime(clock(), startTime) / 1000;
    if (timeLeft < 0)
        timeLeft = 0;
    snprintf(readableElapsedTimeInfo, sizeof(readableElapsedTimeInfo) / sizeof(char), "Time Left: %.3fs", timeLeft);

    glutTimerFunc(1, timerFunc, 0);
}

// 移動キー入力に関する部分
void mySpecialFunc(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_UP:
            player = move(player, UP, gameBoard);
            break;
        case GLUT_KEY_LEFT:
            player = move(player, LEFT, gameBoard);
            break;
        case GLUT_KEY_RIGHT:
            player = move(player, RIGHT, gameBoard);
            break;
        case GLUT_KEY_DOWN:
            player = move(player, DOWN, gameBoard);
            break;
	    default:
		    break;
	}
}

void idle(void) {

	glutPostRedisplay();
}

void init(void) {

    gameBoard = newGameBoard(LENGTH_OF_MAP_BLOCK, (MapSize){MAP_SIZE_X, MAP_SIZE_Y}, CHECK_POINT_DENSITY);
    player = newPlayer(gameBoard);
    enemyList = newEnemyList(gameBoard, player);
    timeLimit = 10;
    startTime = clock();

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

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(WINDOWS_NAME);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
