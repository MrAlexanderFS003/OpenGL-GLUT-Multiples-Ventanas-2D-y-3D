# MULTIPLE VENTANA

En el anterior repositorio ( https://github.com/MrAlexanderFS003/OpenGL-GLUT-SubMenu ) , vimos como crear u usar los submenus y que estos nos facilitaba el acceso a ciertas funciones
ya sea para cambiar el comportamiento del objeto o la ventana. sin embargo este proyecto se van hacer uso las ventanas multiples, estas puden ser 2D | 2D o 3D | 2D y viceversa. Para
crear y usar esto nos guiaremos del siguiente ejemplo:

```C++
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

//Tamaño de la ventana
#define ANCHO 800
#define ALTO 600

int win1, win2;

int main() {
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  
//Configuramos el ventana 1
glutInitWindowSize(ANCHO, ALTO);
glutInitWindowPosition(50, 50);
win1 = glutCreateWindow("2D"); // El valor de la ventana creada se guarda en una variable
  
//Configuramos el ventana 2
glutInitWindowSize(ANCHO,ALTO);
glutInitWindowPosition(300,300);
win2 = glutCreateWindow("3D");

glutSetWindow(win1); //Ahora el valor de "win1" se lo enviamos a la ventana para su creación
glutDisplayFunc(DibujaRenWin2D); // Funcion para la "win1"
CrearMenu(); // Funcion para la "win1"

glutSetWindow(win2); //Ahora el valor de "win2" se lo enviamos a la ventana para su creación
Init();// Funcion para la "win2"
glutDisplayFunc(DibujaRenWin3D); // Funcion para la "win2"
CrearMenuWIn2(); // Funcion para la "win2"

/*
Crear ventana "glutSetWindow()"
Funcion/es que afectara/an a esta ventana (Init,glutDisplayFunc,etc).
*/

glutMainLoop();
return 0;
}

```
------------
# PLANO EN R3/3D
Para este proyecto se tuvo pensado hacer un editor de mapa básico, dicho editor debe editar el mapa en 2D y crear objetos en 3D, en este caso al trabajar con el plano
3D tenemos que tener en cuenta la matriz modelo vista, juento al "gluLookAt()" esta funcion nos ayudara a configurar la posicion de la camara:
### GLULOOKAT
Para configruar la camara en el plano 3D puede ser tedioso o complicado de entender, entonces no hay que hacerse problemas. La funcion "gluLookAt()"
tiene 9 parametros de entrada, y se puede entender de la siguiente manera:

```C++
void Dibujar(){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
//gluLookAt(X,Y,Z,AnguloX,AnguloY,AnguloZ,VectorX,VectorY,VectorZ);
gluLookAt(20,0,20,5,0,0,0,1,0); // Donde VectorX, VectorY y VectorZ casi siempre sera 0 , 1 , 0
}
```

Entonces si se desea caminar en el mapa como en un videojuego como DOOM 1993 se tendria el siguiente codigo:

```C++
//Codigo funcional. CONTROLES : w(avanza), s(Retrocede), a(Gira a la izquierda), d(Gira a la direcha)
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

GLUquadricObj* p = gluNewQuadric();

float rota = 0.0;
//Transformaciones Solido
//float avan = 0.0, vel = 0.06;
float posX = 0;
float posZ = 0;
//Rotacion Cuadrado
float angulo = 0.0;
//Vector direccion
float lx = 0.0f, lz = -1.0f;
//XZ posicion de la camara
float x = 5.0f, z = 11.0f;

typedef struct {
	float w, a, d, s;
}ButtonKeys; ButtonKeys Keys;

void inicializar(){
glClearColor(0.7 , 0.7 , 1, 1.0f);
glEnable(GL_DEPTH_TEST);
}

void Arbol() {
glPushMatrix();
glRotatef(270, 1, 0, 0);
glTranslatef(0, 0, 2.5f);
glColor3ub(13, 173, 49);
glutSolidCone(2, 3, 32, 8);

glTranslatef(0, 0, 1.5);
glColor3ub(40, 180, 99);
glutSolidCone(2, 3, 32, 8);
	
glTranslatef(0, 0, -3);
glColor3ub(35, 155, 86);
glutSolidCone(2, 3, 32, 8);
glPopMatrix();
	
glPushMatrix();
glRotatef(270, 1, 0, 0);
glTranslatef(4, 0, 0);
glColor3ub(88, 214, 141);
glutSolidCone(0.5, 0.7, 32, 8);
glTranslatef(0, 0, 0.5);
glColor3ub(39, 174, 96);
glutSolidCone(0.5, 0.7, 32, 8);
glPopMatrix();

glPushMatrix();
glRotatef(270, 1, 0, 0);
glColor3ub(102, 51, 0);
gluCylinder(p, 0.5f, 0.1f, 5, 32, 8);
glPopMatrix();
}
void Decoracion() {
glPushMatrix();
glColor3ub(237, 187, 153);
glBegin(GL_QUADS);
glVertex3f(-100.0f, 0.0f, -100.0f);
glVertex3f(-100.0f, 0.0f, 100.0f);
glVertex3f(100.0f, 0.0f, 100.0f);
glVertex3f(100.0f, 0.0f, -100.0f);
glEnd();
glPopMatrix();
glPushMatrix();
for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
		glPushMatrix();
		glTranslatef(i * 10.0, 0, j * 10.0);
		Arbol();
		glPopMatrix();
	}
glPopMatrix();

}

void graficar(){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);

// Movimiento de la camara 
float fraccion = 0.05f;
if (Keys.w == 1) { x +=  fraccion * lx; z += lz * fraccion; }
if (Keys.s == 1) { x -=  fraccion * lx; z -= lz * fraccion; }
if (Keys.a == 1) { rota -= 0.01f; lx = sin(rota); lz = -cos(rota);  angulo += 0.6f; }
if (Keys.d == 1) { rota += 0.01f; lx = sin(rota); lz = -cos(rota);  angulo -= 0.6f; }

Decoracion();
glutSwapBuffers();
}

void TecladoAbajo(unsigned char tecla, int xx, int yy ) {
if (tecla == 'w') { Keys.w = 1; }
if (tecla == 's') { Keys.s = 1; }
if (tecla == 'a') { Keys.a = 1; }
if (tecla == 'd') { Keys.d = 1; }

switch (tecla){
case 27:
	exit(0);
default:
	break;
}
glutPostRedisplay();
}

void TecladoArriba(unsigned char tecla , int x, int y) {
if (tecla == 'w') { Keys.w = 0; }
if (tecla == 's') { Keys.s = 0; }
if (tecla == 'a') { Keys.a = 0; }
if (tecla == 'd') { Keys.d = 0; }
glutPostRedisplay();
}


void Actualiza() {
glutPostRedisplay();
}

void redimensionar(int w, int h){
glViewport(0, 0, w, h);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45, (float)w / float(h), 1, 100);
}

int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(1280 , 720);
glutInitWindowPosition(50, 50);
glutCreateWindow("CAMARA");

inicializar();

glutIdleFunc(Actualiza);
glutDisplayFunc(graficar);
glutReshapeFunc(redimensionar);
glutKeyboardFunc(TecladoAbajo);
glutKeyboardUpFunc(TecladoArriba);
glutMainLoop();

return 0;
}

```

### ILUMINACION BÁSICA
La iluminacion que se uso fue ambiental y aunque no halla una fuente de luz esta lo que hace es reducir los colores muy vivos de opengl, en proyectos mas adelante se desarrollaran
todos los tipos de iluminacion que hay. Por el momento se tiene este ejemplo:

```C++
//Esta iluminacion puede ser usada con la misma funcion , pero tener en cuenta que para que la luz le afecte a un 
//objeto o modelo cargado este debe contar con las normales configuradas o cargadas si fuese un modelo 3D.
void Iluminacion(){
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
```
------------
> Nota: El código de este proyecto no habra mucho comentario como en los anteriores, puesto que tengo pensado explicarlos aun mas profundo en proyectos futuros.
Ademas El proyecto se nombre "Mapa-Colision" ,en el siguiente repositorio que se desarrolle se explicará la colisión de objetos en base a la libreria Vector :).

### CAPTURA DEL PROYECTO

![Captura](https://user-images.githubusercontent.com/96871746/219967531-92d78c56-d4f4-47b7-8ca9-ff10d86b0152.png)

# PROGRAMA EN EJECUCIÓN

![GIF](https://user-images.githubusercontent.com/96871746/219965377-9b071828-c50f-46bf-be8c-7d7a01dede29.gif)
