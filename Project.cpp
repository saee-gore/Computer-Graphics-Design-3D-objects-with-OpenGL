#include <math.h>
#include <GL\glut.h>
//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near = 5, far = 20;
const float REGION_DIM = 4;
GLfloat fov = 45.0, aspect = 1;
GLfloat theta = 30, phi = 60, rho = 10;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat alpha = 0, beta = 0, gama = 0;
GLfloat dAlpha = 5, dBeta = 5, dGama = 5;
GLfloat a = 0.5, b = 2, c = 1;
GLfloat dA = 0.1, dB = 0.1, dC = 0.1;
GLfloat direction = 1.0;
GLfloat lightPos[] = { 2, 4, 6, 1 };

const GLfloat DtoR = 0.017453;

typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

typedef struct lightingStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
} lightingStruct;

materialStruct* currentMaterials;
lightingStruct* currentLighting;

materialStruct brassMaterials = {
	{ 0.33, 0.22, 0.03, 1.0 },
{ 0.78, 0.57, 0.11, 1.0 },
{ 0.99, 0.91, 0.81, 1.0 },
27.8
};

materialStruct redPlasticMaterials = {
	{ 0.3, 1.0, 0.0, .1 },
{ 0.6, 0.0, 0.0, .1 },
{ 0.8, 0.6, 0.6, .1 },
32.0
};

materialStruct whiteShineyMaterials = {
	{ 1.0, 1.0, 1.0, 1.0 },
{ 1.0, 1.0, 1.0, 1.0 },
{ 1.0, 1.0, 1.0, 1.0 },
100.0
};

lightingStruct whiteLighting = {
	{0.0, 0.0, 0.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0}
};

lightingStruct coloredLighting = {
	{0.2, 0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0, 1.0},
	{0.0, 0.0, 1.0, 1.0}
};

void materials(materialStruct*);
void lighting(lightingStruct*);

//----- prototypes ----------
void display1(void);
void display2(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void keys(unsigned char k, int x, int y);
void mouse(int, int, int, int);
void idle(void);

void midbtn_menu(int);
void menu(int);

void materials(materialStruct* m)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m->shininess);
}

void lighting(lightingStruct* li)
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, li->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, li->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, li->specular);

}

void midbtn_menu(int id)
{}

void display1(void)
{
	GLUquadricObj *myObject;
	myObject = gluNewQuadric();
	GLenum myStyle = GLU_LINE;  

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), rho*cos(theta*DtoR)*sin(phi*DtoR), 0, 0, 0, 0, 1, 0);
	
	materials(currentMaterials);
	lighting(currentLighting);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	gluQuadricDrawStyle(myObject, myStyle);

	glLineWidth(3);

	//------------- the nosecone -----------------
	glPushMatrix();
	glRotatef(alpha, 1, 0, 0);	//rotation about the x-axis
	glutSolidCone(a, 1, 50, 50);
	glTranslatef(0, 0, -2);
	gluCylinder(myObject, 0.5, 0.5, 2, 60, 20);
	gluDisk(myObject, 0, 0.5, 60, 20);
	glTranslatef(0, 0, -0.5);
	glutSolidCone(a, 1, 50, 50);
	glPopMatrix();
	//-----------------------------------------------
	
	glTranslatef(-2, 3, 0);	// shift to the side
	//--------------------------------------------------------------
	glPushMatrix();
	glRotatef(gama, 1, 0, 0); //rotation about the y-axis
	glutSolidSphere(1, 30, 20);
	glPopMatrix();

	//--------------------------------------------------------------------
	glTranslatef(2, -3, 0);	

	glTranslatef(3, 0, 0);	
	//---------- the  rocket body -------------

	glPushMatrix();
	glRotatef(gama, 0, 1, 0); //rotation about the y-axis
	gluDisk(myObject, 0, 0.5, 60, 20);
	gluCylinder(myObject, 0.5, 0.5, 2, 60, 20);
	glTranslatef(0, 0, -0.5);
	glutSolidCone(a, 1, 50, 50);
	glTranslatef(0, 0, 2.5);
	gluDisk(myObject, 0, 0.5, 60, 20);
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void display2(void)
{
	GLUquadricObj *myObject;
	myObject = gluNewQuadric();
	GLenum myStyle = GLU_LINE;  //Seleted from GLU_LINE, GLU_POINT, GLU_FILL, GLU_SILHOUETTE, etc.

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), rho*cos(theta*DtoR)*sin(phi*DtoR), 0, 0, 0, 0, 1, 0);

	materials(currentMaterials);
	lighting(currentLighting);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	gluQuadricDrawStyle(myObject, myStyle);

	glLineWidth(3);
	//---------------------------------------------------- 
	
	glutSolidSphere(1, 30, 20);
	glRotatef(gama * -1, 0, 1, 0);
	glRotatef(alpha * -1, 1, 0, 0);
	glTranslatef(2, 2, 0);
	glTranslatef(2, 0, 0);
	glRotatef(beta, 0, 1, 0);
	glutSolidCone(a, 1, 30, 30);
	glTranslatef(0, 0, -2);
	gluCylinder(myObject, 0.5, 0.5, 2, 60, 20);
	glTranslatef(0, 0, -0.5);
	glutSolidCone(a, 1, 50, 50);
	gluCylinder(myObject, 0.5, 0.5, 2, 60, 20);
	gluDisk(myObject, 0, 0.5, 60, 20);
	glTranslatef(0, 0, -0.5);
	glutSolidCone(a, 1, 50, 50);

	glutSwapBuffers();
	glutPostRedisplay();	// work with GLUT_DOUBLE

}



void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	currentMaterials = &whiteShineyMaterials;
	
	materials(currentMaterials);
	currentLighting = &whiteLighting;
	lighting(currentLighting);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


	float ratio = ww * 1.0 / (wh*1.0);


	glClearColor(0, 0, 0, 1.0);	// background color; default black; (R, G, B, Opacity)
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -1.0 * REGION_DIM;
		top = REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -1.0 * REGION_DIM / ratio;
		top = REGION_DIM / ratio;
	}

	glFrustum(left, right, bottom, top, near, far);	
	glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w * 1.0 / (h*1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -1.0 * REGION_DIM;
		top = REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -1.0 * REGION_DIM / ratio;
		top = REGION_DIM / ratio;
	}
	
	glFrustum(left, right, bottom, top, near, far);	
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		
	ww = w;
	wh = h;
}

void idle()
{
	alpha += 0.01;
	beta += 0.01;
	gama += 0.01;

	if (alpha >= 360)
		alpha -= 360;

	if (beta >= 360)
		beta -= 360;

	if (gama >= 360)
		gama -= 360;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		alpha += dAlpha * direction;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		beta += dBeta * direction;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gama += dGama * direction;
	}
}

void keys(unsigned char k, int x, int y)
{
	switch (k)
	{
	case '1':
		glutIdleFunc(NULL);
		break;
	case '2':
		glutIdleFunc(idle);
		break;
	case '3':
		currentMaterials = &redPlasticMaterials;
		break;
	case '4':
		currentMaterials = &whiteShineyMaterials;
		break;
	case '5':
		currentMaterials = &brassMaterials;
		break;
	case '6':
		currentLighting = &whiteLighting;
		break;
	case '7':
		currentLighting = &coloredLighting;
		break;
	case 'q':
		exit(0);
		break;
	}

}


void menu(int id)
{
	if (id == 1)
	{
		glutDisplayFunc(display2);
	}
	else if (id == 2)
	{
		glutDisplayFunc(display1);
	}
	else if (id == 3)
	{
		exit(0);
	}
}

void specialKeys(int k, int x, int y)
{
	if (k == GLUT_KEY_LEFT)
		theta -= dTheta;
	else if (k == GLUT_KEY_RIGHT)
		theta += dTheta;
	else if (k == GLUT_KEY_UP)
	{
		if (phi > dPhi)
			phi -= dPhi;
		else if (phi == dPhi)
			phi = 0.01;		
	}
	else if (k == GLUT_KEY_DOWN)
	{
		if (phi <= 180 - dPhi)
			phi += dPhi;
	}
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(ww, wh);	
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("Saee's Final Graphic Project");
	init();
	glutDisplayFunc(display1);
	int display_menu;
	display_menu = glutCreateMenu(menu);
	glutAddMenuEntry("Start the animation", 1); //display2 will be called
	glutAddMenuEntry("Stop the animation", 2);//display1 will be called as it is the default display
	glutAddMenuEntry("Exit", 3);//Exits the program
	glutCreateMenu(midbtn_menu);
	glutAddSubMenu("What would you like the program to do?", display_menu);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);
	glutIdleFunc(idle);
	glutMainLoop();
	return 1;
}
