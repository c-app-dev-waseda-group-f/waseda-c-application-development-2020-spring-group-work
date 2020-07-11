#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#define PI (3.14159)

GLfloat pos0[] = { 5.0, 0.0, 0.0, 1.0 };
GLfloat pos1[] = { 0.0, 0.0, 5.0, 1.0 };
enum COLOR { WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GRAY, BLACK };
GLfloat color[][4] = {
		{ 1.0, 1.0, 1.0, 1.0 },
		{ 1.0, 0.0, 0.0, 1.0 },
		{ 0.0, 1.0, 0.0, 1.0 },
		{ 0.0, 0.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 1.0, 1.0 },
		{ 0.0, 1.0, 1.0, 1.0 },
		{ 0.7, 0.7, 0.7, 1.0 },
		{ 0.0, 0.0, 0.0, 1.0 } };//色を増やす場合はここに追加
int mySpecialValue = 0;

#define L 1 // マスの辺の長さ
#define XG 10 //地面x方向のマスの数
#define YG 10 //地面y方向のマスの数

time_t t; // 経過時間 TODO: 時間計測の実装

// 地面の描画
void drawGround() {
	int i, j;
	GLdouble normal[3] = { 0.0, 0.0, 1.0 };

	glPushMatrix();

	glNormal3dv(normal);

    // TODO: チェックポイントの色変え

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GRAY]);//灰色
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glBegin(GL_QUADS);
	for (i = 1; i < YG; i++)
		for (j = 0; j < XG; j++) {
		    GLdouble v[4][3];
		    if (!((i^j) & 1))
                continue;
            v[0][0] = (j + 0 - 0.5)*L;
            v[0][1] = (i + 0 - 0.5)*L;
            v[0][2] = 0;
            v[1][0] = (j + 1 - 0.5)*L;
            v[1][1] = (i + 0 - 0.5)*L;
            v[1][2] = 0;
            v[2][0] = (j + 1 - 0.5)*L;
            v[2][1] = (i + 1 - 0.5)*L;
            v[2][2] = 0;
            v[3][0] = (j + 0 - 0.5)*L;
            v[3][1] = (i + 1 - 0.5)*L;
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
	for (i = 0; i < YG; i++)
		for (j = 0; j < XG; j++) {
            GLdouble v[4][3];
            if ((i^j) & 1)continue;
            v[0][0] = (j + 0 - 0.5)*L;
            v[0][1] = (i + 0 - 0.5)*L;
            v[0][2] = 0;
            v[1][0] = (j + 1 - 0.5)*L;
            v[1][1] = (i + 0 - 0.5)*L;
            v[1][2] = 0;
            v[2][0] = (j + 1 - 0.5)*L;
            v[2][1] = (i + 1 - 0.5)*L;
            v[2][2] = 0;
            v[3][0] = (j + 0 - 0.5)*L;
            v[3][1] = (i + 1 - 0.5)*L;
            v[3][2] = 0;
            glVertex3dv(v[0]);
            glVertex3dv(v[1]);
            glVertex3dv(v[2]);
            glVertex3dv(v[3]);
		}
	glEnd();

	glPopMatrix();
}

int walls[XG][YG]; // 各マスの壁情報
// 壁の描画
void drawWalls() {
    // TODO: 実装
}

// 自機と敵機用
typedef struct {
    double x, y, z;  
} Character;

#define ENEMY_N 3 // 敵機の数

Character player = {0, 0, 0}; // 自機
Character enemies[ENEMY_N] = { // 敵機の配列
    {2.0, 6.0, 0.0},
    {4.0, 3.0, 0.0},
    {1.0, 1.0, 0.0}
};

void drawPlayer() {
	glPushMatrix();

	glTranslatef(player.x, player.y, player.z);
	glTranslatef(0.0, 0.0, 0.5);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GREEN]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

    glutSolidSphere((double)L / 2, 100, 100);
    glPopMatrix();
}

void drawEnemies() {
	int i;
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	glTranslatef(0.0, 0.0, 0.5);
	for (i = 0; i < ENEMY_N; i++) {
		glPushMatrix();
		glTranslatef(enemies[i].x, enemies[i].y, enemies[i].z);
	    glutSolidSphere((double)L/2, 100, 100);
		glPopMatrix();
	}
	glPopMatrix();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawGround();
	drawPlayer();
	drawEnemies();

	glPopMatrix();
	glutSwapBuffers();
}

// 敵との衝突判定 衝突したらtrue
int collision() {
	int i;
	for (i = 0; i < ENEMY_N; i++) {
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

# define CHECKPOINT_N 3 // チェックポイントの数
double checkpoints[3]; // チェックポイントの中心座標
int doneCheckpoints = 0; // 通ったチェックポイントの数
bool isCheckpoint() {
    // TODO: チェックポイントかどうかの確認の実装
    // 今いるのがチェックポイントかつ通っていないチェックポイントだったらtrueを返す
    return false;
}

// 自機の移動
void playerTimerFunc(int value) {
	int groundXMin = 0, groundXMax = (XG-1)*L, groundYMin = 0, groundYMax = (YG-1)*L;
	if (mySpecialValue & (1 << 0)) {
		player.y += 0.1;
		if (collision())player.y -= 0.1;
		if (player.y > groundYMax)player.y = groundYMax;
	} else if (mySpecialValue & (1 << 1)) {
		player.x -= 0.1;
		if (collision())player.x += 0.1;
		if (player.x < groundXMin)player.x = groundXMin;
	} else if (mySpecialValue & (1 << 2)) {
		player.x += 0.1;
		if (collision())player.x -= 0.1;
		if (player.x > groundXMax)player.x = groundXMax;
	} else if (mySpecialValue & (1 << 3)) {
		player.y -= 0.1;
		if (collision())player.y += 0.1;
		if (player.y < groundYMin)player.y = groundYMin;
	}

	//視点を移動
	glLoadIdentity();
	gluLookAt(0.0 + player.x, -10.0 + player.y, 2.0, 0.0 + player.x, 0.0 + player.y, 1.5, 0.0, 0.0, 1.0);

    // TODO: チェックポイントの確認
    if (isCheckpoint()) {
        doneCheckpoints++;
        if (doneCheckpoints == CHECKPOINT_N) {
            // ゴール処理
            return;
        }
    }

    glutTimerFunc(10, playerTimerFunc, 0);
}

// 敵機の移動
void enemiesTimerFunc(int value) {
    int i;
    for (i = 0; i < ENEMY_N; i++) {
        // TODO: 敵機の移動
        enemies[i].x = enemies[i].x;
        enemies[i].y = enemies[i].y;
        enemies[i].z = enemies[i].z;
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

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Maze Game");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
