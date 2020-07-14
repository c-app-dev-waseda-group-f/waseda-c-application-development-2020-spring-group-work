#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "color.h"
#include "gameBoard.h"
#include "character.h"

///Githubわかんね

GLfloat pos0[] = { 5.0, 0.0, 0.0, 1.0 };
GLfloat pos1[] = { 0.0, 0.0, 5.0, 1.0 };

GameBoard gameBoard;
Character player;
EnemyList enemyList;

time_t t; // 経過時間 TODO: 時間計測の実装

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawGameBoard(gameBoard);
	drawPlayer(player, (double)gameBoard.lengthOfBlock / 2);
	drawEnemies(enemyList, (double)gameBoard.lengthOfBlock / 2);

	glPopMatrix();
	glutSwapBuffers();
}

void checkPointsInGameBoardIfNeeded() {

    // TODO: 自機がチェックポイントにいる場合、そのチェックポイントを Checked にする
};

void finishGameIfCollidedWithEnemies() {

    for (int i = 0; i < enemyList.count; i++) {
        // TODO: 敵との衝突判定
        if (false) {
            // TODO: 衝突時のゲームオーバーの処理
        }
    }
}

void finishGameIfAllPointsChecked() {

    if (gameBoard.countOfUncheckedPoints == 0) {

        // TODO: ゴール処理
    }
}

void finishGameIfNeeded() {

    finishGameIfAllPointsChecked();
    finishGameIfCollidedWithEnemies();
}

// 自機の移動
void timerFunc(int value) {

	// 視点を移動
	glLoadIdentity();
	gluLookAt(0.0 + player.coordinate.x, -22.0 + player.coordinate.y, 15.0, 0.0 + player.coordinate.x, 0.0 + player.coordinate.y, 1.5, 0.0, 0.0, 1.0);

	// 敵機の移動
    for (int i = 0; i < enemyList.count; i++) {
        // TODO: 敵機の移動
    }

    // チェックポイント検査
    checkPointsInGameBoardIfNeeded();

    // ゲーム終了検査
    finishGameIfNeeded();

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

    gameBoard = newGameBoard(1);
    player = newPlayer(gameBoard);
    enemyList = newEnemyList(gameBoard, player);

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
	glutCreateWindow("Maze Game");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
