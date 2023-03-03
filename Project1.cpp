#include <iostream>
#include <glut.h>

using namespace std;

GLfloat interPoints[4][3];
float inverseMBxMp[4][4] = { {1, 0, 0, 0},{-0.833, 3, -1.5, 0.333},{0.333, -1.5, 3, -0.8333},{0, 0, 0, 1} };
GLfloat bezPoints[4][3];
GLfloat p2[6][3];
GLfloat p3[7][3] = { {-0.9,0.0,0.0},{-0.7,0.7,0.0},{-0.5,-0.5,0.0},{0.0,0.0,0.0},{0.5,0.5,0.0},{0.7,-0.7,0.0},{0.9,0.0,0.0} };
GLfloat p4[4][4][3] =
{ {{0.0,-0.9,0.0},{-0.8,-0.7,0.6},{-0.8,-0.4,0.8},{0.0,0.0,0.9}},
{{-0.8,-0.5,-0.3},{-0.8,-0.3,0.1},{-0.8,-0.1,0.5},{-0.8,0.2,0.6}},
{{-0.8,-0.2,-0.5},{-0.8,-0.1,-0.3},{-0.8,0.3,0.2},{-0.8,0.6,0.2}},
{{0.0,0.0,-0.9},{-0.8,0.4,-0.8},{-0.8,0.7,-0.6},{0.0,0.9,0.0}} };
int clicks1 = 0;
int clicks2 = 0;
float dist[7];
float rx, ry;
int mode;
const float COLOR[] = { 0.0, 0.0, 0.0 };
bool camera = false;

void init()
{
	glClearColor(COLOR[0], COLOR[1], COLOR[2], COLOR[3]);
	std::cout << "Right click to choose curve/surface." << endl;
}

void interToBez(float bezPoints[4][3])
{
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			bezPoints[i][j] = 0;
			for (int k = 0; k <= 3; k++)
			{
				bezPoints[i][j] += inverseMBxMp[i][k] * interPoints[k][j];
			}
		}
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (mode)
	{
	case 1:
		if (clicks1 > 3)
		{
			interToBez(bezPoints);
			glColor3f(0.0, 1.0, 0.0);
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &bezPoints[0][0]);
			glEnable(GL_MAP1_VERTEX_3);
			glMapGrid1f(100, 0.0, 1.0);
			glEvalMesh1(GL_LINE, 0, 100);
			for (int i = 0; i <= 3; i++)
			{
				glColor3f(1.0, 0.0, 0.0);
				glPointSize(6);
				glBegin(GL_POINTS);
				glVertex3f(interPoints[i][0], interPoints[i][1], 0.0);
				glEnd();
			}
		}
		break;
	case 2:
		if (clicks2 > 4)
		{
			glColor3f(0.0, 1.0, 0.0);
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 6, &p2[0][0]);
			glEnable(GL_MAP1_VERTEX_3);
			glMapGrid1f(100, 0.0, 1.0);
			glEvalMesh1(GL_LINE, 0, 100);
			for (int i = 0; i <= 4; i++)
			{
				glColor3f(1.0, 0.0, 0.0);
				glPointSize(6);
				glBegin(GL_POINTS);
				glVertex3f(p2[i][0], p2[i][1], 0.0);
				glEnd();
			}
			glColor3f(0.0, 0.0, 1.0);
			for (int i = 0; i <= 3; i++)
			{
				glBegin(GL_LINES);
				glVertex3f(p2[i][0], p2[i][1], 0.0);
				glVertex3f(p2[i + 1][0], p2[i + 1][1], 0.0);
				glEnd();
			}
			glBegin(GL_LINES);
			glVertex3f(p2[4][0], p2[4][1], 0.0);
			glVertex3f(p2[0][0], p2[0][1], 0.0);
			glEnd();
		}
		break;
	case 3:
		glColor3f(0.0, 1.0, 1.0);
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &p3[0][0]);
		glEnable(GL_MAP1_VERTEX_3);
		glMapGrid1f(100, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 100);

		glColor3f(1.0, 0.0, 0.0);
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &p3[3][0]);
		glEnable(GL_MAP1_VERTEX_3);
		glMapGrid1f(100, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 100);

		for (int i = 0; i <= 6; i++)
		{
			glColor3f(0.0, 1.0, 0.0);
			glPointSize(6);
			glBegin(GL_POINTS);
			glVertex3f(p3[i][0], p3[i][1], 0.0);
			glEnd();
			glColor3f(1.0, 1.0, 0.0);
			glBegin(GL_LINES);
			glVertex3f(p3[2][0], p3[2][1], 0.0);
			glVertex3f(p3[4][0], p3[4][1], 0.0);
			glEnd();
		}
		break;
	case 4:
		if (camera)
		{
			glRotatef(60, 0.0, 1.0, 0.0);
		}
		else
		{
			glRotatef(-60.0, 0.0, 1.0, 0.0);
		}
		glColor3f(0.0, 1.0, 0.0);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4, &p4[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);
		for (int i = 0; i <= 3; i++)
		{
			for (int j = 0; j <= 3; j++)
			{
				glColor3f(1.0, 0.0, 0.0);
				glPointSize(6);
				glBegin(GL_POINTS);
				glVertex3f(p4[i][j][0], p4[i][j][1], p4[i][j][2]);
				glEnd();
			}
		}
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(p4[0][0][0], p4[0][0][1], p4[0][0][2]);
		glVertex3f(p4[3][0][0], p4[3][0][1], p4[3][0][2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(p4[0][3][0], p4[0][3][1], p4[0][3][2]);
		glVertex3f(p4[3][3][0], p4[3][3][1], p4[3][3][2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(p4[3][0][0], p4[3][0][1], p4[3][0][2]);
		glVertex3f(p4[3][3][0], p4[3][3][1], p4[3][3][2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(p4[0][3][0], p4[0][3][1], p4[0][3][2]);
		glVertex3f(p4[0][0][0], p4[0][0][1], p4[0][0][2]);
		glEnd();
		break;
	}
	glutSwapBuffers();
	return;
}

void mouse(int button, int state, int x, int y)
{
	glutSwapBuffers();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		rx = (2.0 * x) / (float)(500 - 1) - 1.0;
		ry = (2.0 * (500 - 1 - y)) / (float)(500 - 1) - 1.0;
		if (mode == 1)
		{
			if (clicks1 <= 3)
			{
				interPoints[clicks1][0] = rx;
				interPoints[clicks1][1] = ry;
				interPoints[clicks1][2] = 0.0;
				glColor3f(1.0, 0.0, 0.0);
				glPointSize(6);
				glBegin(GL_POINTS);
				glVertex3f(rx, ry, 0.0);
				glEnd();
				glFlush();
			}
			if (clicks1 == 3)
			{
				interToBez(bezPoints);
				glColor3f(0.0, 1.0, 0.0);
				glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &bezPoints[0][0]);
				glEnable(GL_MAP1_VERTEX_3);
				glMapGrid1f(100, 0.0, 1.0);
				glEvalMesh1(GL_LINE, 0, 100);
			}
			clicks1++;
		}
		if (mode == 2)
		{
			if (clicks2 <= 4)
			{
				p2[clicks2][0] = rx;
				p2[clicks2][1] = ry;
				p2[clicks2][2] = 0.0;
				p2[5][0] = p2[0][0];
				p2[5][1] = p2[0][1];
				p2[5][2] = 0.0;
				glColor3f(1.0, 0.0, 0.0);
				glPointSize(6);
				glBegin(GL_POINTS);
				glVertex3f(rx, ry, 0.0);
				glEnd();
				glFlush();
			}
			if (clicks2 == 4)
			{
				glColor3f(0.0, 0.0, 1.0);
				for (int i = 0; i <= 3; i++)
				{
					glBegin(GL_LINES);
					glVertex3f(p2[i][0], p2[i][1], 0.0);
					glVertex3f(p2[i + 1][0], p2[i + 1][1], 0.0);
					glEnd();
				}
				glBegin(GL_LINES);
				glVertex3f(p2[4][0], p2[4][1], 0.0);
				glVertex3f(p2[0][0], p2[0][1], 0.0);
				glEnd();
				glColor3f(0.0, 1.0, 0.0);
				glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 6, &p2[0][0]);
				glEnable(GL_MAP1_VERTEX_3);
				glMapGrid1f(100, 0.0, 1.0);
				glEvalMesh1(GL_LINE, 0, 100);
			}
			clicks2++;
		}
	}
}

void motion(int x, int y)
{
	if (mode != 4)
	{
		rx = (2.0 * x) / (float)(500 - 1) - 1.0;
		ry = (2.0 * (500 - 1 - y)) / (float)(500 - 1) - 1.0;
		if (mode == 1)
		{
			if (clicks1 > 3)
			{
				int i;
				for (i = 0; i <= 4; i++)
				{
					dist[i] = sqrt(pow((interPoints[i][0] - rx), 2) + pow((interPoints[i][1] - ry), 2));
				}
				int minimum = 0;
				for (i = 0; i <= 4; i++)
				{
					if (dist[i] < dist[minimum])
					{
						minimum = i;
					}
				}
				interPoints[minimum][0] = rx; interPoints[minimum][1] = ry;
			}
		}
		if (mode == 2)
		{
			if (clicks2 > 4)
			{
				int i;
				for (i = 0; i <= 4; i++)
				{
					dist[i] = sqrt(pow((p2[i][0] - rx), 2) + pow((p2[i][1] - ry), 2));
				}
				int minimum = 0;
				for (i = 0; i <= 4; i++)
				{
					if (dist[i] < dist[minimum])
					{
						minimum = i;
					}
				}
				p2[minimum][0] = rx; p2[minimum][1] = ry;
				if (minimum == 0)
				{
					p2[5][0] = rx;
					p2[5][1] = ry;
				}
				else
				{
					p2[5][0] = p2[0][0];
					p2[5][1] = p2[0][1];
				}
			}
		}
		if (mode == 3)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(1.0, 0.0, 0.0);
			int i;
			for (i = 0; i <= 6; i++)
			{
				dist[i] = sqrt(pow((p3[i][0] - rx), 2) + pow((p3[i][1] - ry), 2));
			}
			int minimum = 0;
			for (i = 0; i <= 6; i++)
			{
				if (dist[i] < dist[minimum])
				{
					minimum = i;
				}
			}
			if (minimum == 3)
			{
				p3[2][0] = p3[2][0] + rx - p3[3][0];
				p3[2][1] = p3[2][1] + ry - p3[3][1];
				p3[4][0] = p3[4][0] + rx - p3[3][0];
				p3[4][1] = p3[4][1] + ry - p3[3][1];
				p3[minimum][0] = rx; p3[minimum][1] = ry;
			}
			if (minimum == 2)
			{
				p3[4][0] = p3[4][0] - rx + p3[2][0];
				p3[4][1] = p3[4][1] - ry + p3[2][1];
				p3[minimum][0] = rx; p3[minimum][1] = ry;
			}
			if (minimum == 4)
			{
				p3[2][0] = p3[2][0] - rx + p3[4][0];
				p3[2][1] = p3[2][1] - ry + p3[4][1];
				p3[minimum][0] = rx; p3[minimum][1] = ry;
			}
			else
				p3[minimum][0] = rx; p3[minimum][1] = ry;
		}
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 32)
	{
		camera = !camera;
		glutPostRedisplay();
	}
}

void menu(int choose)
{
	if (choose != 5)
	{
		mode = choose;
		glutPostRedisplay();
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
	glutInitWindowPosition(300, 200);
	glutCreateWindow("Bezier Curves and Surface");
	glutCreateMenu(menu);
	glutAddMenuEntry("Cubic Interpolation Curve", 1);
	glutAddMenuEntry("Closed Bezier 5-Degree Curve", 2);
	glutAddMenuEntry("Two cubic C1 Bezier Curves", 3);
	glutAddMenuEntry("Bicubic Bezier Surface", 4);
	glutAddMenuEntry("Exit", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}
