#include <string.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>





static void redraw();
/*Global variables*/
int moving, startx, starty;
float angle=0.0, angle2=0.0;

GLfloat floorVertices[4][3] = {
	{ -15.0, 0.0, 15.0 },
	{ 15.0, 0.0, 15.0 },
	{ 15.0, 0.0, -15.0 },
	{ -15.0, 0.0, -15.0 },
};

static void mouse(int button, int state, int x, int y) {
	float pos;

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			moving = 1;
			startx = x;
			starty = y;
		}
		if (state == GLUT_UP) moving = 0;
	}
	
}

static void motion(int x, int y) {

	if (moving) {
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
		startx = x;
		starty = y;
	}
}



static void drawFloor(void) {
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(floorVertices[0]);
	glTexCoord2f(0.0, 16.0);
	glVertex3fv(floorVertices[1]);
	glTexCoord2f(16.0, 16.0);
	glVertex3fv(floorVertices[2]);
	glTexCoord2f(16.0, 0.0);
	glVertex3fv(floorVertices[3]);
	glEnd();
	glEnable(GL_LIGHTING);
}

static void redraw(void) {
	GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLoadIdentity();
	gluLookAt(40.0, 40.0, 40.0, 0.0, 8.0, 0.0, 0.0, 1.0, 0.0);
	glDisable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glStencilMask(0xffffffff);
	glClearStencil(0x4);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	glPushMatrix();
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	
	drawFloor();
	
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glutSwapBuffers();
}

void Inicio(int argc, char **argv){


	glutInit(&argc, argv);
	glutInitWindowSize(700, 500);
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
#if 1  
	glutInitDisplayString("samples stencil>=3 rgb double depth");
#endif
	glutCreateWindow("Proyecto final");
	if (glutGet(GLUT_WINDOW_STENCIL_SIZE) < 3) {
		printf("halomagic: Sorry, I need at least 3 bits of stencil.\n");
		exit(1);
	}
	glutDisplayFunc(redraw);
	glutIdleFunc(redraw);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	//glutKeyboardFunc(keyboard);
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 1.0, 20.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 8.0, 70.0, 0.0, 8.0, 0.0, 0.0, 1.0, 0.);
	glEnable(GL_LIGHTING);
	
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}