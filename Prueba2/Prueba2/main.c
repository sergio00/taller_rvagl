#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>



  
struct NodoStruct { 
    void* contenido; 
    struct NodoStruct* next; 
}NodoStruct; 
typedef struct NodoStruct* Nodo; 

struct ListaStruct { 
     Nodo inicio; 
     Nodo fin; 
}ListaStruct; 
typedef struct ListaStruct* Lista;   

struct ArcoStruct { 
    Nodo inicio; 
    Nodo fin; 
	//int visitado;
}ArcoStruct; 
typedef struct ArcoStruct* Arco; 

struct MeshStruct { 
	Lista Vertices;
    Lista Superficies;
}MeshStruct; 
typedef struct MeshStruct* Mesh; 

struct SuperficieStruct { 
    Lista Vertices;
	//float normal[3];
}MeshStruct; 
typedef struct SuperficieStruct* Superficie; 

Nodo crearNodo(void* content);
Lista crearLista();
void doList(Lista l,void (*hacer)( void*));
Arco unirNodos(Nodo inicio, Nodo fin);
int estaDentroLista(Lista list,void* c);
int listaSize(Lista l);
static void redraw();
void agregarVertice(Superficie s,Nodo n);
void agregarSuperficie(Mesh m,Superficie s);
Superficie crearSuperficie();
Mesh crearMesh();





/*Global variables*/
int moving, startx, starty;
float angle=0.0, angle2=0.0;



GLfloat floorVertices[4][3] = {
	{ -15.0, 0.0, 15.0 },
	{ 15.0, 0.0, 15.0 },
	{ 15.0, 0.0, -15.0 },
	{ -15.0, 0.0, -15.0 },
};

GLfloat primeVertices[5][3] = {
	{ -7.0, 0.0, 7.0 },
	{ 7.0, 0.0, 7.0 },
	{ 7.0, 0.0, -7.0 },
	{ -7.0, 0.0, -7.0 },
	{ 0.0, 12.0, 0.0 },
};




static void mouse(int button, int state, int x, int y) {


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
}


Mesh crearPiramide(void) {
	


	glBegin(GL_TRIANGLE_STRIP);
	//caras
	glVertex3fv(primeVertices[0]);
	glVertex3fv(primeVertices[4]);
	glVertex3fv(primeVertices[1]);
	glVertex3fv(primeVertices[4]);
	glVertex3fv(primeVertices[2]);
	glVertex3fv(primeVertices[4]);
	glVertex3fv(primeVertices[3]);
	glVertex3fv(primeVertices[4]);
	glVertex3fv(primeVertices[0]);
	//base
	glVertex3fv(primeVertices[0]);
	glVertex3fv(primeVertices[1]);
	glVertex3fv(primeVertices[2]);
	glVertex3fv(primeVertices[3]);
	
	glEnd();
	
}
static void drawPiramide(Mesh piramide) {

	  for (i = 5; i >= 0; i--) {
    glBegin(type);
    glNormal3fv(&n[i][0]);

    glTexCoord2f(0.0, 0.0); glVertex3fv(&v[faces[i][0]][0]);
    glTexCoord2f(0.0, 1.0); glVertex3fv(&v[faces[i][1]][0]);
    glTexCoord2f(1.0, 1.0); glVertex3fv(&v[faces[i][2]][0]);
    glTexCoord2f(1.0, 0.0); glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }

	
}
void drawLightArrow(GLfloat move_x, GLfloat move_y, GLfloat move_z){
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(1.0, 1.0, 0.0);
		glTranslatef(move_x, move_y, move_z);

		//glRotatef(90, 0, 0, 1);
		glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0, 0, 0);
			glVertex3f(2, 1, 1);
			glVertex3f(2, -1, 1);
			glVertex3f(2, -1, -1);
			glVertex3f(2, 1, -1);
			glVertex3f(2, 1, 1);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
			glVertex3f(0.1, 0, 0);
			glVertex3f(5, 0, 0);
		glEnd();
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

static void redraw(void) {


	GLfloat lightColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat lightPosition[]         = {-15.0, 15.0, 0.0, 0.0};

	GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);
	glLoadIdentity();
	gluLookAt(40.0, 40.0, 40.0, 0.0, 8.0, 0.0, 0.0, 1.0, 0.0);
	glDisable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	//glStencilMask(0xffffffff);
	//glClearStencil(0x4);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	glPushMatrix();
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	

	/*
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
			glEnable(GL_LIGHT0);
			//glRotatef(angle2, 1.0, 0.0, 0.0);
			//glRotatef(angle, 0.0, 1.0, 0.0);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
			glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);		
			//drawLightArrow(15.0, 20.0, 0.0, LIGHT_NEAR);

			drawLightArrow(lightPosition[0],lightPosition[1],lightPosition[2]);
		glPopMatrix();
		
	//drawFloor();
	glColor3f(0.5,1.0,0.3);

	*/glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
			glEnable(GL_LIGHT0);
			glRotatef(angle2, 1.0, 0.0, 0.0);
			glRotatef(angle, 0.0, 1.0, 0.0);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
			glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);		
			//drawLightArrow(15.0, 20.0, 0.0, LIGHT_NEAR);

			drawLightArrow(lightPosition[0],lightPosition[1],lightPosition[2]);
		glPopMatrix();


	
   //glutSolidSphere (7.0, 20, 16);
  
   /*
		glPushMatrix();
	drawLightArrow(10.0, 10.0, 10.0);
	glPopMatrix();*/
	drawPiramide();
	 glFlush ();
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glutSwapBuffers();
}

void init(void) 
{
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
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
	

	init();

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

int main(int argc, char **argv)
{
	Inicio(argc, argv);
	glutMainLoop();
	return 0;
}

void agregarNodo(Lista l,Nodo n) {
	Nodo ultimo =l->inicio;
	while(1){
		if(ultimo==NULL){
			l->inicio=n;
			l->fin=n;
			return;
		}
		if(ultimo->next==NULL){
			ultimo->next=n;
			l->fin=n;
			return;
		}else{
			ultimo=ultimo->next;
		}
	}
}

Mesh crearMesh() {
	Mesh m = (Mesh)(malloc(sizeof(MeshStruct)));
	m->Superficies=crearLista();
	m->Vertices=crearLista();
    return m;
}
Superficie crearSuperficie() {
	Superficie s = (Superficie)(malloc(sizeof(SuperficieStruct)));
	s->Vertices=crearLista();
    return s;
}
void agregarSuperficie(Mesh m,Superficie s) {
	agregarNodo(m->Superficies,crearNodo(s));
}
void agregarVertice(Superficie s,Nodo n) {
	agregarNodo(s->Vertices,n);
}
Nodo crearNodo(void* content) {
	Nodo n = (Nodo)(malloc(sizeof(NodoStruct)));
	n->contenido=content;
	n->next=NULL;
    return n;
}
Lista crearLista() {
	Lista l = (Lista)(malloc(sizeof(ListaStruct)));
	l->inicio=NULL;
	l->fin=NULL;
    return l;
}
void doList(Lista l,void (*hacer)( void*)){
	Nodo ultimo = NULL;
	for(ultimo=l->inicio; ultimo != NULL; ultimo=ultimo->next){
		hacer((ultimo->contenido));
	}
}
Arco unirNodos(Nodo inicio, Nodo fin){
	Arco a = (Arco)(malloc(sizeof(ArcoStruct)));
	a->inicio = inicio;
	a->fin = fin;
	return a;
}
int estaDentroLista(Lista list,void* c){
	Nodo n1;
	for(n1=list->inicio;n1!=NULL;n1=n1->next){
		if(n1->contenido==c){
			return 1;//ya esta alli
		}
	}
	return 0;
}
int listaSize(Lista l){
	Nodo n;
	int i=0;
	for(n=l->inicio;n!=NULL;n=n->next){
		i++;
	}
	return i;
}