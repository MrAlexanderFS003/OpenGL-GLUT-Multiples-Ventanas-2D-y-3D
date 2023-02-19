#include "Puntero.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void Puntero::Cabeza() {
	Actualiza();
	glPushMatrix();
	glLineWidth(2);
	glTranslatef(posX + 0.5f, posY + 0.5f, 0);
	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();
	glPopMatrix();
}

void Puntero::Seleccion() {
	Actualiza();
	glPushMatrix();
	glLineWidth(2);
	glTranslatef(posX + 0.5f, posY + 0.5f, 0);
	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();
	glPopMatrix();
}

void Puntero::Borrar() {
	Actualiza();
	glPushMatrix();
	glLineWidth(2);
	glTranslatef(posX + 0.5f, posY + 0.5f, 0);
	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 0, 0);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();
	glPopMatrix();
}

void Puntero::Actualiza() {
	glutPostRedisplay();
}