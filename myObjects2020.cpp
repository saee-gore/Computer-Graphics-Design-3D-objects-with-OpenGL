#include <math.h>
#include <GL\glut.h>


const GLfloat DtoR = 0.017453;
const GLfloat Pi = 3.14159;

void parabola(float a, float h, float k, float leftEnd, float rightEnd);
void parabola2(float a, float b, float c, float leftEnd, float rightEnd);
void circle(float x0, float y0, float r);
void ellipse(float x0, float y0, float a, float b);
void cone(float r, float h);
void cylinder(float r, float h);
void colorCube(float a, float b, float c, float size);
void axes(float length);
void sphere(float r, int slices, int stacks);
void ellipsoid(float a, float b, float c, int slices, int stacks);
void paraboloid(float a, float b, float c, int slices, int stacks);
void normal(float p0[], float p1[], float p2[], float n[]);
void normal(float p0[], float p1[], float p2[], float n[], float size);

void normal(float p0[], float p1[], float p2[], float n[], float size)
{
	float a[3], b[3];
	float d;

	for (int i = 0; i < 3; i++)
	{
		a[i] = p1[i] - p0[i];
		b[i] = p2[i] - p0[i];
	}

	n[0] = (a[1] * b[2] - a[2] * b[1]);
	n[1] = (a[2] * b[0] - a[0] * b[2]);
	n[2] = (a[0] * b[1] - a[1] * b[0]);

	d = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);

	if (d == 0)
		d = 1;

	for (int i = 0; i < 3; i++)
		n[i] = n[i] / d * size;
}

void normal(float p0[], float p1[], float p2[], float n[])
{
	float a[3], b[3];
	float d;

	for (int i = 0; i < 3; i++)
	{
		a[i] = p1[i] - p0[i];
		b[i] = p2[i] - p0[i];
	}

	n[0] = a[1] * b[2] - a[2] * b[1];
	n[1] = a[2] * b[0] - a[0] * b[2];
	n[2] = a[0] * b[1] - a[1] * b[0];

	d = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);

	if (d == 0)
		d = 1;

	for (int i = 0; i < 3; i++)
		n[i] = n[i] / d;
}

void normalize(float p[3])
{
	float dSquare = p[0] * p[0] + p[1] * p[1] + p[2] * p[2];

	if (dSquare != 0.0)
		for (int i = 0; i < 3; i++)
			p[i] = p[i] / sqrt(dSquare);
}

void paraboloidN(float a, float b, float c, int slices, int stacks)
{
	float z1, z2;
	float dz = c / stacks;
	int dTheta = (int)(360.0 / slices);
	float p1[3], p2[3], p3[3], p4[3];
	float n1[3], n2[3], n3[3], n4[3];
	float xAxis1, yAxis1, xAxis2, yAxis2;

	for (int i = 0; i < stacks; i++)
	{
		for (int theta = 0; theta <= 360; theta += dTheta)
		{
			z1 = i * dz;
			xAxis1 = a * sqrt(z1 / c);
			yAxis1 = b * sqrt(z1 / c);

			z2 = z1 + dz;
			xAxis2 = a * sqrt(z2 / c);
			yAxis2 = b * sqrt(z2 / c);

			p1[0] = xAxis1 * cos(theta*DtoR);
			p1[1] = yAxis1 * sin(theta*DtoR);
			p1[2] = z1;
			n1[0] = 2 * p1[0] / a / a;
			n1[1] = 2 * p1[1] / b / b;
			n1[2] = -1.0 / c;
			normalize(n1);

			p2[0] = xAxis1 * cos((theta + dTheta)*DtoR);
			p2[1] = yAxis1 * sin((theta + dTheta)*DtoR);
			p2[2] = z1;
			n2[0] = 2 * p2[0] / a / a;
			n2[1] = 2 * p2[1] / b / b;
			n2[2] = -1.0 / c;
			normalize(n2);

			p3[0] = xAxis2 * cos((theta + dTheta)*DtoR);
			p3[1] = yAxis2 * sin((theta + dTheta)*DtoR);
			p3[2] = z2;
			n3[0] = 2 * p3[0] / a / a;
			n3[1] = 2 * p3[1] / b / b;
			n3[2] = -1.0 / c;
			normalize(n3);

			p4[0] = xAxis2 * cos(theta*DtoR);
			p4[1] = yAxis2 * sin(theta*DtoR);
			p4[2] = z2;
			n4[0] = 2 * p4[0] / a / a;
			n4[1] = 2 * p4[1] / b / b;
			n4[2] = -1.0 / c;
			normalize(n4);

			glBegin(GL_POLYGON);
			glNormal3fv(n1);
			glVertex3fv(p1);

			glNormal3fv(n2);
			glVertex3fv(p2);

			glNormal3fv(n3);
			glVertex3fv(p3);

			glNormal3fv(n4);
			glVertex3fv(p4);
			glEnd();
		}
	}
}


void paraboloid(float a, float b, float c, int slices, int stacks)
{
	float z1, z2;
	float dz = c / stacks;
	int dTheta = (int)(360.0 / slices);
	float x, y;


	for (int i = 0; i <= stacks; i++)
	{
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= slices + 1; j++)
		{
			z1 = i * dz;
			x = a * sqrt(z1 / c)*cos(j*dTheta*DtoR);
			y = b * sqrt(z1 / c)*sin(j*dTheta*DtoR);
			glVertex3f(x, y, z1);

			z2 = z1 + dz;
			x = a * sqrt(z2 / c)*cos(j*dTheta*DtoR);
			y = b * sqrt(z2 / c)*sin(j*dTheta*DtoR);
		}
		glEnd();
	}
	//glEnd();
}

void ellipsoid(float a, float b, float c, int slices, int stacks)
{
	GLint longitude = (int)(360.0 / slices);
	GLint latitude = (int)(180.0 / stacks);
	GLint phi, theta;
	GLfloat p1[3], p2[3], p3[3], p4[3];

	glBegin(GL_POLYGON);
	for (phi = 0; phi < 180; phi += latitude)
	{
		for (theta = 0; theta < 360; theta += longitude)
		{
			p1[0] = a * sin(phi*DtoR)*cos(theta*DtoR);
			p1[1] = b * sin(phi*DtoR)*sin(theta*DtoR);
			p1[2] = c * cos(phi*DtoR);

			p2[0] = a * sin((phi + latitude)*DtoR)*cos(theta*DtoR);
			p2[1] = b * sin((phi + latitude)*DtoR)*sin(theta*DtoR);
			p2[2] = c * cos((phi + latitude)*DtoR);

			p3[0] = a * sin((phi + latitude)*DtoR)*cos((theta + longitude)*DtoR);
			p3[1] = b * sin((phi + latitude)*DtoR)*sin((theta + longitude)*DtoR);
			p3[2] = c * cos((phi + latitude)*DtoR);

			p4[0] = a * sin((phi)*DtoR)*cos((theta + longitude)*DtoR);
			p4[1] = b * sin((phi)*DtoR)*sin((theta + longitude)*DtoR);
			p4[2] = c * cos((phi)*DtoR);

			glVertex3fv(p1);
			glVertex3fv(p2);
			glVertex3fv(p3);
			glVertex3fv(p4);
		}
	}
	glEnd();
}

void sphere(float r, int slices, int stacks)
{
	GLint longitude = (int)(360.0 / slices);
	GLint latitude = (int)(180.0 / stacks);
	GLint phi, theta;
	GLfloat p1[3], p2[3], p3[3], p4[3];

	for (phi = 0; phi <= 180 - latitude; phi += latitude)
	{
		for (theta = 0; theta <= 360; theta += longitude)
		{
			p1[0] = r * sin(phi*DtoR)*cos(theta*DtoR);
			p1[1] = r * sin(phi*DtoR)*sin(theta*DtoR);
			p1[2] = r * cos(phi*DtoR);

			p2[0] = r * sin((phi + latitude)*DtoR)*cos(theta*DtoR);
			p2[1] = r * sin((phi + latitude)*DtoR)*sin(theta*DtoR);
			p2[2] = r * cos((phi + latitude)*DtoR);

			p3[0] = r * sin((phi + latitude)*DtoR)*cos((theta + longitude)*DtoR);
			p3[1] = r * sin((phi + latitude)*DtoR)*sin((theta + longitude)*DtoR);
			p3[2] = r * cos((phi + latitude)*DtoR);

			p4[0] = r * sin((phi)*DtoR)*cos((theta + longitude)*DtoR);
			p4[1] = r * sin((phi)*DtoR)*sin((theta + longitude)*DtoR);
			p4[2] = r * cos((phi)*DtoR);

			glBegin(GL_POLYGON);
			glVertex3fv(p1);
			glVertex3fv(p2);
			glVertex3fv(p3);
			glVertex3fv(p4);
			glEnd();
		}
	}
}

void axes(float length)
{
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-1 * length, 0, 0);
	glVertex3f(length, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, -1 * length, 0);
	glVertex3f(0, length, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -1 * length);
	glVertex3f(0, 0, length);
	glEnd();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(length, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(length / 40, length / 8, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0, length, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(length / 40, length / 8, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(0, 0, length);
	glutSolidCone(length / 40, length / 8, 20, 10);
	glPopMatrix();

	glPopAttrib();
	glPopMatrix();
}

//void axes(float length)	// a simple version
//{
//	//glLineWidth(1);
//	glBegin(GL_LINES);
//	glColor3f(0.8, 0, 0);
//	glVertex3f(-0.5*length, 0, 0);
//	glVertex3f(0.5*length, 0, 0);
//
//	glColor3f(0, 0.8, 0);
//	glVertex3f(0, -0.5*length, 0);
//	glVertex3f(0, 0.5*length, 0);
//
//	glColor3f(0, 0, 0.8);
//	glVertex3f(0, 0, -0.5*length);
//	glVertex3f(0, 0, 0.5*length);
//	glEnd();
//}

void colorCube(float a, float b, float c, float size)
{
	glBegin(GL_QUAD_STRIP);
	glColor3f(0, 0, 0);
	glVertex3f(a - 0.5*size, b - 0.5*size, c - 0.5*size);

	glColor3f(1, 0, 0);
	glVertex3f(a + 0.5*size, b - 0.5*size, c - 0.5*size);

	glColor3f(0, 1, 0);
	glVertex3f(a - 0.5*size, b + 0.5*size, c - 0.5*size);

	glColor3f(1, 1, 0);
	glVertex3f(a + 0.5*size, b + 0.5*size, c - 0.5*size);

	glColor3f(0, 1, 1);
	glVertex3f(a - 0.5*size, b + 0.5*size, c + 0.5*size);

	glColor3f(1, 1, 1);
	glVertex3f(a + 0.5*size, b + 0.5*size, c + 0.5*size);

	glColor3f(0, 0, 1);
	glVertex3f(a - 0.5*size, b - 0.5*size, c + 0.5*size);

	glColor3f(1, 0, 1);
	glVertex3f(a + 0.5*size, b - 0.5*size, c + 0.5*size);

	glColor3f(0, 0, 0);
	glVertex3f(a - 0.5*size, b - 0.5*size, c - 0.5*size);

	glColor3f(1, 0, 0);
	glVertex3f(a + 0.5*size, b - 0.5*size, c - 0.5*size);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(a + 0.5*size, b - 0.5*size, c - 0.5*size);

	glColor3f(1, 1, 0);
	glVertex3f(a + 0.5*size, b + 0.5*size, c - 0.5*size);

	glColor3f(1, 1, 1);
	glVertex3f(a + 0.5*size, b + 0.5*size, c + 0.5*size);

	glColor3f(1, 0, 1);
	glVertex3f(a + 0.5*size, b - 0.5*size, c + 0.5*size);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex3f(a - 0.5*size, b - 0.5*size, c - 0.5*size);

	glColor3f(0, 1, 0);
	glVertex3f(a - 0.5*size, b + 0.5*size, c - 0.5*size);

	glColor3f(0, 1, 1);
	glVertex3f(a - 0.5*size, b + 0.5*size, c + 0.5*size);

	glColor3f(0, 0, 1);
	glVertex3f(a - 0.5*size, b - 0.5*size, c + 0.5*size);
	glEnd();
}


void cylinder(float r, float h)
{
	glBegin(GL_QUAD_STRIP);
	for (int theta = 0; theta <= 360; theta += 5)
	{
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), 0);
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), h);
	}

	glEnd();
}


void cone(float r, float h)
{
	glBegin(GL_TRIANGLE_FAN);
	for (int theta = 0; theta <= 360; theta += 5)
	{
		glVertex3f(0, 0, h);
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), 0);
		glVertex3f(r*cos((theta + 5)*DtoR), r*sin((theta + 5)*DtoR), 0);

	}
	glEnd();
}

void parabola2(float a, float b, float c, float leftEnd, float rightEnd)
{
	float x, y, dx = 0.01;


	glBegin(GL_LINE_STRIP);
	x = leftEnd;
	while (x <= rightEnd)
	{
		y = a * x*x + b * x + c;

		glVertex2f(x, y);

		x += dx;
	}
	glEnd();
}

void ellipse(float x0, float y0, float a, float b)
{
	float theta, dTheta = 1;
	float x, y;

	glBegin(GL_POLYGON);
	theta = 0;
	while (theta < 360)
	{
		x = x0 + a * cos(theta*DtoR);
		y = y0 + b * sin(theta*DtoR);

		glVertex2f(x, y);

		theta += dTheta;
	}
	glEnd();
}

void circle(float x0, float y0, float r)
{
	float theta, dTheta = 1;
	int count;
	float x, y;

	count = (int)(360.0 / dTheta);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= count; i++)
	{
		theta = i * dTheta*DtoR;
		x = x0 + r * cos(theta);
		y = y0 + r * sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

void parabola(float a, float h, float k, float leftEnd, float rightEnd)
{
	float x, y;
	float dx = 0.01;

	x = leftEnd;
	glBegin(GL_LINE_STRIP);
	while (x <= rightEnd)
	{
		y = a * (x - h)*(x - h) + k;

		glVertex2f(x, y);

		x += dx;
	}
	glEnd();
}
