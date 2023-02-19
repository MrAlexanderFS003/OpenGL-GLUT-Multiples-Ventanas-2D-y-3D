#include "Camara.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

float Camara::x = 20.0f; // 5.0f
float Camara::y = 1.0f;
float Camara::z = 18.0f;
float Camara::fraccion = 0.1f;
int Camara::w;
int Camara::s;

void Camara::Vista() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, 0.0f, z, x + lx, 0.0f, z + lz, 0.0f, 1.0f, 0.0f);
	//gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);
	
}

void Camara::CamaraPosicion() {
	glPushMatrix();
	glTranslatef(x,z,0);
	glRotatef(angulo * 57.2957795,0,0,1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0,0.5);
	glVertex2f(-0.5,-0.5);
	glVertex2f(0,0);
	glVertex2f(0.5,-0.5);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, -1.0);
	glEnd();
	glPopMatrix();
}