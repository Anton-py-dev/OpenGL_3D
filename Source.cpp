#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
using namespace std;

double PI = 3.14159;
GLdouble x, y , z;
GLfloat sheet[20000][3];
GLfloat vect = 1.0f;
GLboolean perspective = true;

float radius = 2.5;
int Ou = 57, fi = 26;
int wightScreen = 1280, highScreen = 720;

void coordinate(int Ou, int fi) {
	Ou = Ou % 360;
	z = (float)(radius * sin(Ou * PI / 180) * cos(fi * PI / 180));
	y = (float)(radius * cos(Ou * PI / 180));
	x = (float)(radius * sin(Ou * PI / 180) * sin(fi * PI / 180));
}

void sheetFunc(GLfloat sheet[20000][3]) {
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < 100; i++) {
		for (int k = 0; k < 100; k++) {
			float xt = 0.01f + 0.01f * i;
			float yt = 0.01f + 0.01f * k;
			float zt = sqrt(xt) + sqrt(yt);
			sheet[10000 + i * 100 + k][0] = xt;
			sheet[10000 + i * 100 + k][1] = yt;
			sheet[10000 + i * 100 + k][2] = zt;
		}
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, sheet);
	glPointSize(2.f);
	glDrawArrays(GL_LINES, 0, 20000);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void init(void) {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h) {
	GLfloat wh = (float)w / (float)h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (perspective) {
		gluPerspective(60.0, wh, 0.01, 20.0);
		//glFrustum(-0.5 * wh, 0.5 * wh, -0.5, 0.5, 1.0, 20.0);
	} else {
		glOrtho(-1.0 * wh, 1.0 * wh, -1, 1, -10.0, 10.0);
	}

	glMatrixMode(GL_MODELVIEW);
	
}

void display(void) {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0, 0.0, vect, 0.0);

	// X line Red
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();

	// Y line Green
	glBegin(GL_LINES);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	// Z line Blue
	glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();

	// Wire Dodecahedron Yellow
	glPushMatrix();
		glTranslatef(-1.0f, 0.5f, -0.5f);
		glColor3f(1.0f, 1.0f, 0.0f);
		glScalef(0.1f, 0.1f, 0.1f);
		glutWireDodecahedron();
	glPopMatrix();

	// Solid Square Pink
	glPushMatrix();
		glTranslatef(1.0f, 0.5f, 0.5f);
		glColor3f(1.0f, 0.0f, 1.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0);
		glutSolidCube(0.5);
	glPopMatrix();

	// Sheet White
	sheetFunc(sheet);

	glFlush();
}

void keyboard(unsigned char key, int xt, int yt) {
	switch (key) {
	case 'w':
		Ou -= 2;
		break;
	case 's':
		Ou += 2;
		break;
	case 'a':
		fi -= 2;
		break;
	case 'd':
		fi += 2;
		break;
	case 'r':
		radius -= 0.03;
		break;
	case 'f':
		radius += 0.03;
		break;
	case 'p':
		perspective = true;
		reshape(wightScreen, highScreen);
		break;
	case 'o':
		perspective = false;
		reshape(wightScreen, highScreen);
		break;
	default:
		break;
	}
	
	coordinate(Ou, fi);
	
	if (Ou >= -180 && Ou <= 0) vect = -1;
	else if (Ou > 180) vect = -1;
	else vect = 1;

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(wightScreen, highScreen);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Lab2 Melnyk");
	coordinate(Ou, fi);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}