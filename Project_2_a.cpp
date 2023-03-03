#include <math.h>
#include <iostream>
#include <array>
#include <glut.h>

using namespace std;
int a = 0;
int mode = 0;
std::array<float, 15> angles = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
std::array<float, 15> old_angles;
std::array<float, 15> new_angles;
GLUquadricObj* torso, * neck, * head,
* bruleg, * brdleg, * brpow, * bluleg, * bldleg, * blpow,
* fruleg, * frdleg, * frpow, * fluleg, * fldleg, * flpow;
void updateMode(int new_mode);
void repeat(int);

void initEnvironment()
{
	torso = gluNewQuadric();
	gluQuadricDrawStyle(torso, GLU_FILL);
	neck = gluNewQuadric();
	gluQuadricDrawStyle(neck, GLU_FILL);
	bruleg = gluNewQuadric();
	gluQuadricDrawStyle(bruleg, GLU_FILL);
	brdleg = gluNewQuadric();
	gluQuadricDrawStyle(brdleg, GLU_FILL);
	brpow = gluNewQuadric();
	gluQuadricDrawStyle(brpow, GLU_FILL);
	bluleg = gluNewQuadric();
	gluQuadricDrawStyle(bluleg, GLU_FILL);
	bldleg = gluNewQuadric();
	gluQuadricDrawStyle(bldleg, GLU_FILL);
	blpow = gluNewQuadric();
	gluQuadricDrawStyle(blpow, GLU_FILL);
	fruleg = gluNewQuadric();
	gluQuadricDrawStyle(fruleg, GLU_FILL);
	frdleg = gluNewQuadric();
	gluQuadricDrawStyle(frdleg, GLU_FILL);
	frpow = gluNewQuadric();
	gluQuadricDrawStyle(frpow, GLU_FILL);
	fluleg = gluNewQuadric();
	gluQuadricDrawStyle(fluleg, GLU_FILL);
	fldleg = gluNewQuadric();
	gluQuadricDrawStyle(fldleg, GLU_FILL);
	flpow = gluNewQuadric();
	gluQuadricDrawStyle(flpow, GLU_FILL);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-100, 100, -100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	updateMode(6);
	repeat(0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (a == 0)
	{
		glRotatef(90, 0.0, 1.0, 0.0);
	}
	else if (a == 1)
	{
		glRotatef(30.0, 0.0, 1.0, 0.0);
	}
	else if (a == 2)
	{
		glRotatef(-30.0, 0.0, 1.0, 0.0);
	}
	glColor3ub(45, 3, 3);
	glRotatef(angles[0], 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0, 0, -45);
	gluCylinder(torso, 15, 15, 70, 10, 10);
	glColor3ub(110, 30, 15);
	glTranslatef(0, 10, 65);
	glRotatef(angles[1], 1.0, 0.0, 0.0);
	glRotatef(-30, 1.0, 0.0, 0.0);
	gluCylinder(neck, 4, 4, 20, 10, 10);
	glColor3ub(45, 3, 3);
	glTranslatef(0, 0, 25);
	glRotatef(angles[2], 1.0, 0.0, 0.0);
	glutSolidSphere(10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(110, 30, 15);
	glTranslatef(-9, -10, -40);
	glRotatef(angles[3], 1.0, 0.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(bruleg, 5, 5, 20, 10, 10);
	glColor3ub(45, 3, 3);
	glTranslatef(0, 0, 15);
	glRotatef(angles[4], 1.0, 0.0, 0.0);
	gluCylinder(brdleg, 5, 5, 25, 10, 10);
	glColor3ub(110, 30, 15);
	glTranslatef(0, -5, 27);
	glRotatef(angles[5], 1.0, 0.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(brpow, 3, 3, 20, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(110, 30, 15);
	glTranslatef(9, -10, -40);
	glRotatef(angles[6], 1.0, 0.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(bluleg, 5, 5, 20, 10, 10);
	glColor3ub(45, 3, 3);;
	glTranslatef(0, 0, 15);
	glRotatef(angles[7], 1.0, 0.0, 0.0);
	gluCylinder(bldleg, 5, 5, 25, 10, 10);
	glColor3ub(110, 30, 15);
	glTranslatef(0, -5, 27);;
	glRotatef(angles[8], 1.0, 0.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(blpow, 3, 3, 20, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(110, 30, 15);
	glTranslatef(-9, -10, 20);
	glRotatef(angles[9], 1.0, 0.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(fruleg, 5, 5, 20, 10, 10);
	glColor3ub(45, 3, 3);
	glTranslatef(0, 0, 15);
	glRotatef(angles[10], 1.0, 0.0, 0.0);
	gluCylinder(frdleg, 5, 5, 25, 10, 10);
	glColor3ub(110, 30, 15);
	glTranslatef(0, -5, 27);
	glRotatef(angles[11], 1.0, 0.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(frpow, 3, 3, 20, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(110, 30, 15);
	glTranslatef(9, -10, 20);
	glRotatef(angles[12], 1.0, 0.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(fluleg, 5, 5, 20, 10, 10);
	glColor3ub(45, 3, 3);
	glTranslatef(0, 0, 15);
	glRotatef(angles[13], 1.0, 0.0, 0.0);
	gluCylinder(fldleg, 5, 5, 25, 10, 10);
	glColor3ub(110, 30, 15);
	glTranslatef(0, -5, 27);
	glRotatef(angles[14], 1.0, 0.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(flpow, 3, 3, 20, 10, 10);
	glPopMatrix();

	glutSwapBuffers();
	return;
}

void updateAngles(void)
{
	for (int i = 0; i < 15; i++)
	{
		if ((new_angles[i] >= old_angles[i]) && (new_angles[i] <= angles[i]))
		{
			angles[i] = new_angles[i];
		}
		else if ((new_angles[i] <= old_angles[i]) && (new_angles[i] >= angles[i]))
		{
			angles[i] = new_angles[i];
		}
		else
		{
			angles[i] += (new_angles[i] - old_angles[i]) / 100;
		}
	}
	glutPostRedisplay();
	return;
}

void repeat(int)
{
	updateAngles();
	glutTimerFunc(3, repeat, 0);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 32)
	{
		a++;
		glutPostRedisplay();
		if (a == 3)
		{
			a = 0;
		}
	}
}

void updateMode(int new_mode)
{
	mode = new_mode;
	switch (mode)
	{
	case 1:
	{
		array<float, 15> theta = { 0, 0, 0, 0 ,0, 0, 0, 0, 0, -60, 100, 0 , -60 , 100, 0 };
		new_angles = theta;
		break;
	}
	case 2:
	{
		array<float, 15> theta = { -45, 0, 0, 20 , 30 , 0 , 20, 30, 0, -60, 100, 0, -60, 100, 0 };
		new_angles = theta;
		break;
	}
	case 3:
	{
		array<float, 15> theta = { 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		new_angles = theta;
		break;
	}
	case 4:
	{
		array<float, 15> theta = { 0, 0, 0, 10, 5, 0, -50, 50, 0, -30, 15, 0, -60, 100, 0 };
		new_angles = theta;
		break;
	}
	case 5:
	{
		array<float, 15> theta = { 0, 0, 0, 50, 10, 0, 50, 10, 0, -50, 10, 0, -50, 10, 0 };
		new_angles = theta;
		break;
	}
	case 6:
	{
		array<float, 15> theta = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		new_angles = theta;
		break;
	}
	}
	old_angles = angles;
	glutPostRedisplay();
}

void menu(int id)
{
	if (id != 7)
	{
		updateMode(id);
	}
	else
	{
		exit(0);
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 200);
	glutCreateWindow("Dog model");
	glEnable(GL_DEPTH_TEST);
	glutCreateMenu(menu);
	glutAddMenuEntry("Front legs up", 1);
	glutAddMenuEntry("Stand in back legs", 2);
	glutAddMenuEntry("Head-neck down", 3);
	glutAddMenuEntry("Walk position", 4);
	glutAddMenuEntry("Run position", 5);
	glutAddMenuEntry("Initial position", 6);
	glutAddMenuEntry("Exit", 7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(display);
	initEnvironment();
	glutMainLoop();
}
