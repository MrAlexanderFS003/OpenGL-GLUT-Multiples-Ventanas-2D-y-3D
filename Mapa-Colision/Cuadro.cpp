#include "Cuadro.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void Cuadro::Dibuja() {
	glPushMatrix();
	glColor3ub(r, g, b);
	glRectd(posX, posY, posX + 1, posY + 1);
	glLineWidth(1);
	glTranslatef(posX + 0.5f, posY + 0.5f, 0);
	glBegin(GL_LINE_LOOP);
		glColor3ub(255, 255, 255);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
	glEnd();
	glPopMatrix();
	//cout << "X: " << posX << " | Y: " << posY << " | X2: " << posX + 1 << " | Y: " << posY + 1<< endl;
}

void Cuadro::Actualiza() { glutPostRedisplay(); }