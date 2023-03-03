#include <iostream>
#include <array>
#include <vector>
#include <glut.h>

using namespace std;

//A particle is defined by an identity number,a mass,a position and a velocity.
struct particle
{
	int x;
	float mass;
	array<float, 3> position;
	array<float, 3> velocity;
};

bool elastic = true;
//I want particles to get inital speed which is -100<speed<100.
float minSpeed = -100.0;
float maxSpeed = 100.0;
//Generator refresh.
float gRefresh = 200;
//Position refresh.
float pRefresh = 10;
float g[3] = { 0, -300, 0 };
int pnumber = 0;
//Save each particle in a vector.
vector<particle> save;

void gTimer(int);
void pTimer(int);
void rTimer(int);

void initEnvironment()
{
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1.0, 40, 600);
	gluLookAt(0, 100, -400, 0, 100, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	gTimer(0);
	pTimer(0);
	rTimer(0);
}

//Create random velocity.
float velocity()
{
	float u = static_cast <float> (rand());
	float v = static_cast <float> (RAND_MAX / (maxSpeed - minSpeed));
	float speed = minSpeed + u / v;
	return speed;
}

void generateParticles()
{
	pnumber++;
	particle p = { pnumber, 0.5,{ 0,300,0 },{ velocity(),velocity(),velocity() } };
	save.push_back(p);
}

//How often to generate particles.
void gTimer(int)
{
	generateParticles();
	glutTimerFunc(gRefresh, gTimer, 0);
}

void updateParticle(particle& p)
{
	float a = 0.8;
	float step = 0.01;
	//Check if a particle hits the plane z=0.
	if (p.position[1] + step * p.velocity[1] < 0)
	{
		if (elastic)
		{
			p.velocity[1] = -p.velocity[1];
		}
		//If the collision is inelastic,the velocity is getting smaller.
		else
		{
			p.velocity[1] = -a * p.velocity[1];
		}
	}
	//Specify the position of each particle by using Euler aproximation.
	for (int i = 0; i < 3; i++)
	{
		p.position[i] += p.velocity[i] * step;
		p.velocity[i] += (g[i] / p.mass) * step;
	}
}

//How often to update each particle's position.
void pTimer(int)
{
	for (auto p = save.begin(); p < save.end(); ++p)
	{
		updateParticle((*p));
	}
	glutTimerFunc(pRefresh, pTimer, 0);
}

//How often to make changes on the screen.
void rTimer(int)
{
	glutPostRedisplay();
	glutTimerFunc(pRefresh, rTimer, 0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Draw the plane z=0;
	glColor3f(0.5, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-200, 0, -200);
	glVertex3f(-200, 0, 200);
	glVertex3f(200, 0, 200);
	glVertex3f(200, 0, -200);
	glEnd();

	//Draw the generator point.
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(15);
	glBegin(GL_POINTS);
	glVertex3f(0.0, 300.0, 0.0);
	glEnd();

	//Draw the particles as solid spheres.
	for (auto k = save.begin(); k < save.end(); ++k)
	{
		particle p = *k;
		glLoadIdentity();
		glColor3f(1.0, 1.0, 0.0);
		glTranslatef(p.position[0], p.position[1], p.position[2]);
		glutSolidSphere(5, 16, 16);
	}
	glutSwapBuffers();
	return;
}

//Change the type of collision by pressing the space key.
void keyboard(unsigned char key, int x, int y)
{
	if (key == 32)
	{
		elastic = !elastic;
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 200);
	glutCreateWindow("Particles");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	initEnvironment();
	glutMainLoop();
}
