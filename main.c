#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "color.h"
#include "gameBoard.h"
#include "character.h"

const int L = 1;

GLfloat pos0[] = { 5.0, 0.0, 0.0, 1.0 };
GLfloat pos1[] = { 0.0, 0.0, 5.0, 1.0 };
int mySpecialValue = 0;

GameBoard gameBoard;
Player player;
EnemyList enemyList;

time_t t; // 経過時間 TODO: 時間計測の実装

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawGameBoard(gameBoard, L);
	drawPlayer(player, L);
	drawEnemies(enemyList, L);

	glPopMatrix();
	glutSwapBuffers();
}

// 敵との衝突判定 衝突したらtrue
int collision() {
	for (int i = 0; i < enemyList.count; i++) {
        // TODO: 敵との衝突判定
		if (false) {
            // TODO: 衝突時のゲームオーバーの処理
			return true;
		}
	}
	return false;
}

// 壁との衝突判定 衝突したらtrue
int wallCollision() {
    // TODO: 壁との衝突判定の実装
    return false;
}

void checkPointsInGameBoardIfNeeded() {

    // TODO: 自機がチェックポイントにいる場合、そのチェックポイントを Checked にする
};

void finishGameIfNeeded() {

    if (gameBoard.countOfUncheckedPoints == 0) {

        // TODO: ゴール処理
        return;
    }
}

// 自機の移動
void playerTimerFunc(int value) {

	int groundXMin = 0, groundXMax = (gameBoard.mapSize.x - 1) * L, groundYMin = 0, groundYMax = (gameBoard.mapSize.y - 1) * L;
	if (mySpecialValue & (1 << 0)) {
		player.coordinate.y += 0.1;
		if (collision())player.coordinate.y -= 0.1;
		if (player.coordinate.y > groundYMax)player.coordinate.y = groundYMax;
	} else if (mySpecialValue & (1 << 1)) {
		player.coordinate.x -= 0.1;
		if (collision())player.coordinate.x += 0.1;
		if (player.coordinate.x < groundXMin)player.coordinate.x = groundXMin;
	} else if (mySpecialValue & (1 << 2)) {
		player.coordinate.x += 0.1;
		if (collision())player.coordinate.x -= 0.1;
		if (player.coordinate.x > groundXMax)player.coordinate.x = groundXMax;
	} else if (mySpecialValue & (1 << 3)) {
		player.coordinate.y -= 0.1;
		if (collision())player.coordinate.y += 0.1;
		if (player.coordinate.y < groundYMin)player.coordinate.y = groundYMin;
	}

	//視点を移動
	glLoadIdentity();
	gluLookAt(0.0 + player.coordinate.x, -10.0 + player.coordinate.y, 2.0, 0.0 + player.coordinate.x, 0.0 + player.coordinate.y, 1.5, 0.0, 0.0, 1.0);

    checkPointsInGameBoardIfNeeded();
    finishGameIfNeeded();

    glutTimerFunc(10, playerTimerFunc, 0);
}

// 敵機の移動
void enemiesTimerFunc(int value) {
    for (int i = 0; i < enemyList.count; i++) {
        // TODO: 敵機の移動
    }

	glutTimerFunc(10, enemiesTimerFunc, 0);
}

// 移動キー入力に関する部分
void mySpecialFunc(int key, int x, int y) {
	switch (key) {
        case GLUT_KEY_UP:
            mySpecialValue |= 1 << 0;//mySpecialValueの1bit目を1にする
            break;
        case GLUT_KEY_LEFT:
            mySpecialValue |= 1 << 1;//mySpecialValueの2bit目を1にする
            break;
        case GLUT_KEY_RIGHT:
            mySpecialValue |= 1 << 2;//mySpecialValueの3bit目を1にする
            break;
        case GLUT_KEY_DOWN:
            mySpecialValue |= 1 << 3;//mySpecialValueの4bit目を1にする
            break;
	    default:
		    break;
	}
}

// 移動キー入力に関する部分
void mySpecialUpFunc(int key, int x, int y) {
	switch (key) {
        case GLUT_KEY_UP:
            mySpecialValue &= ~(1 << 0);//mySpecialValueの1bit目を0にする
            break;
        case GLUT_KEY_LEFT:
            mySpecialValue &= ~(1 << 1);//mySpecialValueの2bit目を0にする
            break;
        case GLUT_KEY_RIGHT:
            mySpecialValue &= ~(1 << 2);//mySpecialValueの3bit目を0にする
            break;
        case GLUT_KEY_DOWN:
            mySpecialValue &= ~(1 << 3);//mySpecialValueの4bit目を0にする
            break;
        default:
            break;
	}

}

void idle(void) {
	glutPostRedisplay();
}

void init(void) {

    gameBoard = newGameBoard();
    player = newPlayer(gameBoard);
    enemyList = newEnemyList(gameBoard, player);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutSpecialFunc(mySpecialFunc);
	glutSpecialUpFunc(mySpecialUpFunc);

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
	playerTimerFunc(0);
	enemiesTimerFunc(0);
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
