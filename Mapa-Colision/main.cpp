/*
	Hecho por Max Flores Saldaña , Usando la programación orientada a Objetos en C++.
	Si desea ver la documentacion de GLUT: https://www.opengl.org/resources/libraries/glut/spec3/spec3.html
*/

/// CODIGO REUTILIZADO DE https://github.com/MrAlexanderFS003/OpenGL-GLUT-SubMenu

#include "Cuadro.h"
#include "Puntero.h"
#include "Camara.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

//Tamaño de la ventana
#define ANCHO 800
#define ALTO 600

//Tamaño de la Cuadricula
#define COLUMNAS 50
#define FILAS 50

//Funciones

//Objetos
Cuadro ptn;
vector<Cuadro>gen;
Puntero punt;
Camara camera;

//Variables usadas para almacenar los calculos obtenidos
float objX = 20.0f, objY = 20.0f, MobjX = 0.0f, MobjY = 0.0f;
float x = 5.0f, y = 0.0f, z = 18.0f;
int valor = 0, cont = 0, val = 0, win = 0, win2 = 0, codigo = 0, Verifica = 0;
bool bandera = false, bandPint = false, ActivaMapa = false, mosCamara = false;
bool Bor = false;

//Variables para el raton
float rota = 0.0;
bool firstMouse = true;
float lastX = 0;
float lastY = 0;
float win_w = ANCHO;
float win_h = ALTO;
float My = 1.0f;

typedef struct {
	int w, a, d, s, space;
}ButtonKeys; ButtonKeys Keys;

void Almacen();

void Init() {
	glShadeModel(GL_SMOOTH);

	const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

	const GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat high_shininess[] = { 100.0f };

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void Cuadricula() {
	glColor3ub(142, 142, 142);
	glLineWidth(1.0);
	for (int x = 0; x < COLUMNAS; x++) {
		for (int y = 0; y < FILAS; y++) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(x, y);
			glVertex2f(x + 1, y);
			glVertex2f(x + 1, y + 1);
			glVertex2f(x, y + 1);
			glEnd();
		}
	}
}

//Esta funcion crea las acciones de las opciones que eligamos en el Menu
void Accion() {
	if (val == 1) {
		ptn.setRGB(255, 0, 0);
		gen.push_back(ptn);
	}

	if (val == 2) {
		ptn.setRGB(251, 255, 0);
		gen.push_back(ptn);
	}

	if (val == 3) {
		ptn.setRGB(0, 19, 255);
		gen.push_back(ptn);
	}

	if (val == 4) {
		bandera = true;
	}

	if (val == 5) {
		bandera = false;
	}

	if (val == 6) {
		gen.clear();
		val = NULL;
	}

	if (val == 7) {
		exit(0);
	}
	
	if (val == 8) {
		bandPint = false;
		Bor = false;
	}

	if (val == 9) {
		bandPint = true;
		Bor = false;

		ptn.setPosX(punt.getPosX());
		ptn.setPosY(punt.getPosY());
		gen.push_back(ptn);
	}

	if (val == 10) {
		ActivaMapa = false;
	}

	if (val == 11) {
		ActivaMapa = true;
	}
	
	if (val == 12) {
		mosCamara = true;
	}

	if (val == 13) {
		mosCamara = false;
	}
	
	if (val == 14) {
		Bor = true;
		bandPint = false;
	}

	glutPostRedisplay();
}


void Piso() {
	glPushMatrix();
	//glTranslatef(0, 1, 0);
	glPushMatrix();
	//glScalef(3.0, 3.0, 3.0);
	glNormal3i(0, -1, 0);
	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2i(1, 0); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2i(1, 1); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2i(0, 1); glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void Cubo() {
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glPushMatrix();
	//glScalef(3.0, 3.0, 3.0);
	glNormal3i(0, -1, 0);
	// LADO TRASERO: lado blanco
	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2i(1, 0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2i(1, 1); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2i(0, 1); glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// LADO DERECHO: lado morado
	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2i(1, 0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2i(1, 1); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2i(0, 1); glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// LADO IZQUIERDO: lado verde
	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2i(1, 0); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2i(1, 1); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2i(0, 1); glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// LADO SUPERIOR: lado azul
	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2i(1, 0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2i(1, 1); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2i(0, 1); glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// LADO INFERIOR: lado rojo
	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2i(1, 0); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2i(1, 1); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2i(0, 1); glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void Almacen() {
	for (int i = 0; i < gen.size(); i++) {
		glPushMatrix();
		if (gen[i].getRGB() == 255) {
			glPushMatrix();
			glColor3ub(255, 0, 0);
			glTranslatef(gen[i].getPosX(), 0, gen[i].getPosY());
			Cubo();
			glPopMatrix();
		}

		if (gen[i].getRGB() == 506) {
			glPushMatrix();
			glColor3ub(251, 255, 0);
			glTranslatef(gen[i].getPosX(), 0, gen[i].getPosY());
			Piso();
			glPopMatrix();
		}
		
		if (gen[i].getRGB() == 274) {
			glPushMatrix();
			glColor3ub(0, 19, 255);
			glTranslatef(gen[i].getPosX(), 1, gen[i].getPosY());
			Piso(); // Techo
			glPopMatrix();
		}
		glPopMatrix();
	}
}

void DibujaRenWin2D() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNAS, 1.0f, FILAS, -1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPushMatrix();
	if (bandera == true) { Cuadricula(); }
	glPopMatrix();
	Accion();
	
	for (int i = 0; i < gen.size(); i++) {
		if (i > 0) {
			if (i > i - 1) {
				glPushMatrix(); gen[i - 1].Dibuja(); glPopMatrix();
			}
			if (bandPint) { glPushMatrix(); punt.Cabeza(); glPopMatrix(); }
		}
		Verifica = gen[i].getRGB();
	}

	if (Bor == true) {
		glPushMatrix(); punt.Borrar(); glPopMatrix();
		for (int i = 0; i < gen.size(); i++) {
			/*
			glPushMatrix();
			glBegin(GL_LINES);
			glVertex2d(punt.getPosX(), punt.getPosY());
			glVertex2d(gen[i].getPosX(), gen[i].getPosY());
			glEnd();
			glPopMatrix();
			*/
			if (punt.getPosX() == gen[i].getPosX() && punt.getPosY() == gen[i].getPosY()) {
				gen.erase(gen.begin() + i);
			}
		}
	}

	if (bandPint == false ) {
		glPushMatrix(); punt.Seleccion(); glPopMatrix();
	}

	if (mosCamara == true) {
		camera.CamaraPosicion();
	}

	glutSwapBuffers();

}

void DibujaRenWin3D() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.Vista();

	float fraccion = camera.getFraccion();
	if (Keys.w == 1) { x += fraccion * camera.getLx(); z += camera.getLz() * fraccion; camera.setX(x); camera.setZ(z); }
	if (Keys.s == 1) { x -= fraccion * camera.getLx(); z -= camera.getLz() * fraccion; camera.setX(x); camera.setZ(z); }
	
	Accion();

	Almacen();
	glutSwapBuffers();
}

void Actualiza() {

	glutPostRedisplay();
}

void TecladoAbajo(unsigned char tecla, int x, int y) {
	if (ActivaMapa == true) {
		if (tecla == 'w') { Keys.w = 1; }
		if (tecla == 's') { Keys.s = 1; }
		if (tecla == 'a') { Keys.a = 1; }
		if (tecla == 'd') { Keys.d = 1; }
	}

	switch (tecla) {
	case 27:
		exit(0);
	default:
		break;
	}
	glutPostRedisplay();
}

void TecladoArriba(unsigned char tecla, int x, int y) {
	if (ActivaMapa == true) {
		if (tecla == 'w') { Keys.w = 0; }
		if (tecla == 's') { Keys.s = 0; }
		if (tecla == 'a') { Keys.a = 0; }
		if (tecla == 'd') { Keys.d = 0; }
	}
	glutPostRedisplay();
}


void TecladoWin2(unsigned char tecla, int x, int y) {
	if (bandPint == true && Verifica != 0) {
		if (tecla == 'w') {
			ptn.setPosY(ptn.getPosY() + 1);
			gen.push_back(ptn);
			punt.setPosY(punt.getPosY() + 1);
		}

		if (tecla == 's') {
			ptn.setPosY(ptn.getPosY() - 1);
			gen.push_back(ptn);
			punt.setPosY(punt.getPosY() - 1);
		}

		if (tecla == 'a') {
			ptn.setPosX(ptn.getPosX() - 1);
			gen.push_back(ptn);
			punt.setPosX(punt.getPosX() - 1);
		}
		if (tecla == 'd') {
			ptn.setPosX(ptn.getPosX() + 1);
			gen.push_back(ptn);
			punt.setPosX(punt.getPosX() + 1);
		}
	}

	if (bandPint == false) {
		if (tecla == 'w') {
			punt.setPosY(punt.getPosY() + 1);
		}

		if (tecla == 's') {
			punt.setPosY(punt.getPosY() - 1);
		}

		if (tecla == 'a') {
			punt.setPosX(punt.getPosX() - 1);
		}
		if (tecla == 'd') {
			punt.setPosX(punt.getPosX() + 1);
		}
	}

	switch (tecla) {
	case 27:
		exit(0);
	default:
		break;
	}
	glutPostRedisplay();
}

void PassiveMouse(int x, int y) {
	if (ActivaMapa == true) {
		if (firstMouse) {
			lastX = x;
			lastY = y;
			firstMouse = false;
		}

		float xoffset = x - lastX;
		float yoffset = lastY - y; 

		if (xoffset / 10 > 0) {
			//rota += 0.035f;
			rota += 0.05f;
			camera.setAngulo(rota);
			camera.setLx(sin(rota)); camera.setLz(-cos(rota));
		}
		else {
			if (xoffset / 10 < 0) {
				rota -= 0.05f;
				camera.setAngulo(rota);
				camera.setLx(sin(rota)); camera.setLz(-cos(rota));
			}
		}

		if (yoffset / 10 > 0) {
			My += 0.05f;
			camera.setY(My);
		}
		else {
			if (yoffset / 10 < 0) {
				My -= 0.05f;
				camera.setY(My);
			}
		}

		lastX = x;
		lastY = y;

		glutPostRedisplay();

		//this is the main thing that keeps it from leaving the screen
		if (x < 100 || x > win_w - 100) {  //you can use values other than 100 for the screen edges if you like, kind of seems to depend on your mouse sensitivity for what ends up working best
			lastX = win_w / 2;   //centers the last known position, this way there isn't an odd jump with your cam as it resets
			lastY = win_h / 2;
			glutWarpPointer(win_w / 2, win_h / 2);  //centers the cursor
		}
		else if (y < 100 || y > win_h - 100) {
			lastX = win_w / 2;
			lastY = win_h / 2;
			glutWarpPointer(win_w / 2, win_h / 2);
		}
	}
}

//Creamos una funcion "Menu" para comprobar cada valor 
void Menu(int value) {
	//Si al crear el menu el valor es 0 : destruye la ventana y la cierra 
	if (value == 0) { glutDestroyWindow(win); exit(0); }
	else { val = value; } // de otro modo el valor se agrega a otra variable 
	glutPostRedisplay();
}

/*
	glutAddMenuEntry(Nombre, Numero de orden);

	glutAddSubMenu(Nombre, Variable del menu Creado);
*/

void CrearMenu() {
	int OpcColor = glutCreateMenu(Menu); // Crea el Menu
	glutAddMenuEntry("Rojo", 1); // En este caso SubMenu
	glutAddMenuEntry("Amarillo", 2);
	glutAddMenuEntry("Azul", 3);
	int OpcCuad = glutCreateMenu(Menu);
	glutAddMenuEntry("Mostrar Cuadricula", 4);
	glutAddMenuEntry("Ocultar Cuadricula", 5);
	glutAddMenuEntry("Limpiar Pantalla", 6);
	glutAddMenuEntry("Cerrar todo", 7);
	glutAddMenuEntry("Usar Mapa 3D", 11);
	glutAddMenuEntry("Mostrar Camara 2D", 12);
	glutAddMenuEntry("Ocultar Camara 2D", 13);
	int OpcPunt = glutCreateMenu(Menu);
	glutAddMenuEntry("Seleccionar", 8);
	glutAddMenuEntry("Pintar", 9);
	glutAddMenuEntry("Borrador", 14);
	int subMenu = glutCreateMenu(Menu);// Crea el Menu
	glutAddSubMenu("Colores", OpcColor); // Aqui se crea el menu principal del submenu
	glutAddSubMenu("Puntero",OpcPunt);
	glutAddSubMenu("Ventana", OpcCuad);

	//Cada vez que hagamos click derecho saldra el submenu
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void CrearMenuWIn2() {
	int OpcCuad = glutCreateMenu(Menu);
	glutAddMenuEntry("Cerrar todo", 7);
	glutAddMenuEntry("Usar Mapa 2D", 10);
	int subMenu = glutCreateMenu(Menu);// Crea el Menu
	// Aqui se crea el menu principal del submenu
	glutAddSubMenu("Ventana", OpcCuad);

	//Cada vez que hagamos click derecho saldra el submenu
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void redimensionar(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);
}

int main() {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(ANCHO, ALTO);
	glutInitWindowPosition(50, 50);
	win = glutCreateWindow("SUBMENU-CUADRICULAS"); // El valor de la ventana creada se guarda en una variable

	glutInitWindowSize(ANCHO,ALTO);
	glutInitWindowPosition(300,300);
	win2 = glutCreateWindow("3D");

	glutSetWindow(win);
	glutDisplayFunc(DibujaRenWin2D);
	CrearMenu();
	glutIdleFunc(Actualiza);
	glutKeyboardFunc(TecladoWin2);

	glutSetWindow(win2);
	Init();
	glutDisplayFunc(DibujaRenWin3D);
	CrearMenuWIn2();
	glutReshapeFunc(redimensionar);
	glutKeyboardFunc(TecladoAbajo);
	glutKeyboardUpFunc(TecladoArriba);
	glutPassiveMotionFunc(PassiveMouse);

	glutMainLoop();
	return 0;
}